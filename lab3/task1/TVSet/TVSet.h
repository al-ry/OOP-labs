#pragma once

class CTVSet
{
public:
	bool IsTurnedOn() const;
	int GetChannel() const;
	void TurnOn();
	void TurnOff();
	bool SelectChannel(int channel);
	bool SelectPreviousChannel();

private:
	int  m_isOn = false;
	int m_selectedChannel = 1;
	int m_prevChannel = m_selectedChannel;
};
