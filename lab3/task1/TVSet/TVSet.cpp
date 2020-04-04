#include "stdafx.h"
#include "TVSet.h"

std::string DeleteExtraBlanks(std::string channelName)
{
	auto newChannelName = std::regex_replace(channelName, std::regex("[ ]+"), " ");
	boost::trim(newChannelName);
	if (newChannelName == " ")
	{
		newChannelName.clear();
	}
	return newChannelName;
}


auto CTVSet::SearchChannelByNumber(int channel) const
{
	return m_channelMap.find(channel);
}

auto CTVSet::SearchChannelByName(const std::string& channel) const
{
	return std::find_if(m_channelMap.begin(), m_channelMap.end(),
		[=](auto res) { return res.second == channel; });
}

bool CTVSet::IsTurnedOn() const
{
	return m_isOn;
}

int CTVSet::GetChannel() const
{
	return m_isOn ? m_selectedChannel : 0;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

bool IsAvailableChannel(int channel)
{
	return (channel >= 1) && (channel <= 99);
}

bool CTVSet::SelectChannel(int channel)
{
	if (IsAvailableChannel(channel) && m_isOn)
	{
		m_prevChannel = m_selectedChannel;
		m_selectedChannel = channel;
		return true;
	}
	return false;
}

bool CTVSet::SelectChannel(const std::string& channelName)
{
	if (m_isOn)
	{
		auto it = SearchChannelByName(channelName);
		if (it != m_channelMap.end())
		{
			m_selectedChannel = it->first;
			return true;
		}
	}
	return false;
}



bool CTVSet::SelectPreviousChannel()
{
	if (m_isOn)
	{
		m_selectedChannel = m_prevChannel;
		return true;
	}
	return false;
}

bool CTVSet::SetChannelName(int channel, const std::string& channelName)
{
	std::string newChannel = DeleteExtraBlanks(channelName);
	if (IsAvailableChannel(channel) && m_isOn && !newChannel.empty())
	{
		DeleteChannelName(newChannel);
		auto it = SearchChannelByNumber(channel);
		if (it != m_channelMap.end())
		{
			m_channelMap.erase(it);
		}
		m_channelMap.emplace(channel, newChannel);
		return true;
	}
	return false;
}

std::string CTVSet::GetChannelName(int channel) const
{
	std::string channelName;
	if (IsAvailableChannel(channel) && m_isOn)
	{
		auto it = SearchChannelByNumber(channel);
		if (it != m_channelMap.end())
		{
			channelName = it->second;
		}
	}
	return channelName;
}

int CTVSet::GetChannelByName(std::string channelName) const
{
	int channel = 0;
	std::string chName = DeleteExtraBlanks(channelName);
	if (m_isOn)
	{
		auto it = SearchChannelByName(chName);
     	if (it != m_channelMap.end())
		{
			channel = it->first;
		}
	}
	return channel;
}


bool CTVSet::DeleteChannelName(const std::string& channelName)
{
	if (m_isOn)
	{
		auto it = SearchChannelByName(channelName);
		if (it != m_channelMap.end())
		{
			m_channelMap.erase(it);
			return true;
		}
	}
	return false;
}

void CTVSet::PrintChannelSet(std::ostream& out)
{
	for (auto &item : m_channelMap)
	{
		out << item.first << " - " << item.second << std::endl;
	}
}

