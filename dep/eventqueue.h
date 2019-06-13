#pragma once

//�¼�ѭ������
#include"F:\whale_storm\dep\bytearray.h"
#include<vector>
#include<string>
#include<mutex>
#include<chrono>
#include<memory>
#include<condition_variable>

namespace meshy
{
	class IStream;

	class BaseEvent
	{
	public:
		BaseEvent() {}

		BaseEvent(const std::string& type, const ByteArray& data, IStream* stream) :
			_type(type), _data(data), _stream(stream) {}

		void SetData(const ByteArray& data)
		{
			_data = data;
		}

		const ByteArray& GetData() const
		{
			return _data;
		}

		void SetType(const std::string &type)
		{
			_type = type;
		}

		const std::string &GetType() const
		{
			return _type;
		}

		void SetStream(IStream *stream)
		{
			_stream = stream;
		}

		IStream *GetStream() const
		{
			return _stream;
		}
	private:
		std::string _type;
		ByteArray _data;
		IStream* _stream;
	};

	class EventQueue
	{
	public:
		EventQueue(int timeout = 0) :_timeout(timeout) {}

		void PostEvent(BaseEvent* event)  //���¼������¼�������
		{
			std::unique_lock<std::mutex> locker(_mutex);

			_events.push_back(std::shared_ptr<BaseEvent>(event));
		}

		std::shared_ptr<BaseEvent> GetEvent()
		{
			std::unique_lock<std::mutex> locker(_mutex);

			if (_events.empty())   //�ж϶����Ƿ���Ԫ��
			{
				if (_timeout == 0)
					return nullptr;
				  //Ϊ�������������ϵȴ�
				_waitCondition.wait_for(locker, std::chrono::milliseconds(_timeout));
				//��ʱ�����ƣ�����ĳ��ʱ�����ٵȴ���ֱ�ӷ���
			}
			if (!_events.empty())
			{
				std::shared_ptr<BaseEvent> event = _events.front();
				_events.erase(_events.begin());

				return event;
			}

			return nullptr;
		}
	private:
		std::vector<std::shared_ptr<BaseEvent>> _events;
		std::mutex _mutex;
		std::condition_variable _waitCondition;
		int _timeout;
	};
}