// stdafx.cpp : source file that includes just the standard includes
// Task1Tests.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// Сообщаем библиотеке boost test, что функция main будет предоставлена нами (для предварительного конфигурирования библиотеки),
// а не сгенерирована boost-ом за нас
#define BOOST_TEST_NO_MAIN
// подключаем реализацию boost test
#include <boost/test/included/unit_test.hpp>
