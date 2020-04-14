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
	void GetChannelName(const string& command)
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
		BOOST_AUTO_TEST_SUITE(Test_Turn_command)
			BOOST_AUTO_TEST_CASE(can_handle_TurnOn_command)
			{
				VerifyCommandHandling("TurnOn", 1, "TV is turned on\n");
			}

			BOOST_AUTO_TEST_CASE(can_turn_off_tv_which_is_on)
			{
				tv.TurnOn();
				VerifyCommandHandling("TurnOff", none, "TV is turned off\n");
			}
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(Test_Info_command)
			BOOST_AUTO_TEST_CASE(can_print_tv_info)
			{
				// Ожидаемое поведение команды Info, вызванной у выключенного телевизора
				VerifyCommandHandling("Info", none, "TV is turned off\n");

				// Проверяем поведение команды Info у включенного телевизора
				tv.TurnOn();
				tv.SelectChannel(42);
				VerifyCommandHandling("Info", 42, "TV is turned on\nChannel is: 42\n");
			}
			BOOST_AUTO_TEST_CASE(can_print_tv_info_with_channel_set)
			{
				tv.TurnOn();
				tv.SelectChannel(42);
				tv.SetChannelName(1, "first");
				tv.SetChannelName(15, "tv3 channel");
				VerifyCommandHandling("Info", 42, "TV is turned on\nChannel is: 42\n1 - first\n15 - tv3 channel\n");
			}
			BOOST_AUTO_TEST_CASE(can_print_selected_channel_with_name)
			{
				tv.TurnOn();
				tv.SetChannelName(1, "first");
				tv.SelectChannel("first");
				VerifyCommandHandling("Info", 1, "TV is turned on\nChannel is: 1 - first\n1 - first\n");
			}

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE(Test_SetChannelName_command)
			BOOST_AUTO_TEST_CASE(cannot_set_channel_name_when_tv_is_off)
			{
				VerifyCommandHandling("SetChannelName 2 first", none, "Can't set channel name because TV is turned off\n");
				tv.TurnOn();
			}
			BOOST_AUTO_TEST_CASE(can_set_channel_name_when_tv_is_on)
			{
				tv.TurnOn();
				VerifyCommandHandling("SetChannelName 2 first", 1, "Channel name has been set\n");
				BOOST_CHECK_EQUAL(tv.GetChannelName(2), "first");

			}
			BOOST_AUTO_TEST_CASE(can_set_channel_name_with_extra_spaces_when_tv_is_on)
			{
				tv.TurnOn();
				VerifyCommandHandling("SetChannelName 2      first    ", 1, "Channel name has been set\n");
				BOOST_CHECK_EQUAL(tv.GetChannelName(2), "first");
			}
			BOOST_AUTO_TEST_CASE(can_set_channel_name_with_few_words_when_tv_is_on)
			{
				tv.TurnOn();
				VerifyCommandHandling("SetChannelName 2 first channel", 1, "Channel name has been set\n");
				BOOST_CHECK_EQUAL(tv.GetChannelName(2), "first channel");
			}
			BOOST_AUTO_TEST_CASE(can_set_channel_name_with_few_words_and_extra_spaces_when_tv_is_on)
			{
				tv.TurnOn();
				VerifyCommandHandling("SetChannelName 2    first    channel  ", 1, "Channel name has been set\n");
				BOOST_CHECK_EQUAL(tv.GetChannelName(2), "first channel");
			}
			BOOST_AUTO_TEST_CASE(can_set_channel_name_when_channel_name_is_number_and_when_tv_is_on)
			{
				tv.TurnOn();
				VerifyCommandHandling("SetChannelName 2    5", 1, "Channel name has been set\n");
				BOOST_CHECK_EQUAL(tv.GetChannelName(2), "5");
			}
			BOOST_AUTO_TEST_CASE(cannot_set_channel_name_to_out_of_range_number)
			{
				tv.TurnOn();
				VerifyCommandHandling("SetChannelName 100 channel", 1, "Cannot set channel name\n");
			}

		BOOST_AUTO_TEST_SUITE_END()

		struct when_there_are_channels_set_ : RemoteControlFixture
		{
			when_there_are_channels_set_()
			{
				tv.TurnOn();
				tv.SetChannelName(5, "Discovery channel");
				tv.SetChannelName(1, "first");
				tv.SetChannelName(17, "MTV");
			}
		};

		BOOST_AUTO_TEST_SUITE(Test_SelectChannel_command)
			BOOST_AUTO_TEST_SUITE(SelectChannel_by_number_command)
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
			BOOST_AUTO_TEST_SUITE_END()

			BOOST_FIXTURE_TEST_SUITE(SelectChannel_by_name_command, when_there_are_channels_set_)
				BOOST_AUTO_TEST_CASE(can_select_channel_by_name)
				{
					VerifyCommandHandling("SelectChannel MTV", 17, "Channel selected\n");
					VerifyCommandHandling("SelectChannel  Discovery channel", 5, "Channel selected\n");
				}
				BOOST_AUTO_TEST_CASE(can_select_channel_with_unknown_name)
				{
					VerifyCommandHandling("SelectChannel STS", 1, "Invalid channel\n");
				}
			BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE_END()

		BOOST_FIXTURE_TEST_SUITE(Test_DeleteChannelName_command, when_there_are_channels_set_)
			BOOST_AUTO_TEST_CASE(can_delete_channel_contains_few_word_from_channel_set)
			{
				VerifyCommandHandling("DeleteChannelName Discovery channel", 1, "Channel successfully deleted\n");

			}
			BOOST_AUTO_TEST_CASE(can_delete_channel_contains_one_word_from_channel_set)
			{
				VerifyCommandHandling("DeleteChannelName MTV", 1, "Channel successfully deleted\n");
			}
			BOOST_AUTO_TEST_CASE(cannot_delete_unknown_channel_from_channel_set)
			{
				VerifyCommandHandling("DeleteChannelName TV3", 1, "Channel didn't delete\n");
			}
			BOOST_AUTO_TEST_CASE(cannot_delete_channel_when_tv_is_off)
			{
				tv.TurnOff();
				VerifyCommandHandling("DeleteChannelName Discovery channel", none, "Can't delete channel because TV is turned off\n");
				tv.TurnOn();
			}
		BOOST_AUTO_TEST_SUITE_END()
		BOOST_AUTO_TEST_SUITE(Test_SelectPreviousChannel_command)
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

BOOST_AUTO_TEST_SUITE_END()