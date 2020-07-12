#pragma once
#include <string>
#include "../People/IPerson.h"
#include "../People/IPupil.h"

void VerifyPerson(const IPerson* person, const std::string& exName, const std::string& exSurname
	, const std::string& exPatronymic, const std::string& exAddress);
