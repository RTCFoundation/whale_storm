#pragma once
#include<iostream>
#include"F:\whale_storm\base\Values.h"
#include"F:\whale_storm\message\SupervisorCommander.h"
//数据收集器，进行数据传输


namespace whale_storm
{
	namespace topology
	{
		class ITopology;
	}
	namespace base
	{
		class OutputCollector
		{
		public:
			struct Strategy  //数据发送策略
			{
				enum Values
				{
					Global = 0, //全局发送
					Random = 1,  //随即发生
					Group=2       //分组发送
				};
			};
			OutputCollector(const std::string& src, int strategy) :_src(src), _strategy(strategy),
				_commander(nullptr) {}  
			virtual void Emit(const Values& values);  //发送元组
			void SetCommander(whale_storm::message::SupervisorCommander* commander)
			{                                 //设置一个命令执行器
				if (_commander)
				{
					delete _commander;
				}
				_commander = commander;
			}
			void SetTaskIndex(int taskIndex)   //每次发送元组时目的地的编号
			{
				_taskIndex = taskIndex;
			}
			void SetGroupField(int groupField)
			{
				_groupField = groupField;    //分组策略根据此将数据发送给固定的数据处理单元
			}
			int GetGroupField() const
			{
				return _groupField;      //获得分组编号字段
			}
			int GetStrategy() const
			{
				return _strategy;  //
			}
			virtual void RandomDestination() {};  //随机策略中实现随机选择目的消息处理单元
			virtual void GroupDestination() {};  //根据字段选择元组发送的目标消息处理单元
		private:
			std::string _src;  //消息来源任务名称
			int _strategy;     //消息发送策略
			int _taskIndex;    //目标任务标号
			whale_storm::message::SupervisorCommander* _commander;  //命令发送器，默认为空指针
			int _groupField; //制定分组的字段编号
		};
	}
}