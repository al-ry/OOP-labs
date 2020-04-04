#pragma once

class CTVSet
{
	typedef std::map<int, std::string> ChannelMap;
public:
	bool IsTurnedOn() const;
	int GetChannel() const;
	void TurnOn();
	void TurnOff();
	bool SelectChannel(int channel);
	bool SelectChannel(const std::string &channelName);
	bool SelectPreviousChannel();
	bool SetChannelName(int channel, const std::string &channelName);
	std::string GetChannelName(int channel) const;
	int GetChannelByName(std::string channelName) const;
	bool DeleteChannelName(const std::string& channelName);
	void PrintChannelSet(std::ostream& out);

private:

	auto SearchChannelByName(const std::string &channel) const;
	auto SearchChannelByNumber(int channel) const;
	int m_isOn = false;
	int m_selectedChannel = 1;
	int m_prevChannel = m_selectedChannel;
	ChannelMap m_channelMap;
};
