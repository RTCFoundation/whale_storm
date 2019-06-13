#pragma once
//消息队列接口

#include<functional>
#include<map>
#include<memory>
#include<string>

namespace whale_storm
{
	namespace message
	{
		class Message;

		class MessageLoop
		{
		public:
			typedef std::function<void(Message*)> MessageHandler;

			MessageLoop();
			MessageLoop(const MessageLoop&) = delete;
			const MessageLoop& operator=(const MessageLoop&) = delete;//每个消息队列都是不可复制的

			template <class ObjectType, class MethodType>  //模板
			void MessageMap(int messageType, ObjectType* self, MethodType method)  
			{
				MessageMap(messageType, std::bind(method, self, std::placeholders::_1));
			}
			void MessageMap(int messageType, MessageHandler handler)//实现某个消息类型与消息处理函数之间的映射关系
			{
				_messageHandler.insert({ messageType,handler });  
			}

			void Run(); //启动消息队列
			void Stop();// 停止消息队列
			void PostMessage(Message* message); //向消息队列投递消息
		private:
			std::map<int, MessageHandler> _messageHandler;
			uint64_t _threadId;
		};
		class MessageLoopManager//解耦合，将1所有的消息队列存在一个映射表中，每个名字就对应一个消息队列
		{
		public:
			static MessageLoopManager& GetInstance()
			{
				static MessageLoopManager manager;
				return manager;    //将该类型实例化，解决初始化依赖项问题
			}
			MessageLoopManager(const MessageLoopManager&) = delete;
			const MessageLoopManager& operator=(const MessageLoopManager&) = delete;

			void Register(const std::string& name, MessageLoop* loop)
			{
				_messageLoops.insert({ name,std::shared_ptr<MessageLoop>(loop) }); //注册消息队列
			}
			void PostMessage(const std::string& name, Message* message)  //传递消息
			{
				auto messageLoopPair = _messageLoops.find(name);
				if (messageLoopPair != _messageLoops.end())
				{
					messageLoopPair->second->PostMessage(message);
				}

			}
		private:
			MessageLoopManager() {}
			std::map<std::string, std::shared_ptr<MessageLoop>> _messageLoops;
		};
	}
}