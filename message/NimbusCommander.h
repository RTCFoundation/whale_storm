#pragma once

#include"F:\whale_storm\base\NetConnector.h"
#include"F:\whale_storm\base\NetAddress.h"

namespace whale_storm
{
	namespace message
	{
		class NimbusCommander
		{
		public:
			NimbusCommander(const whale_storm::base::NetAddress& supervisorAddress) :
				_supervisorAddress(supervisorAddress) {}

			void Connect()
			{
				if (!_connector.get())
				{
					_connector = std::make_shared<NetConnector>(_supervisorAddress);
					_connector->Connect();
				}
			}

			void StartSpout(const std::string& spoutName, int executorIndex);
			void StartBolt(const std::string& boltName, int executorIndex);
		private:
			whale_storm::base::NetAddress _supervisorAddress;
			std::shared_ptr<NetConnector> _connector;
		};
	}
}