#include "stdafx.h"
#include "../TVSet/TVSet.h"


struct TVSetFixture
{
	CTVSet tv;
};
// Телевизор
BOOST_FIXTURE_TEST_SUITE(TVSet, TVSetFixture)
	// изначально выключен
	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!tv.IsTurnedOn());
	}
	// не может переключать канал в выключенном состоянии
	BOOST_AUTO_TEST_CASE(cant_select_channel_when_turned_off)
	{
		BOOST_CHECK(!tv.SelectChannel(87));
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}

	// может быть включен
	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		tv.TurnOn();
		BOOST_CHECK(tv.IsTurnedOn());
	}
	// изначально отображает 0 канал
	BOOST_AUTO_TEST_CASE(displays_channel_0_by_default)
	{
		BOOST_CHECK_EQUAL(tv.GetChannel(), 0);
	}

	struct when_turned_on_ : TVSetFixture
	{
		when_turned_on_()
		{
			tv.TurnOn();
		}
	};
	// после включения
	BOOST_FIXTURE_TEST_SUITE(when_turned_on, when_turned_on_)
		// отображает канал 1
		BOOST_AUTO_TEST_CASE(displays_channel_one)
		{
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
		}
		// можно выключить
		BOOST_AUTO_TEST_CASE(can_be_turned_off)
		{
			tv.TurnOff();
			BOOST_CHECK(!tv.IsTurnedOn());
		}
		// позволяет выбрать канал от 1 до 99
		BOOST_AUTO_TEST_CASE(can_select_channel_from_1_to_99)
		{
			BOOST_CHECK(tv.SelectChannel(1));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);

			BOOST_CHECK(tv.SelectChannel(99));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 99);

			// Выбираем канал между 1 и 99
			BOOST_CHECK(tv.SelectChannel(42));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 42);

			// При попытке выбрать канал за пределами [1; 99]
			// телевизор не должен менять свой канал
			BOOST_CHECK(!tv.SelectChannel(0));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 42);

			BOOST_CHECK(!tv.SelectChannel(100));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 42);
		}

	    BOOST_AUTO_TEST_CASE(can_select_channel_by_name)
		{
			std::string channelName = "TNT";
			BOOST_CHECK(tv.SetChannelName(10, channelName));
			tv.SelectChannel(19);
			BOOST_CHECK(tv.SelectChannel(channelName));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 10);
		}

		BOOST_AUTO_TEST_CASE(cannot_select_nonexistance_channel_by_name)
		{
			BOOST_CHECK(!tv.SelectChannel('dtv'));
		}
	    BOOST_AUTO_TEST_CASE(can_set_channel_by_name)
		{
			std::string channelName = "TNT";
			BOOST_CHECK(tv.SetChannelName(10, channelName));
		}
		BOOST_AUTO_TEST_CASE(can_get_channel_name)
		{
			std::string channelName = "TNT";
			BOOST_CHECK(tv.SetChannelName(10, channelName));
			BOOST_CHECK_EQUAL(tv.GetChannelName(10), channelName);
		}
		BOOST_AUTO_TEST_CASE(can_get_channel_by_name)
		{
			std::string channelName = "TNT";
			BOOST_CHECK(tv.SetChannelName(10, channelName));
			BOOST_CHECK_EQUAL(tv.GetChannelByName(channelName), 10);
		}
		BOOST_AUTO_TEST_CASE(cannot_set_channel_by_empty_name)
		{
			BOOST_CHECK(!tv.SetChannelName(3, ""));
		}
		BOOST_AUTO_TEST_CASE(cannot_set_channel_with_one_space)
		{
			BOOST_CHECK(!tv.SetChannelName(5, " "));
		}

		BOOST_AUTO_TEST_CASE(can_set_channel_with_extra_spaces)
		{
			std::string channelName = "     Russia    24    ";
			BOOST_CHECK(tv.SetChannelName(8, channelName));
			BOOST_CHECK_EQUAL(tv.GetChannelName(8), "Russia 24");
			
		}
		BOOST_AUTO_TEST_CASE(can_redefine_channel_name)
		{
			BOOST_CHECK(tv.SetChannelName(8, "Discovery"));
			BOOST_CHECK(tv.SetChannelName(5, "Discovery"));
			BOOST_CHECK_EQUAL(tv.GetChannelName(5), "Discovery");

			BOOST_CHECK(tv.GetChannelName(8).empty());
		}

		BOOST_AUTO_TEST_CASE(can_delete_channel_by_name)
		{
			tv.SetChannelName(5, "sts");
			BOOST_CHECK(tv.GetChannelByName("sts"));
			BOOST_CHECK(tv.DeleteChannelName("sts"));
			BOOST_CHECK(!tv.GetChannelByName("sts"));
		}
		BOOST_AUTO_TEST_CASE(can_keep_chosen_channel_after_deleting)
		{
			tv.SetChannelName(5, "sts");
			tv.SelectChannel("sts");
			BOOST_CHECK(tv.DeleteChannelName("sts"));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 5);
		}
		BOOST_AUTO_TEST_CASE(cannot_delete_channel_with_out_name)
		{
			BOOST_CHECK(!tv.DeleteChannelName("sts"));
		}

	BOOST_AUTO_TEST_SUITE_END()

	struct after_subsequent_turning_on_ : when_turned_on_
	{
		after_subsequent_turning_on_()
		{
			tv.SelectChannel(33);
			tv.TurnOff();
			tv.TurnOn();
		}
	};

	// после повторного включения
	BOOST_FIXTURE_TEST_SUITE(after_subsequent_turning_on, after_subsequent_turning_on_)
		// восстанавливает последний выбранный канал
		BOOST_AUTO_TEST_CASE(restores_last_selected_channel)
		{
			BOOST_CHECK_EQUAL(tv.GetChannel(), 33);
		}

		BOOST_AUTO_TEST_CASE(cant_back_to_prev_channel_when_tv_turns_off)
		{
			tv.TurnOff();
			BOOST_CHECK(!tv.SelectPreviousChannel());
		}

		BOOST_AUTO_TEST_CASE(back_to_prev_channel)
		{
			tv.TurnOn();
			tv.SelectChannel(55);
			tv.SelectChannel(88);
			tv.SelectPreviousChannel();
			BOOST_CHECK_EQUAL(tv.GetChannel(), 55);

		}

	BOOST_AUTO_TEST_SUITE_END()

	struct after_subsequent_turning_on_and_setting_name_ : when_turned_on_
	{
		after_subsequent_turning_on_and_setting_name_()
		{
			tv.SetChannelName(1, "first");
			tv.TurnOff();
			tv.TurnOn();
		}
	};


	BOOST_FIXTURE_TEST_SUITE(after_subsequent_turning_on_and_setting_name, after_subsequent_turning_on_and_setting_name_)
		BOOST_AUTO_TEST_CASE(can_get_channel_by_name)
		{
			BOOST_CHECK_EQUAL(tv.GetChannelByName("first"), 1);
		}
		BOOST_AUTO_TEST_CASE(can_get_channel_name)
		{
			BOOST_CHECK_EQUAL(tv.GetChannelName(1), "first");
		}
		BOOST_AUTO_TEST_CASE(can_delete_channel_name)
		{
			BOOST_CHECK(tv.DeleteChannelName("first"));
			BOOST_CHECK(tv.GetChannelName(1).empty());
			BOOST_CHECK(tv.GetChannelByName("first") == 0);
		}
		BOOST_AUTO_TEST_CASE(can_select_channel_by_name)
		{
			BOOST_CHECK(tv.SelectChannel("first"));
			BOOST_CHECK_EQUAL(tv.GetChannel(), 1);
		}
		BOOST_AUTO_TEST_CASE(cant_set_two_channels_by_one_name)
		{
			BOOST_CHECK(tv.SetChannelName(8, "first"));
			BOOST_CHECK(tv.GetChannelName(5).empty());
			BOOST_CHECK_EQUAL(tv.GetChannelByName("first"), 8);
		}
		BOOST_AUTO_TEST_CASE(can_rename_channel)
		{
			BOOST_CHECK(tv.SetChannelName(1, "first channel"));
			BOOST_CHECK_EQUAL(tv.GetChannelName(1), "first channel");
			BOOST_CHECK_EQUAL(tv.GetChannelByName("first channel"), 1);
		}
	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
