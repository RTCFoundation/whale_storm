#pragma once
#include<string>
namespace whale_storm
{
	namespace base
	{
		class NetAddress
		{
		public:
			NetAddress(const std::string& host, int port) :_host(host), _port(port) {

			}
			const std::string& GetHost() const {
				return _host;
			}
			void SetHost(const std::string& host)
			{
				_host = host;
			}

			int GetPort() const {
				return _port;
			}
			void SetPort(int port) {
				_port = port;
			}
		private:
			std::string _host;
			int _port;
		};
	}
}