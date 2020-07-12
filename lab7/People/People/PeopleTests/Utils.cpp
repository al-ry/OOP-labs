
#include "stdafx.h"
#include "Utils.h"
#include "../People/IPerson.h"
#include "../People/IPupil.h"
#include "../People/ITeacher.h"

void VerifyPerson(const IPerson* person, const std::string& exName, const std::string& exSurname, const std::string& exPatronymic, const std::string& exAddress)
{
	BOOST_CHECK_EQUAL(person->GetName(), exName);
	BOOST_CHECK_EQUAL(person->GetSurname(), exSurname);
	BOOST_CHECK_EQUAL(person->GetPatronymic(), exPatronymic);
	BOOST_CHECK_EQUAL(person->GetAddress(), exAddress);
}
