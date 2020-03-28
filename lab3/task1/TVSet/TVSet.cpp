#include "stdafx.h"
#include "TVSet.h"

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

bool CTVSet::SelectChannel(int channel)
{
	bool isAvailableChannel = (channel >= 1) && (channel <= 99);
	if (isAvailableChannel && m_isOn)
	{
		m_prevChannel = m_selectedChannel;
		m_selectedChannel = channel;
		return true;
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
