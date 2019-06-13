#pragma once

//日志接口定义
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
		DEBUG, //调试
		STATE,  //状态1
		INFO,   //普通
		WARING, //警告
		FAULT   //致命错误
	};

	class Logger    //日志工具
	{
		Logger &operator=(const Logger&) = delete;

		Logger(const Logger &other) = delete;

	public:
		static Logger *Get();   //获取日志

		void SetPriority(Priority priority);   //设置获取优先级

		Priority GetPriority();   //

		void WriteLog(Priority priority, const std::string &log);  //按特定优先级输出日志

	private:
		Logger(Priority priority);

		virtual ~Logger()
		{

		}

		void _InitializeFileStream();  //初始化日志文件流

		void _WriteThread();  //负责输出的线程函数
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
