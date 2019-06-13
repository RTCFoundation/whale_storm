#pragma once

//Ïß³Ì³Ø
#ifndef NET_FRAME_THREAD_POOL_H
#define NET_FRAME_THREAD_POOL_H

#include"F:\whale_storm\dep\utils\concurrent_queue.h"
#include<vector>
#include<queue>
#include<memory>
#include<mutex>
#include<condition_variable>
#include<future>
#include<functional>
#include<stdexcept>

#define MIN_THREADS 10

namespace meshy
{
	template<class Type>

	class ThreadPool
	{
		ThreadPool &operator=(const ThreadPool&) = delete;

		ThreadPool(const ThreadPool &other) = delete;
	public:
		TreadPool(int32_t threads, std::function<void(Type &record)>hander);

		virtual ~ThreadPool();

		void Submit(Type record);

	private:
		bool _shutdown;
		int32_t _threads;
		std::function<void(Type& record)> _headler;
		std::vector<std::thread> _workers;
		ConcurrentQueue <type> _task;
	};
}
#endif NET_FRAME_THREAD_POOL_H
