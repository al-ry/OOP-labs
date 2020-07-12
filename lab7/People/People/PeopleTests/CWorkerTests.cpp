#include "stdafx.h"
#include "../People/CWorker.h"
#include "Utils.h"

struct unknownWorker
{
	CWorker worker;
};

void VerifyWorker(const IWorker& worker, const std::string& specialization)
{
	BOOST_CHECK(worker.GetSpecialization() == specialization);
}

BOOST_FIXTURE_TEST_SUITE(CWorker_tests, unknownWorker)
	BOOST_AUTO_TEST_CASE(is_a_person)
	{
		BOOST_CHECK(static_cast<const IPerson*>(&worker));
	}
	BOOST_AUTO_TEST_CASE(is_an_unknown_person)
	{
		VerifyPerson(&worker, "", "", "", "");
		VerifyWorker(worker, "");
	}
	BOOST_AUTO_TEST_CASE(can_make_worker_via_constructor)
	{
		CWorker anotherWorker("Vasya", "Vasiviev", "Vasilivich", "Lenina 3", "Tester");
		VerifyPerson(&anotherWorker, "Vasya", "Vasiviev", "Vasilivich", "Lenina 3");
		VerifyWorker(anotherWorker, "Tester");
	}

	struct when_set_values_ : unknownWorker
	{
		when_set_values_()
		{
			worker.SetName("Anton");
			worker.SetSurname("Pupkin");
			worker.SetPatronymic("Iliich");
			worker.SetAddress("Pushkina, 8, 42");
			worker.SetSpecialization("Programmer");
		}
	};
	BOOST_FIXTURE_TEST_SUITE(when_set_values, when_set_values_)
		BOOST_AUTO_TEST_CASE(can_identify_worker)
		{
			VerifyPerson(&worker, "Anton", "Pupkin", "Iliich", "Pushkina, 8, 42");
			VerifyWorker(worker, "Programmer");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()