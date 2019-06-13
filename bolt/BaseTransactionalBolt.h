#pragma once

#include"F:\whale_storm\bolt\BaseBatchBolt.h"
#include"F:\whale_storm\bolt\TransactionAttempt.h"

namespace whale_storm
{
	namespace base
	{
		class BatchOutputCollector;
	}

	namespace bolt
	{
		class BAseTransactionalBolt :public BaseBatchBolt
		{
		public:
			virtual void Prepare(base::BatchOutputCollector& collector, TransactionAttempt* attempt) = 0;
			void Prepare(base::BatchOutputCollector& collector, void* id) {
			}
		};
	}
}