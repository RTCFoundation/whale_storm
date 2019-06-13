#pragma once
#include"F:\whale_storm\spout\ISpout.h"
#include"F:\whale_storm\base\Executor.h"

#include<iostream>

namespace whale_storm
{
	namespace topology
	{
		class ITopology;
	}
	namespace message
	{
		class SupervisorCommander;
	}
	namespace spout
	{
		class SpoutOutputCollector;

		class SpoutExecutor :public base::Executor<spout::ISpout>
		{
		public:
			SpoutExecutor() :base::Executor<spout::ISpout>(), _needToStop(false) {

			}

			void StopTask() override;
			void OnCreate();            //??£¿£¿£¿£¿£¿£¿£¿£¿£¿£¿£¿
			void OnStop() override;

			void SetExecutorIndex(int excutorIndex)
			{
				_executorIndex = excutorIndex;
			}
			void SetCommander(message::SupervisorCommander* commander);
			void RandomDestination(SpoutOutputCollector* outputCollector);
			void GroupDestination(SpoutOutputCollector* outputCollector, int fieldIndex);

		private:
			topology::ITopology* _topology;
			bool _needToStop;
			message::SupervisorCommander* _commander;
			int _executorIndex;
		};
	}
}
