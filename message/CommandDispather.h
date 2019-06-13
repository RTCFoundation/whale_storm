#pragma once

#include"F:\whale_storm\spout\Command.h"
#include<map>
#include<functional>

namespace meshy
{
	class TcpConnection;
}

namespace whale_storm
{
	namespace message
	{
		class CommandDispatcher
		{
		public:
			typedef std::function<void(whale_storm::base::Variants args, std::shared_ptr<meshy::TcpConnection> src)> Handler;

			CommandDispatcher& OnCommand(Command::Type::Values type, Handler handler)
			{
				_handler[type] = handler;

				return *this;
			}

			void Dispatch(const Command& command);

		private:
			std::map<Command::Type::Values, Handler> _handler;
		};
	}
}