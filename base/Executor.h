#pragma once
#include"F:\whale_storm\message\MessageLoop.h"
#include"F:\whale_storm\base\ITask.h"

#include<thread>
#include<memory>
#include<vector>
#include<iostream>
#include<mutex>
#include<functional>

namespace whale_storm
{
	namespace base
	{
		template<class TaskType>
		class Executor
		{
			public:
				enum class Status  //表示执行器状态
				{
					Stopping,
					Running
				};
				Executor() :_status(Status::Stopping) {}
				virtual ~Executor() {}

				void StartTask(const std::string& taskName, TaskType* task)  //负责启动任务
				{
					_messageLoop.MessageMap(BoltMessage::MEssageType::Data, this, &BoltMessageLoop::OnData);
					_taskName = taskName;
					_task = task;

					_thread = std::thread(std::bind(&Executor::StartThread, this));
				}
				virtual void StopTask()
				{
					_messageLoop.Stop();
				}
				Status GetStatus() const
				{
					return _status;
				}
				const std::string& GetTaskName() const
				{
					return _taskName;
				}
		protected:
			virtual void OnCreate() = 0;
			virtual void OnStop() = 0;
			std::shared_ptr<TaskType> _task;
			whale_storm::message::MessageLoop _messageLoop;
		private:
			std::thread _thread;
			Status _status;
			std::string _taskName;
			void StartThread()     
			{
				_status = Status::Running;   //设置任务状态

				OnCreate();    //初始化任务执行器
				_messageLoop.Run();  //执行任务
				OnStop();  //停止
				
				_status = Status::Stopping;
			}
		};
	}
}