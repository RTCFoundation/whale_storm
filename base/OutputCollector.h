#pragma once
#include<iostream>
#include"F:\whale_storm\base\Values.h"
#include"F:\whale_storm\message\SupervisorCommander.h"
//�����ռ������������ݴ���


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
			struct Strategy  //���ݷ��Ͳ���
			{
				enum Values
				{
					Global = 0, //ȫ�ַ���
					Random = 1,  //�漴����
					Group=2       //���鷢��
				};
			};
			OutputCollector(const std::string& src, int strategy) :_src(src), _strategy(strategy),
				_commander(nullptr) {}  
			virtual void Emit(const Values& values);  //����Ԫ��
			void SetCommander(whale_storm::message::SupervisorCommander* commander)
			{                                 //����һ������ִ����
				if (_commander)
				{
					delete _commander;
				}
				_commander = commander;
			}
			void SetTaskIndex(int taskIndex)   //ÿ�η���Ԫ��ʱĿ�ĵصı��
			{
				_taskIndex = taskIndex;
			}
			void SetGroupField(int groupField)
			{
				_groupField = groupField;    //������Ը��ݴ˽����ݷ��͸��̶������ݴ���Ԫ
			}
			int GetGroupField() const
			{
				return _groupField;      //��÷������ֶ�
			}
			int GetStrategy() const
			{
				return _strategy;  //
			}
			virtual void RandomDestination() {};  //���������ʵ�����ѡ��Ŀ����Ϣ����Ԫ
			virtual void GroupDestination() {};  //�����ֶ�ѡ��Ԫ�鷢�͵�Ŀ����Ϣ����Ԫ
		private:
			std::string _src;  //��Ϣ��Դ��������
			int _strategy;     //��Ϣ���Ͳ���
			int _taskIndex;    //Ŀ��������
			whale_storm::message::SupervisorCommander* _commander;  //���������Ĭ��Ϊ��ָ��
			int _groupField; //�ƶ�������ֶα��
		};
	}
}