#include"F:\whale_storm\base\NetConnector.h"
#include"F:\whale_storm\whale_storm.h"
#include"F:\whale_storm\Meshy.h"

#include<thread>
#include<chrono>

void NetConnector::Connect()
{
	_client = meshy::TcpClient::Connect(_host.GetHost(), _host.GetPort(), nullptr);
}
int32_t NetConnector::SendAndReceive(const char * buffer, int32_t size, char* resultBuffer, int32_t resultSize)
{
	_client->Send(meshy::ByteArray(buffer, size));

	bool receivedData = false;
	_client->OnDataIndication([&receivedData, &resultSize, &resultBuffer](const char* buf, int64_t size) {
		if (resultSize > size) {
			resultSize = size;
		}

		memcpy(resultBuffer, buf, resultSize);
		receivedData = true;
	});

	while (!receivedData) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	return resultSize;