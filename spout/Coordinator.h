#pragma once
#include"F:\whale_storm\spout\ISpout.h"

namespace whale_storm
{
	namespace spout
	{
		class Coordinator :public ISpout
		{
		public:
			virtual void Open(base::OutputCollector& outputCollector)
			{
				_outputCollector = &outputCollector;
			}

			virtual void Close() {}

			virtual void Execuute() {}

		private:
			base::OutputCollector* _outputCollector;
		};
	}
}