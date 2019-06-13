#pragma once

//��־�ӿڶ���
#ifndef NET_FRAME_LOGGER_H
#define NET_FRAME_LOGGER_H

#include"F:\whale_storm\dep\utils\concurrent_queue.h"
#include<memory>
#include<thread>
#include<queue>
#include<string>
#include<fstream>
namespace meshy
{
	enum Priority
	{
		DEBUG, //����
		STATE,  //״̬1
		INFO,   //��ͨ
		WARING, //����
		FAULT   //��������
	};

	class Logger    //��־����
	{
		Logger &operator=(const Logger&) = delete;

		Logger(const Logger &other) = delete;

	public:
		static Logger *Get();   //��ȡ��־

		void SetPriority(Priority priority);   //���û�ȡ���ȼ�

		Priority GetPriority();   //

		void WriteLog(Priority priority, const std::string &log);  //���ض����ȼ������־

	private:
		Logger(Priority priority);

		virtual ~Logger()
		{

		}

		void _InitializeFileStream();  //��ʼ����־�ļ���

		void _WriteThread();  //����������̺߳���
	private:
		ConcurrentQueue<std::string> _queue;
		std::ofstream* _fileStream;
		Priority _priority;
		bool _shutdown;
	};
#define TRACE_DEBUG(LOG_CONTENT) Logger::Get()->WriteLog(DEBUG, LOG_CONTENT);
#define TRACE_STATE(LOG_CONTENT) Logger::Get()->WriteLog(STATE, LOG_CONTENT);
#define TRACE_INFO(LOG_CONTENT) Logger::Get()->WriteLog(INFO, LOG_CONTENT);
#define TRACE_WARNING(LOG_CONTENT) Logger::Get()->WriteLog(WARNING, LOG_CONTENT);
#define TRACE_ERROR(LOG_CONTENT) Logger::Get()->WriteLog(FAULT, LOG_CONTENT);
}
#endif // !NET_FRAME_LOGGER_H
