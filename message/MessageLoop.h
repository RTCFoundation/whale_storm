#pragma once
//��Ϣ���нӿ�

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
			const MessageLoop& operator=(const MessageLoop&) = delete;//ÿ����Ϣ���ж��ǲ��ɸ��Ƶ�

			template <class ObjectType, class MethodType>  //ģ��
			void MessageMap(int messageType, ObjectType* self, MethodType method)  
			{
				MessageMap(messageType, std::bind(method, self, std::placeholders::_1));
			}
			void MessageMap(int messageType, MessageHandler handler)//ʵ��ĳ����Ϣ��������Ϣ������֮���ӳ���ϵ
			{
				_messageHandler.insert({ messageType,handler });  
			}

			void Run(); //������Ϣ����
			void Stop();// ֹͣ��Ϣ����
			void PostMessage(Message* message); //����Ϣ����Ͷ����Ϣ
		private:
			std::map<int, MessageHandler> _messageHandler;
			uint64_t _threadId;
		};
		class MessageLoopManager//����ϣ���1���е���Ϣ���д���һ��ӳ����У�ÿ�����־Ͷ�Ӧһ����Ϣ����
		{
		public:
			static MessageLoopManager& GetInstance()
			{
				static MessageLoopManager manager;
				return manager;    //��������ʵ�����������ʼ������������
			}
			MessageLoopManager(const MessageLoopManager&) = delete;
			const MessageLoopManager& operator=(const MessageLoopManager&) = delete;

			void Register(const std::string& name, MessageLoop* loop)
			{
				_messageLoops.insert({ name,std::shared_ptr<MessageLoop>(loop) }); //ע����Ϣ����
			}
			void PostMessage(const std::string& name, Message* message)  //������Ϣ
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