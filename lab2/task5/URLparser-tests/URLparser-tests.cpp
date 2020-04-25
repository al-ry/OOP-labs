#include "stdafx.h"
#include "..\URLparser\URLparser.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ParseURL_function)

	Protocol protocol;
	int port;
	string document;
	string host;

	BOOST_AUTO_TEST_SUITE(Check_ParseUrl)
		BOOST_AUTO_TEST_SUITE(when_get_default_url)
			BOOST_AUTO_TEST_CASE(should_parse_url_by_default)
			{
				string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
				ParseURL(url, protocol, port, host, document);
				BOOST_CHECK(protocol == Protocol::HTTP);
				BOOST_CHECK(host == "www.mysite.com");
				BOOST_CHECK(port == 80);
				BOOST_CHECK(document == "docs/document1.html?page=30&lang=en#title");
			}
			BOOST_AUTO_TEST_CASE(should_not_parse_unknown_protocol)
			{
				string url = "pop3://www.mysite.com/docs/document1.html?page=30&lang=en#title";
				BOOST_CHECK(!ParseURL(url, protocol, port, host, document));
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(when_get_url_with_port)
			BOOST_AUTO_TEST_CASE(should_parse_url_with_corresponding_port)
			{
				string url = "http://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
				ParseURL(url, protocol, port, host, document);
				BOOST_CHECK(protocol == Protocol::HTTP);
				BOOST_CHECK(host == "www.mysite.com");
				BOOST_CHECK(port == 8000);
				BOOST_CHECK(document == "docs/document1.html?page=30&lang=en#title");
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Check_Port)
		BOOST_AUTO_TEST_SUITE(when_port_contains_boundary_value)
			BOOST_AUTO_TEST_CASE(should_be_correct_port)
			{
				BOOST_CHECK_EQUAL(ParseURL("http://localhost:1", protocol, port, host, document), true);
				BOOST_CHECK(port == 1);

				BOOST_CHECK_EQUAL(ParseURL("http://localhost:5000", protocol, port, host, document), true);
				BOOST_CHECK(port == 5000);

				BOOST_CHECK_EQUAL(ParseURL("http://localhost:65535", protocol, port, host, document), true);
				BOOST_CHECK(port == 65535);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(when_port_in_range)
			BOOST_AUTO_TEST_CASE(should_be_correct_port)
			{
				BOOST_CHECK_EQUAL(ParseURL("http://localhost:1", protocol, port, host, document), true);
				BOOST_CHECK(port == 1);

				BOOST_CHECK_EQUAL(ParseURL("http://localhost:5000", protocol, port, host, document), true);
				BOOST_CHECK(port == 5000);

				BOOST_CHECK_EQUAL(ParseURL("http://localhost:65535", protocol, port, host, document), true);
				BOOST_CHECK(port == 65535);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(when_protocol_contains_out_of_range_port)
			BOOST_AUTO_TEST_CASE(should_return_that_cannot_parse_url)
			{
				BOOST_CHECK_EQUAL(ParseURL("http://localhost:-1", protocol, port, host, document), false);

				BOOST_CHECK_EQUAL(ParseURL("http://localhost:5000000000", protocol, port, host, document), false);

				BOOST_CHECK_EQUAL(ParseURL("http://localhost:0", protocol, port, host, document), false);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Check_Protocol)
		BOOST_AUTO_TEST_SUITE(when_protocol_contains_upper_and_lower_symbols)
			BOOST_AUTO_TEST_CASE(should_parse_correct_protocol)
			{
				BOOST_CHECK_EQUAL(ParseURL("HTTP://localhost", protocol, port, host, document), true);
				BOOST_CHECK(protocol == Protocol::HTTP);

				BOOST_CHECK_EQUAL(ParseURL("httpS://localhost", protocol, port, host, document), true);
				BOOST_CHECK(protocol == Protocol::HTTPS);

				BOOST_CHECK_EQUAL(ParseURL("FtP://localhost", protocol, port, host, document), true);
				BOOST_CHECK(protocol == Protocol::FTP);
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(when_url_doesnt_contain_port)
			BOOST_AUTO_TEST_CASE(should_parse_url_with_default_port)
			{
				BOOST_CHECK_EQUAL(ParseURL("http://localhost", protocol, port, host, document), true);
				BOOST_CHECK(port == 80);

				BOOST_CHECK_EQUAL(ParseURL("https://localhost", protocol, port, host, document), true);
				BOOST_CHECK(port == 443);

				BOOST_CHECK_EQUAL(ParseURL("ftp://localhost", protocol, port, host, document), true);
				BOOST_CHECK(port == 21);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()