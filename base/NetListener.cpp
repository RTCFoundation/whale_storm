#include"F:\whale_storm\spout\NetListener.h"
#include"F:\whale_storm\whale_storm.h"
#include"F:\whale_storm\dep\eventqueueloop.h"
#include"F:\whale_storm\dep\eventqueue.h"
#include"F:\whale_storm\dep\utils\logger.h"
#include"F:\whale_storm\dep\IoLoop.h"
#include<iostream>
#include<thread>
#include<chrono>

const int DATA_BUFFER_SIZE = 65535;

void NetListener::StartListen()
{
	meshy::IoLoop::Get()->Start();

	_server.Listen(_host.GetHost(), _host.GetPort());
	_server.OnConnectIndication([this](meshy::IStream* stream)
	{
		stream->OnDataIndication([stream, this](const char* buf, int64_t size)mutable {
			this->_receiver(dynamic_cast<meshy::TcpStream*>(stream), buf, size);
		});
	});
}