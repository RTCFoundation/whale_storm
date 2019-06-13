#pragma once

#include"F:\whale_storm\bolt\IBolt.h"

namespace whale_storm
{
	namespace bolt
	{
		class Emitter :public IBolt
		{
		public:
			virtual void Prepare(base::OutputCollector& outputCollector)
			{
				_outputCollector = &outputCollector;
			}

			virtual void Cleanup() {}

			virtual void Execute(const base::Values& values) {}
		private:
			base::OutputCollector* _outputCollector;
		};
	}
}