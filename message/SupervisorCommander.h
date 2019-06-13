#pragma once
#include"F:\whale_storm\base\NetAddress.h"
#include"F:\whale_storm\base\NetConnector.h"
#include"F:\whale_storm\base\Values.h"

#include<string>

namespace whale_storm
{
	namespace message
	{
		class SupervisorCommander
		{
		public:
			SupervisorCommander(const whale_storm::base::NetAddress& nimnusAddress,
				const std::string& supervisorName) :
				_nimbusAddress(nimnusAddress), _supervisorName(supervisorName) {}

			void Connect()
			{
				if (!_connector.get())
				{
					_connector = std::make_shared<NetConnector>(_nimbusAddress);
					_connector->Connect();
				}
			}

			void Join();
			void Alive();
			void SendTuple(int taskIndex, const base::Values& value);
			void RandomDestination(const std::string srcType, int32_t srcIndex, std::string * host,
				int * port, int* destIndex);
			void GroupDestination(const std::string srcTypr, int srcIndex,
				std::string * host, int* port, int* destIndex, int FieldIndex);
			const std::string GetSupervisorName() const
			{
				return _supervisorName;
			}
		private:
			whale_storm::base::NetAddress _nimbusAddress;
			std::string _supervisorName;
			std::shared_ptr<NetConnector> _connector;
			int32_t _taskIndex;
		};
	}
}