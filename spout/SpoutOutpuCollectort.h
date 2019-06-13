#pragma once
#include"F:\whale_storm\base\OutputCollector.h"
#include"F:\whale_storm\base\Values.h"
namespace whale_storm
{
	namespace spout
	{
		class SpoutExecutor;

		class SpoutOutputCollector :public base::OutputCollector
		{
		public:
			SpoutOutputCollector(const std::string& src,int strategy,SpoutExecutor* exector):
				base::OutputCollector(src, strategy), _executor(exector) {}

			virtual void RandomDestination() override;
			virtual void GroupDestination() override;
			void Emit(const base::Values& values, int msgId);
		private:
			SpoutExecutor* _executor;
		};
	}
}