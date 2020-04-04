#pragma once
#include <boost/noncopyable.hpp>

class CTVSet;

class CRemoteControl : boost::noncopyable
{
public:
	CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool TurnOn(std::istream& args);
	bool TurnOff(std::istream& args);
	bool Info(std::istream& args);
	bool SelectChannel(std::istream& args);
	bool SelectPreviousChannel(std::istream& args);
	bool SetChannelName(std::istream& args);
	bool DeleteChannelName(std::istream& args);
private:

	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	CTVSet& m_tv;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};
