#include"F:\whale_storm\whale_storm.h"

#include"F:\whale_storm\message\MessageLoop.h"
#include"F:\whale_storm\message\Message.h"

#include<Windows.h>
// Because Windows defined the PostMessage Macro
// So we must undefine it to disable compiler convert PostMessage to PostMessageA/PostMessageW
#ifdef PostMessage
#undef PostMessage
#endif

namespace whale_storm
{
	namespace message
	{
		MessageLoop::MessageLoop()
		{
			_threadId = GetCurrentThreadId();
		}

		void MessageLoop::Run()
		{
			MSG msg;

			while (GetMessage(&msg, 0, 0, 0))
			{
				auto handler = _messageHandler.find(msg.message);

				if (handler != _messageHandler.end())
				{
					handler->second((Message*)(msg.wParam));
				}

				DispatchMessage(&msg);

				if (msg.message == Message::Type::stop)
				{
					break;
				}
			}
		}

		void MessageLoop::PostMessage(Message* message)
		{
			PostThreadMessage(_threadId, message->GetType(), WPARAM(message), 0);
		}

		void MessageLoop::Stop()
		{
			PostMessage(new Message(Message::Type::stop));
		}
	}
}