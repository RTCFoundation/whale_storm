#pragma once

//事件循环接口实现
#include"F:\whale_storm\dep\loop.h"
#include<memory>

namespace meshy
{
	class EventQueue;

	class BaseEvent;

	class EventQueueLoop :public Loop
	{
	public:
		EventQueueLoop(EventQueue* queue);

	protected:

		virtual void _Run();

		virtual void OnEvent(std::shared_ptr<BaseEvent> event) = 0;

	private:
		EventQueue *_queue;
	};
}