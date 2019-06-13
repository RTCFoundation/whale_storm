#pragma once
#include"F:\whale_storm\base\Executor.h"
#include"F:\whale_storm\bolt\IBolt.h"
#include"F:\whale_storm\base\Values.h"

namespace whale_storm
{
	namespace topology
	{
		class ITopology;
	}
	namespace message
	{
		class Message;
		class SupervisorCommander;
	}
	namespace bolt
	{
		class BoltMessageLoop;
		class BoltOutputCollector;

		class BoltExecutor :public base::Executor<bolt::IBolt>
		{
		public:
			BoltExecutor();

			void SetExecutorIndex(int executorIndex) {
				_executorIndex = executorIndex;
			}

			void SendData(const base::Values& values);
			void OnData(whale_storm::message::Message* message);

			void OnCreate() override;
			void OnStop() override;

			void SetCommander(message::SupervisorCommander* commander) {
				_commander = commander;
			}
			void RandomDestination(BoltOutputCollector* outputCollector);
			void GroupDestination(BoltOutputCollector* outputCollector, int fieldIndex);

		private:
			topology::ITopology* _topology;
			message::SupervisorCommander* _commander;
			int _executorIndex;
		};
	}
}