#pragma once

#include"F:\whale_storm\base\Values.h"
#include"F:\whale_storm\base\Fields.h"

namespace whale_storm
{
	namespace base
	{
		class BatchOutputCollector;
	}

	namespace bolt
	{
		class BaseBatchBolt
		{
		private:
			void * _id;
			int _count = 0;
		public:
			virtual void Prepare(base::BatchOutputCollector& collector, void* id) = 0;
			virtual void Execute(const base::Values& values) = 0;
			virtual void FinishBath() = 0;

			virtual base::Fields DeclareOutputFields() = 0;
		};
	}
}