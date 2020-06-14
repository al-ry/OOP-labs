#include "stdafx.h"
#include "../FindMaxEx/FindMaxEx.h"
#include <string>

struct Sportsman
{
	Sportsman()
		: name()
		, height(0.0f)
		, weight(0.0f){};
	Sportsman(std::string name, double height, double weight)
		: name(name)
		, height(height)
		, weight(weight){};
	std::string name;
	double height;
	double weight;
};


class MaxHeightComparator
{
public:
	bool operator()(const Sportsman& fValue, const Sportsman& sValue) const
	{
		return fValue.height < sValue.height;
	}
};

class MaxWeightComparator
{
public:
	bool operator()(const Sportsman& fValue, const Sportsman& sValue) const
	{
		return fValue.weight < sValue.weight;
	}
};

BOOST_AUTO_TEST_SUITE(FindMaxEx_test)
	BOOST_AUTO_TEST_CASE(searching_in_empty_vector)
	{
		std::vector<Sportsman> emptySportsmanVector;
		Sportsman res;
		BOOST_CHECK(!FindMaxEx(emptySportsmanVector, res, MaxHeightComparator()));
		BOOST_CHECK(!FindMaxEx(emptySportsmanVector, res, MaxWeightComparator()));
	}
	BOOST_AUTO_TEST_CASE(searching_in_max_weight_and_max_height_in_vector)
	{
		std::vector<Sportsman> sportsmanVector
		{
			{ "Sergey", 170, 80 },
			{ "Vasiliy", 168, 75 },
			{ "Igor", 150, 65 },
			{ "Maxim", 190, 78 }
		};
		Sportsman res;
		BOOST_CHECK(FindMaxEx(sportsmanVector, res, MaxHeightComparator()));
		BOOST_CHECK(res.name == sportsmanVector.at(3).name);
		BOOST_CHECK(FindMaxEx(sportsmanVector, res, MaxWeightComparator()));
		BOOST_CHECK(res.name == sportsmanVector.at(0).name);
	}
	BOOST_AUTO_TEST_CASE(can_be_found_with_any_type)
	{
		std::vector<const char*> literalsVector = { "Hello", "World", "!"};
		const char* res;
		FindMaxEx(literalsVector, res, [&](const char* str1, const char* str2) {
			if (strcmp(str1, str2) < 0)
			{
				return true;
			}
			return false;
		});
		BOOST_CHECK(res == "World");
	}
BOOST_AUTO_TEST_SUITE_END()