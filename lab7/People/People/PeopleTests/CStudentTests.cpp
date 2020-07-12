#include "stdafx.h"
#include "../People/CStudent.h"
#include "Utils.h"

struct unknownStudent
{
	CStudent student;
};

void VerifyStudent(const IStudent& student, const std::string& universityName, const std::string& studentCard)
{
	BOOST_CHECK(student.GetUniversityName() == universityName);
	BOOST_CHECK(student.GetStudentCardNumber() == studentCard);
}

BOOST_FIXTURE_TEST_SUITE(CStudent_tests, unknownStudent)
	BOOST_AUTO_TEST_CASE(is_a_person)
	{
		BOOST_CHECK(static_cast<const IPerson*>(&student));
	}
	BOOST_AUTO_TEST_CASE(is_an_unknown_person)
	{
		VerifyPerson(&student, "", "", "", "");
		VerifyStudent(student, "", "");
	}
	BOOST_AUTO_TEST_CASE(can_make_student_via_constructor)
	{
		CStudent anotherStudent("Vasya", "Vasiviev", "Vasilivich", "Lenina 3", "mgu", "555123");
		VerifyPerson(&anotherStudent, "Vasya", "Vasiviev", "Vasilivich", "Lenina 3");
		VerifyStudent(anotherStudent, "mgu", "555123");
	}

	struct when_set_values_ : unknownStudent
	{
		when_set_values_()
		{
			student.SetName("Anton");
			student.SetSurname("Pupkin");
			student.SetPatronymic("Iliich");
			student.SetAddress("Pushkina, 8, 42");
			student.SetUniversityName("Volgatech");
			student.SetStudentCardNumber("12345678");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_set_values, when_set_values_)
		BOOST_AUTO_TEST_CASE(can_identify_student)
		{
			VerifyPerson(&student, "Anton", "Pupkin", "Iliich", "Pushkina, 8, 42");
			VerifyStudent(student, "Volgatech", "12345678");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()