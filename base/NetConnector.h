#pragma once
#include"F:\whale_storm\base\NetAddress.h"
#include"F:\whale_storm\Meshy.h"
#include<cstdint>
#include<memory>

class NetConnector
{
public:
	NetConnector(const whale_storm::base::NetAddress& host) :_host(host) {}
	const whale_storm::base::NetAddress& GetHost() const
	{
		return _host;
	}

	void SetHost(const whale_storm::base::NetAddress& host)
	{
		_host = host;
	}

	void Connect();
	int32_t SendAndReceive(const char* buffer, int32_t size, char* resultBuffer, int32_t resultSize);

private:
	whale_storm::base::NetAddress _host;
	std::shared_ptr<meshy::TcpClient> _client;
};