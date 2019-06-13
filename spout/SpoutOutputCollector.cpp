#include"F:\whale_storm\whale_storm.h"

#include"F:\whale_storm\spout\SpoutOutpuCollectort.h"
#include"F:\whale_storm\spout\SpoutExecutor.h"

namespace whale_storm
{
	namespace spout
	{
		void SpoutOutputCollector::RandomDestination()
		{
			_executor->RandomDestination(this);
		}

		void SpoutOutputCollector::GroupDestination()
		{
			_executor->GroupDestination(this, GetGroupField());
		}

		void SpoutOutputCollector::Emit(const base::Values & values, int msgId)
		{
		}
	}
}