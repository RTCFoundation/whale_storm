#include"F:\whale_storm\dep\utils\time.h"
#include"F:\whale_storm\dep\utils\logger.h"

#include<iostream>
#include<sstream>

namespace meshy
{
	const std::string PRIORITY_STRING[]=
	{
		"DEBUG",
		"CONFIG",
		"INFO",
		"WORNING",
		"ERROR"
	};
	Logger *Logger::Get()
	{
		static Logger logger(DEBUG);
		return &logger;
	}

	Logger::Logger(Priority priority) :_queue(), _fileStream(nullptr), _shutdown(false)
	{
		_priority = priority;
		_InitializeFileStream();
		auto func = std::bind(&Logger::_WriteThread, this);
		std::thread writeThread(func);
		writeThread.detach();
	}
	Logger::~Logger()
	{
		_shutdown = true;

		if (_fileStream != nullptr)
		{
			_fileStream->close();
			delete _fileStream;
			_fileStream = nullptr;
		}
	}

	void Logger::SetPriority(Priority priority)
	{
		_priority = priority;
	}

	Priority Logger::GetPriority()
	{
		return _priority;
	}

	void Logger::_InitializeFileStream()
	{
		std::string fileName = "logs/whale_storm_log.log";

		_fileStream = new std::ofstream();

		std::ios_base::openmode mode = std::ios_base::out;      //将文件模式设置为截断
		mode |= std::ios_base::trunc;
		_fileStream->open(fileName, mode);   //打开文件流

		if (!_fileStream->is_open())
		{
			std::ostringstream ss_error;
			ss_error << "FATAL ERROR:  could not Open log file: [" << fileName << "]";
			ss_error << "\n\t\t std::ios_base state = " << _fileStream->rdstate();
			std::cerr << ss_error.str().c_str() << std::endl << std::flush;

			//cleanup
			_fileStream->close();
			delete _fileStream;
			_fileStream = nullptr;
		}
	}
	void Logger::WriteLog(Priority priority, const std::string &log)
	{
		if (priority < _priority)      //用户想输出的优先级是否小于预设优先级
			return;

		std::stringstream stream;
		stream << whale_stormUtils::GetCurrentTimeStamp()    //大于则拼组字符串放入队列
			<< "[" << PRIORITY_STRING[priority] << "]" << log;

		_queue.Push(stream.str());
	}

	void Logger::_WriteThread()     //独立线程，不断取出数据并写入日志文件
	{
		while (!_shutdown)
		{
			std::string log;
			_queue.Pop(log, true);

			std::cout << log << std::endl;

			if (_fileStream)
				*_fileStream << log << std::endl;
		}
	}
}