#pragma once
#include"F:\whale_storm\base\OutputCollector.h"
#include"F:\whale_storm\base\Values.h"

namespace whale_storm
{
	namespace bolt
	{
		class BoltExecutor;

		class BoltOutputCollector :public base::OutputCollector
		{
		public:
			BoltOutputCollector(const std::string& src,int strategy,BoltExecutor* executor):
				base::OutputCollector(src, strategy), _executor(executor) {}

			virtual void RandomDestination() override;
			virtual void GroupDestination() override;

			void Ack(const base::Values& values);  //回复元组处理成功
			void Fail(const base::Values& values);  //回复处理失败

		private:
			BoltExecutor* _executor;
		};
	}
}