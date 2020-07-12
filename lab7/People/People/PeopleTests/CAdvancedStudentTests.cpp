#include "stdafx.h"
#include "../People/CAdvancedStudent.h"
#include "Utils.h"

struct unknownAdvancedStudent
{
	CAdvancedStudent advancedStudent;
};

void VerifyAdvancedStudent(const IAdvancedStudent& student,
	const std::string& universityName,
	const std::string& studentCard,
	const std::string& dissertationTopic)
{
	BOOST_CHECK(student.GetUniversityName() == universityName);
	BOOST_CHECK(student.GetStudentCardNumber() == studentCard);
	BOOST_CHECK(student.GetDissertationTopic() == dissertationTopic);
}

BOOST_FIXTURE_TEST_SUITE(CAdvancedStudent_tests, unknownAdvancedStudent)
	BOOST_AUTO_TEST_CASE(is_a_person)
	{
		BOOST_CHECK(static_cast<const IPerson*>(&advancedStudent));
	}
	BOOST_AUTO_TEST_CASE(is_a_student)
	{
		BOOST_CHECK(static_cast<const IStudent*>(&advancedStudent));
	}
	BOOST_AUTO_TEST_CASE(is_an_unknown_person)
	{
		VerifyPerson(&advancedStudent, "", "", "", "");
		VerifyAdvancedStudent(advancedStudent, "", "", "");
	}
	BOOST_AUTO_TEST_CASE(can_make_advanced_student_via_constructor)
	{
		CAdvancedStudent anotherStudent("Vasya", "Vasiviev", "Vasilivich", "Lenina 3", "mgu", "555123", "topic");
		VerifyPerson(&anotherStudent, "Vasya", "Vasiviev", "Vasilivich", "Lenina 3");
		VerifyAdvancedStudent(anotherStudent, "mgu", "555123", "topic");
	}

	struct when_set_values_ : unknownAdvancedStudent
	{
		when_set_values_()
		{
			advancedStudent.SetName("Anton");
			advancedStudent.SetSurname("Pupkin");
			advancedStudent.SetPatronymic("Iliich");
			advancedStudent.SetAddress("Pushkina, 8, 42");
			advancedStudent.SetUniversityName("Volgatech");
			advancedStudent.SetStudentCardNumber("12345678");
			advancedStudent.SetDissertationTopic("new topic");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_set_values, when_set_values_)
		BOOST_AUTO_TEST_CASE(can_identify_advanced_student)
		{
			VerifyPerson(&advancedStudent, "Anton", "Pupkin", "Iliich", "Pushkina, 8, 42");
			VerifyAdvancedStudent(advancedStudent, "Volgatech", "12345678", "new topic");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()