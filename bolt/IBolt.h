#pragma once
#include"F:\whale_storm\base\ITask.h"

//bolt�ӿڶ���

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
			virtual void Prepare(base::OutputCollector& outputCollector) = 0; //����������ǰ����������ʼ��
			virtual void Cleanup() = 0; //�����˽ṹֹͣʱ��������Դ����
			virtual void Execute(const base::Values& values) = 0;  //����ִ�У�ֻ�����ݵ���ʱ�ŵ���

			virtual  IBolt* Clone() const = 0; //�����������
		};
	}
}