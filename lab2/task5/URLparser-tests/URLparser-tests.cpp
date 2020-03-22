#include "stdafx.h"
#include "..\URLparser\URLparser.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ParseURL_function)

	Protocol protocol;
	int port;
	string document;
	string host;
	BOOST_AUTO_TEST_CASE(check_default_url)
	{
		string url = "http://www.mysite.com/docs/document1.html?page=30&lang=en#title";
		ParseURL(url, protocol, port, host, document);
		BOOST_CHECK(protocol == Protocol::HTTP);
		BOOST_CHECK(host == "www.mysite.com");
		BOOST_CHECK(port == 80);
		BOOST_CHECK(document == "docs/document1.html?page=30&lang=en#title");
	}
	BOOST_AUTO_TEST_CASE(check_url_with_port)
	{
		string url = "http://www.mysite.com:8000/docs/document1.html?page=30&lang=en#title";
		ParseURL(url, protocol, port, host, document);
		BOOST_CHECK(protocol == Protocol::HTTP);
		BOOST_CHECK(host == "www.mysite.com");
		BOOST_CHECK(port == 8000);
		BOOST_CHECK(document == "docs/document1.html?page=30&lang=en#title");
	}
	BOOST_AUTO_TEST_CASE(check_port_range)
	{
		BOOST_CHECK_EQUAL(ParseURL("http://localhost:1", protocol, port, host, document), true);
		BOOST_CHECK(port == 1);

		BOOST_CHECK_EQUAL(ParseURL("http://localhost:5000", protocol, port, host, document), true);
		BOOST_CHECK(port == 5000);

		BOOST_CHECK_EQUAL(ParseURL("http://localhost:65535", protocol, port, host, document), true);
		BOOST_CHECK(port == 65535);
	}

	BOOST_AUTO_TEST_CASE(check_port_in_range)
	{
		BOOST_CHECK_EQUAL(ParseURL("http://localhost:1", protocol, port, host, document), true);
		BOOST_CHECK(port == 1);

		BOOST_CHECK_EQUAL(ParseURL("http://localhost:5000", protocol, port, host, document), true);
		BOOST_CHECK(port == 5000);

		BOOST_CHECK_EQUAL(ParseURL("http://localhost:65535", protocol, port, host, document), true);
		BOOST_CHECK(port == 65535);
	}

	BOOST_AUTO_TEST_CASE(check_port_out_of_range)
	{
		BOOST_CHECK_EQUAL(ParseURL("http://localhost:-1", protocol, port, host, document), false);

		BOOST_CHECK_EQUAL(ParseURL("http://localhost:5000000000", protocol, port, host, document), false);

		BOOST_CHECK_EQUAL(ParseURL("http://localhost:0", protocol, port, host, document), false);
	}

	BOOST_AUTO_TEST_CASE(check_case_insensitive)
	{
		BOOST_CHECK_EQUAL(ParseURL("HTTP://localhost", protocol, port, host, document), true);
		BOOST_CHECK(protocol == Protocol::HTTP);

		BOOST_CHECK_EQUAL(ParseURL("httpS://localhost", protocol, port, host, document), true);
		BOOST_CHECK(protocol == Protocol::HTTPS);

		BOOST_CHECK_EQUAL(ParseURL("FtP://localhost", protocol, port, host, document), true);
		BOOST_CHECK(protocol == Protocol::FTP);
	}

		BOOST_AUTO_TEST_CASE(parse_default_protocol)
	{
		BOOST_CHECK_EQUAL(ParseURL("http://localhost", protocol, port, host, document), true);
		BOOST_CHECK(protocol == Protocol::HTTP);
		BOOST_CHECK(port == 80);

		BOOST_CHECK_EQUAL(ParseURL("https://localhost", protocol, port, host, document), true);
		BOOST_CHECK(protocol == Protocol::HTTPS);
		BOOST_CHECK(port == 443);

		BOOST_CHECK_EQUAL(ParseURL("ftp://localhost", protocol, port, host, document), true);
		BOOST_CHECK(protocol == Protocol::FTP);
		BOOST_CHECK(port == 21);
	}


BOOST_AUTO_TEST_SUITE_END()