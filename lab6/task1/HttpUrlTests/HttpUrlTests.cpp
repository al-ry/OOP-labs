#include "stdafx.h"
#include "../HTTPURL/HTTPUrl.h"
#include "../HTTPURL/UrlParsingError.h"



using namespace std;

template <typename Ex, typename Fn>
void ExpectException(Fn&& fn, const string& expectedDescription)
{
	BOOST_CHECK_EXCEPTION(fn(), Ex, [&](const Ex& e) {
		return e.what() == expectedDescription;
	});
}

template <typename Ex>
void ExpectConstructorFailure(std::string const& domain, std::string const& document, Protocol protocol, 
	unsigned short port, const string& expectedDescription)
{
	ExpectException<Ex>([&] {
		CHttpUrl(domain, document, protocol, port);
	},
		expectedDescription);
}
template <typename Ex>
void ExpectConstructorFailure(const std::string& url, const string& expectedDescription)
{
	ExpectException<Ex>([&] {
		CHttpUrl url(url);
	},
		expectedDescription);
}
template <typename Ex>
void ExpectConstructorFailure(std::string const& domain,
	std::string const& document,
	Protocol protocol,
	const string& expectedDescription)
{
	ExpectException<Ex>([&] {
		CHttpUrl(domain, document, protocol);
	},
		expectedDescription);
}

void VerifyUrlParsing(const std::string& expUrl,
	std::string const& expDomain,
	std::string const& expDocument,
	Protocol expProtocol,
	unsigned short expPort, const CHttpUrl& checkedUrl)
{
	BOOST_REQUIRE_EQUAL(expUrl, checkedUrl.GetURL());
	BOOST_REQUIRE_EQUAL(expDomain, checkedUrl.GetDomain());
	BOOST_REQUIRE_EQUAL(expDocument, checkedUrl.GetDocument());
	BOOST_REQUIRE(expProtocol == checkedUrl.GetProtocol());
	BOOST_REQUIRE_EQUAL(expPort, checkedUrl.GetPort());
}

BOOST_AUTO_TEST_SUITE(Test_exceptions)
	BOOST_AUTO_TEST_CASE(when_protocol_incorrect_should_throw_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("invalidProtocol://www.mysite.com", "Invalid URL protocol");
	}
	BOOST_AUTO_TEST_CASE(when_port_is_upper_should_throw_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("https://www.mysite.com:150000", "Out of range port");
	}
	BOOST_AUTO_TEST_CASE(when_port_is_lower_should_throw_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("https://www.mysite.com:0", "Out of range port");
	}
	BOOST_AUTO_TEST_CASE(when_port_is_completely_incorrect_should_throw_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("https//qwerty", "Invalid URL");
	}
	BOOST_AUTO_TEST_CASE(when_port_is_empty_should_throw_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("https://www.mysite.com:", "Invalid URL");
	}
	BOOST_AUTO_TEST_CASE(when_url_contains_spaces_should_throw_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("https://   www.mysite.com/  document", "Invalid URL");
	}
	BOOST_AUTO_TEST_CASE(when_url_is_empty_should_throw_exception)
	{
		ExpectConstructorFailure<std::invalid_argument>("", "Invalid URL");
	}
	BOOST_AUTO_TEST_SUITE(Test_exception_in_components_constructor)
		BOOST_AUTO_TEST_CASE(when_domain_contains_invald_symbols_should_throw_exception)
		{
			ExpectConstructorFailure<std::invalid_argument>("inccorect/domain", "/document", Protocol::HTTP, "There are invalid symbols in domain");
		}
		BOOST_AUTO_TEST_CASE(when_domain_is_empty_should_throw_exception)
		{
			ExpectConstructorFailure<std::invalid_argument>("", "/document", Protocol::HTTP, "Domain cannot be empty");
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(Test_corrects_urls)
	BOOST_AUTO_TEST_CASE(when_url_is_correct_should_parse_without_exception)
	{
		std::string url = "https://stackoverflow.com/questions/325";
		CHttpUrl parsedUrl(url);
		VerifyUrlParsing(url, "stackoverflow.com", "/questions/325", Protocol::HTTPS, 443, parsedUrl);
	}
	BOOST_AUTO_TEST_CASE(when_url_is_without_document_should_parse_empty_document)
	{
		std::string url = "http://vk.com";
		CHttpUrl parsedUrl(url);
		VerifyUrlParsing(url, "vk.com", "/", Protocol::HTTP, 80, parsedUrl);
	}
	BOOST_AUTO_TEST_CASE(when_url_contain_port_in_range_should_parse_correct_url)
	{
		std::string url = "https://www.mysite.com:150/document";
		CHttpUrl parsedUrl(url);
		VerifyUrlParsing(url, "www.mysite.com", "/document", Protocol::HTTPS, 150, parsedUrl);
	}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE(Test_components_constructor)
	BOOST_AUTO_TEST_CASE(when_url_without_protocol_and_port_should_construct_by_default)
	{
		CHttpUrl parsedUrl("context.reverso.net", "/translation");
		VerifyUrlParsing("http://context.reverso.net/translation",
			"context.reverso.net", "/translation", Protocol::HTTP, 80, parsedUrl);
	}
	BOOST_AUTO_TEST_CASE(when_document_without_slash_should_add_slash_to_document)
	{
		CHttpUrl parsedUrl("context.reverso.net", "translation");
		VerifyUrlParsing("http://context.reverso.net/translation",
			"context.reverso.net", "/translation", Protocol::HTTP, 80, parsedUrl);
	}
	BOOST_AUTO_TEST_CASE(when_specified_protocol_should_assign_this_protocol)
	{
		CHttpUrl parsedUrl("context.reverso.net", "translation", Protocol::HTTPS);
		VerifyUrlParsing("https://context.reverso.net/translation",
			"context.reverso.net", "/translation", Protocol::HTTPS, 443, parsedUrl);
	}
	BOOST_AUTO_TEST_CASE(when_specified_port_should_assign_this_port)
	{
		CHttpUrl parsedUrl("context-reverso.net", "translation", Protocol::HTTPS, 333);
		VerifyUrlParsing("https://context-reverso.net/translation",
			"context-reverso.net", "/translation", Protocol::HTTPS, 333, parsedUrl);
	}
	BOOST_AUTO_TEST_CASE(when_document_is_empty_should_add_slash_to_empty_document)
	{
		CHttpUrl parsedUrl("context-reverso.net", "");
		VerifyUrlParsing("http://context-reverso.net/",
			"context-reverso.net", "/", Protocol::HTTP, 80, parsedUrl);
	}
BOOST_AUTO_TEST_SUITE_END()