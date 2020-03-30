#include "stdafx.h"
#include "../TVSet/RemoteControl.h"
#include "../TVSet/TVSet.h"
#include <boost/optional.hpp>
#include <sstream>

using namespace std;
using boost::none;
using boost::optional;

// Зависимости RemoteControl-а вынесены в родительскую структуру,
// чтобы гарантировать их создание до конструирования самого remote-контрола
struct RemoteControlDependencies
{
	CTVSet tv;
	stringstream input;
	stringstream output;
};

struct RemoteControlFixture : RemoteControlDependencies
{
	CRemoteControl remoteControl;

	RemoteControlFixture()
		: remoteControl(tv, input, output)
	{
	}

	// Вспомогательная функция для проверки работы команды command
	// Она принимает ожидаемый номер канала expectedChannel и expectedOutput
	void VerifyCommandHandling(const string& command, const optional<int>& expectedChannel, const string& expectedOutput)
	{
		// Предварительно очищаем содержимое выходного потока
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK_EQUAL(tv.IsTurnedOn(), expectedChannel.is_initialized());
		BOOST_CHECK_EQUAL(tv.GetChannel(), expectedChannel.get_value_or(0));
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	void GetCommand(const string& command)
	{
		output = stringstream();
		input = stringstream();
		input << command;
	}
};

BOOST_FIXTURE_TEST_SUITE(Remote_Control, RemoteControlFixture)

	BOOST_AUTO_TEST_SUITE(HandlCommand_function)

		BOOST_AUTO_TEST_CASE(Verify_TurnOn_command)
		{
			GetCommand("TurnOn");
			BOOST_CHECK_EQUAL(remoteControl.HandleCommand(), true);
		}
		BOOST_AUTO_TEST_CASE(Verify_TurnOff_command)
		{
			GetCommand("TurnOff");
			BOOST_CHECK_EQUAL(remoteControl.HandleCommand(), true);
		}
		BOOST_AUTO_TEST_CASE(Verify_Info_command)
		{
			GetCommand("Info");
			BOOST_CHECK_EQUAL(remoteControl.HandleCommand(), true);
		}
		BOOST_AUTO_TEST_CASE(Verify_SelectChannel_command)
		{
			GetCommand("SelectChannel");
			BOOST_CHECK_EQUAL(remoteControl.HandleCommand(), true);
		}
		BOOST_AUTO_TEST_CASE(Verify_SelectChannel_with_some_channel_command)
		{
			GetCommand("SelectChannel 20");
			BOOST_CHECK_EQUAL(remoteControl.HandleCommand(), true);
		}
		BOOST_AUTO_TEST_CASE(Verify_SelectPreviousChannel_command)
		{
			GetCommand("SelectPreviousChannel");
			BOOST_CHECK_EQUAL(remoteControl.HandleCommand(), true);
		}
		BOOST_AUTO_TEST_CASE(Cannot_verify_SwitchChannel_command)
		{
			GetCommand("SwitchChannel");
			BOOST_CHECK_EQUAL(remoteControl.HandleCommand(), false);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Test_Commands)

		BOOST_AUTO_TEST_CASE(can_handle_TurnOn_command)
		{
			VerifyCommandHandling("TurnOn", 1, "TV is turned on\n");
		}

		BOOST_AUTO_TEST_CASE(can_turn_off_tv_which_is_on)
		{
			tv.TurnOn();
			VerifyCommandHandling("TurnOff", none, "TV is turned off\n");
		}

		BOOST_AUTO_TEST_CASE(can_print_tv_info)
		{
			// Ожидаемое поведение команды Info, вызванной у выключенного телевизора
			VerifyCommandHandling("Info", none, "TV is turned off\n");

			// Проверяем поведение команды Info у включенного телевизора
			tv.TurnOn();
			tv.SelectChannel(42);
			VerifyCommandHandling("Info", 42, "TV is turned on\nChannel is: 42\n");
		}

		BOOST_AUTO_TEST_CASE(can_select_a_valid_channel_when_tv_which_is_on)
		{
			tv.TurnOn();
			VerifyCommandHandling("SelectChannel 42", 42, "Channel selected\n");
		}

		BOOST_AUTO_TEST_CASE(cant_select_channel_when_tv_is_turned_off)
		{
			VerifyCommandHandling("SelectChannel 42", none, "Can't select channel because TV is turned off\n");
			VerifyCommandHandling("SelectChannel 100", none, "Can't select channel because TV is turned off\n");
		}

		BOOST_AUTO_TEST_CASE(cant_select_an_invalid_channel_when_tv_is_on)
		{
			tv.TurnOn();
			tv.SelectChannel(42);
			VerifyCommandHandling("SelectChannel 100", 42, "Invalid channel\n");
			VerifyCommandHandling("SelectChannel 0", 42, "Invalid channel\n");
		}

		BOOST_AUTO_TEST_CASE(cant_back_to_prev_channel_when_turned_off)
		{
			VerifyCommandHandling("SelectPreviousChannel", none, "Tv is turned off. Cannot select previous channel.\n");
		}

		BOOST_AUTO_TEST_CASE(can_back_to_prev_channel_when_turned_on)
		{
			tv.TurnOn();
			tv.SelectChannel(20);
			tv.SelectChannel(30);
			VerifyCommandHandling("SelectPreviousChannel", 20, "Previous channel selected.\n");
			VerifyCommandHandling("Info", 20, "TV is turned on\nChannel is: 20\n");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()