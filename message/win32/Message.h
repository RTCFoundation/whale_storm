#pragma once
#include<Windows.h>
#include<iostream>
#include<thread>
#include<functional>
#include<map>
#include<cstdint>

class Message
{
public:
	Message(int32_t type) :_type(type) {}

	int32_t GetType() const
	{
		return _type;
	}

	void SetType(int32_t type)
	{
		_type = type;
	}
private:
	int32_t _type;
};

class MessageLoop
{
public:
	typedef std::function<void(Message*)> MessageHandler;

	MessageLoop(const MessageLoop&) = delete;
	const MessageLoop& operator=(const MessageLoop&) = delete;

	template <class ObjectType, class MethodType>  //ģ��
	void MessageMap(int messageType, ObjectType* self, MethodType method)
	{
		MessageMap(messageType, std::bind(method, self, std::placeholders::_1));
	}
	void MessageMap(int messageType, MessageHandler handler)//ʵ��ĳ����Ϣ��������Ϣ��������֮���ӳ���ϵ
	{
		_messageHandler.insert({ messageType,handler });
	}

	void Run()
	{
		MSG msg;

		while (GetMessage(&msg, 0, 0, 0))
		{
			std::cerr << "Recived Message:" << std::endl;
			auto handler = _messageHandler.find(msg.message);

			if (handler != _messageHandler.end())
			{
				handler->second((Message*)(msg.wParam));
			}
			DispatchMessage(&msg);
		}
	}
	void PostMessage(Message* message)
	{
		PostThreadMessage(_threadId, message->GetType(), WPARAM(message), 0);
	}
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