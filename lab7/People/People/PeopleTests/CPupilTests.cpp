#include "stdafx.h"
#include "../People/CPupil.h"
#include "Utils.h"


void VerifyPupil(const IPupil& pupil, const std::string& exSchoolName, const std::string& exGrade)
{
	BOOST_CHECK(pupil.GetSchoolName() == exSchoolName);
	BOOST_CHECK(pupil.GetGrade() == exGrade);
}

struct unknownPupil
{
	CPupil pupil;
};

BOOST_FIXTURE_TEST_SUITE(CPupil_tests, unknownPupil)
	BOOST_AUTO_TEST_CASE(is_a_person)
	{
		BOOST_CHECK(static_cast<const IPerson*>(&pupil));
	}
	BOOST_AUTO_TEST_CASE(is_an_unknown_person)
	{
		VerifyPerson(&pupil, "", "", "", "");
		VerifyPupil(pupil, "", "");
	}
	BOOST_AUTO_TEST_CASE(can_make_pupil_via_constructor)
	{
		CPupil anotherPupil("Vasya", "Vasiviev", "Vasilivich", "Lenina 3", "20" , "1B");
		VerifyPerson(&anotherPupil, "Vasya", "Vasiviev", "Vasilivich", "Lenina 3");
		VerifyPupil(anotherPupil, "20", "1B");
	}

	struct when_set_values_ : unknownPupil
	{
		when_set_values_()
		{
			pupil.SetName("Anton");
			pupil.SetSurname("Pupkin");
			pupil.SetPatronymic("Iliich");
			pupil.SetAddress("Pushkina, 8, 42");
			pupil.SetSchoolName("¹20");
			pupil.SetGrade("8A");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_set_values, when_set_values_)
		BOOST_AUTO_TEST_CASE(can_identify_pupil)
		{
			VerifyPerson(&pupil, "Anton", "Pupkin", "Iliich", "Pushkina, 8, 42");
			VerifyPupil(pupil, "¹20", "8A");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()