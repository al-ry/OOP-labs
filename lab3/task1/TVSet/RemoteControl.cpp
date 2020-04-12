#include "stdafx.h"
#include "RemoteControl.h"
#include "TVSet.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "TurnOn", [this](istream& strm) {
			   return TurnOn(strm);
		   } },
		  { "TurnOff", bind(&CRemoteControl::TurnOff, this, std::placeholders::_1) },
		  { "Info", bind(&CRemoteControl::Info, this, _1) },
		  { "SelectChannel", bind(&CRemoteControl::SelectChannel, this, _1) },
		  { "SelectPreviousChannel", bind(&CRemoteControl::SelectPreviousChannel, this, _1) },
		  { "SetChannelName", bind(&CRemoteControl::SetChannelName, this, _1) },
		  { "DeleteChannelName", bind(&CRemoteControl::DeleteChannelName, this, _1) }
	  })
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CRemoteControl::TurnOn(std::istream& /*args*/)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << endl;
	return true;
}

bool CRemoteControl::TurnOff(std::istream& /*args*/)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << endl;
	return true;
}

bool CRemoteControl::Info(std::istream& /*args*/)
{
	string info = (m_tv.IsTurnedOn())
		? ("TV is turned on\n")
		: "TV is turned off\n";

	m_output << info;
	if (m_tv.IsTurnedOn())
	{
		if (!m_tv.GetChannelName(m_tv.GetChannel()).empty())
		{
			m_output << "Channel is: " + to_string(m_tv.GetChannel()) << " - "
					 << m_tv.GetChannelName(m_tv.GetChannel()) << endl;
		}
		else
		{
			m_output << "Channel is: " + to_string(m_tv.GetChannel()) + "\n";
		}
		m_tv.PrintChannelSet(m_output);
	}

	return true;
}

bool CRemoteControl::SelectChannel(std::istream& args)
{
	string channel;
	getline(args, channel);
	boost::trim(channel);
	int channelNumber = 0;
	if (m_tv.IsTurnedOn())
	{
		if (all_of(channel.begin(), channel.end(), isdigit) && !channel.empty())
		{
			channelNumber = stoi(channel);
		}
		if (m_tv.SelectChannel(channelNumber) || m_tv.SelectChannel(channel))
		{
			m_output << "Channel selected\n";
		}
		else
		{
			m_output << "Invalid channel\n";
		}
	}
	else
	{
		m_output << "Can't select channel because TV is turned off" << endl;
	}
	return true;
}

bool CRemoteControl::SelectPreviousChannel(std::istream&)
{
	if (m_tv.IsTurnedOn())
	{
		m_tv.SelectPreviousChannel();
		m_output << "Previous channel selected."<< endl;
	}
	else
	{
		m_output << "Tv is turned off. Cannot select previous channel." << endl;
	}
	return true;
}

bool CRemoteControl::SetChannelName(std::istream& args)
{
	string channelName;
	int channelNumber;
	if (m_tv.IsTurnedOn())
	{
		args >> channelNumber;
		getline(args, channelName);
		if (m_tv.SetChannelName(channelNumber, channelName))
		{
			m_output << "Channel name has been set" << endl;
		}
		else
		{
			m_output << "Cannot set channel name" << endl;
		}
	}
	else
	{
		m_output << "Can't set channel name because TV is turned off" << endl;
	}
	return true;
}

bool CRemoteControl::DeleteChannelName(std::istream& args)
{
	if (m_tv.IsTurnedOn())
	{
		string deletedChannel;
		getline(args, deletedChannel);
		boost::trim(deletedChannel);
		if (m_tv.DeleteChannelName(deletedChannel))
		{
			m_output << "Channel successfully deleted" << endl;
		}
		else
		{
			m_output << "Channel didn't delete" << endl;
		}
	}
	else
	{
		m_output << "Can't delete channel because TV is turned off" << endl;
	}
	return true;
}