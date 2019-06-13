#pragma once
#include"F:\whale_storm\base\NetAddress.h"
#include"F:\whale_storm\whale_storm.h"
#include"F:\whale_storm\base\Values.h"
#include"F:\whale_storm\Meshy.h"
#include<vector>
#include<iostream>
#include<string>
#include<memory>
#include<thread>
#include<functional>
#include<cstdint>

typedef std::function<void(meshy::TcpStream* connection,
	const char* buffer, int32_t size)>
	DataReceiver;

class NetListener {
public:
	NetListener(const whale_storm::base::NetAddress& host) :
		_host(host) {
	}

	const whale_storm::base::NetAddress& GetHost() const {
		return _host;
	}

	void SetHost(const whale_storm::base::NetAddress& host) {
		_host = host;
	}

	void StartListen();

	void OnData(DataReceiver receiver) {
		_receiver = receiver;
	}

private:
	whale_storm::base::NetAddress _host;
	DataReceiver _receiver;
	meshy::TcpServer _server;
};