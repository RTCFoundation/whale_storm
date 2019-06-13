#pragma once
#include"F:\whale_storm\base\ITask.h"

//bolt接口定义

namespace whale_storm
{
	namespace base
	{
		class OutputCollector;
		class Values;
	}
	namespace bolt
	{
		class IBolt :public base::ITask
		{
		public:
			virtual void Prepare(base::OutputCollector& outputCollector) = 0; //在任务启动前对人物对象初始化
			virtual void Cleanup() = 0; //在拓扑结构停止时对任务资源清理
			virtual void Execute(const base::Values& values) = 0;  //被动执行，只有数据到来时才调用

			virtual  IBolt* Clone() const = 0; //复制任务对象
		};
	}
}