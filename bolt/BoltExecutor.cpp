#include"F:\whale_storm\whale_storm.h"
#include"F:\whale_storm\bolt\BoltExecutor.h"
#include"F:\whale_storm\message\MessageLoop.h"
#include"F:\whale_storm\message\SupervisorCommander.h"
#include"F:\whale_storm\bolt\BoltMessage.h"

#include<iostream>
#include<thread>
#include<chrono>

#ifdef WIN32
#ifdef PostMessage
#undef PostMessage
#endif
#endif // 

namespace whale_storm
{
	namespace bolt
	{
		BoltExecutor::BoltExecutor() : base::Executor<bolt::IBolt>() {
			_messageLoop.MessageMap(BoltMessage::MessageType::Data,
				this, &BoltExecutor::OnData);
		}

		void BoltExecutor::SendData(const base::Values& values)  //发送数据
		{
			_messageLoop.PostMessage(new BoltMessage(values));
		}

		void BoltExecutor::OnData(whale_storm::message::Message* message) {  //处理初始化事件
			BoltMessage* boltMessage = dynamic_cast<BoltMessage*>(message);
			_task->Execute(boltMessage->GetValues());

			delete message;
		}

		void BoltExecutor::OnCreate()                //处理初始化事件
		{
			std::cout << "Start Bolt Task" << std::endl;

			if (_task->GetStrategy() == base::ITask::Strategy::Global) {
				BoltOutputCollector outputCollector(GetTaskName(), base::OutputCollector::Strategy::Global, this);
				RandomDestination(&outputCollector);

				_task->Prepare(outputCollector);
			}
		}

		void BoltExecutor::OnStop()     //停止执行消息处理单元
		{
			std::cout << "Stop Bolt Task" << std::endl;

			_task->Cleanup();
		}

		void BoltExecutor::RandomDestination(BoltOutputCollector * outputCollector)  //随机选择数据发送目标
		{
			std::string host;
			int32_t port;
			int32_t destIndex;

			_commander->RandomDestination("bolt", _executorIndex, &host, &port, &destIndex);
			outputCollector->SetCommander(new message::SupervisorCommander(
				base::NetAddress(host, port), _commander->GetSupervisorName()));
			outputCollector->SetTaskIndex(destIndex);
		}

		void BoltExecutor::GroupDestination(BoltOutputCollector * outputCollector, int fieldIndex)//分组选择数据发送目标
		{
			std::string host;
			int32_t port;
			int32_t destIndex;

			_commander->GroupDestination("bolt", _executorIndex,
				&host, &port, &destIndex, fieldIndex);
			outputCollector->SetCommander(new message::SupervisorCommander(
				base::NetAddress(host, port), _commander->GetSupervisorName()));
			outputCollector->SetTaskIndex(destIndex);
		}
	}
}