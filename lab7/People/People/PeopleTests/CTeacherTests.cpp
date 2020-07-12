#include "stdafx.h"
#include "../People/CTeacher.h"
#include "Utils.h"

struct unknownTeacher
{
	CTeacher teacher;
};

void VerifyTeacher(const ITeacher& teacher, const std::string& subject)
{
	BOOST_CHECK(teacher.GetSubject() == subject);
}

BOOST_FIXTURE_TEST_SUITE(CTeacher_tests, unknownTeacher)
	BOOST_AUTO_TEST_CASE(is_a_person)
	{
		BOOST_CHECK(static_cast<const IPerson*>(&teacher));
	}
	BOOST_AUTO_TEST_CASE(is_an_unknown_person)
	{
		VerifyPerson(&teacher, "", "", "", "");
		VerifyTeacher(teacher, "");
	}
	BOOST_AUTO_TEST_CASE(can_make_teacher_via_constructor)
	{
		CTeacher anotherTeacher("Vasya", "Vasiviev", "Vasilivich", "Lenina 3", "OBJ");
		VerifyPerson(&anotherTeacher, "Vasya", "Vasiviev", "Vasilivich", "Lenina 3");
		VerifyTeacher(anotherTeacher, "OBJ");
	}

	struct when_set_values_ : unknownTeacher
	{
		when_set_values_()
		{
			teacher.SetName("Anton");
			teacher.SetSurname("Pupkin");
			teacher.SetPatronymic("Iliich");
			teacher.SetAddress("Pushkina, 8, 42");
			teacher.SetSubject("Informatika");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_set_values, when_set_values_)
		BOOST_AUTO_TEST_CASE(can_identify_teacher)
		{
			VerifyPerson(&teacher, "Anton", "Pupkin", "Iliich", "Pushkina, 8, 42");
			VerifyTeacher(teacher, "Informatika");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()