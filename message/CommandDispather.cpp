#include"F:\whale_storm\message\CommandDispather.h"

#include"F:\whale_storm\whale_storm.h"

namespace whale_storm
{
	namespace message
	{
		void CommandDispatcher::Dispatch(const Command& command)
		{
			Handler handler = _handler[command.GetType()];
			handler(command.GetArgs(), command.GetSrc());
		}
	}
}