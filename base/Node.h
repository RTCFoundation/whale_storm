#pragma once

#include"F:\whale_storm\base\NetAddress.h"
#include<ctime>
#include<string>

namespace whale_storm
{
	namespace base
	{
		class Node
		{
		public:
			enum class Status
			{
				Dead,
				Alived
			};
			Node() :_address("", 0), _status(Status::Dead)
			{}

			Node(std::string name, const NetAddress& address) :
				_name(name), _address(address), _status(Status::Dead) {}

			const std::string &GetName() const
			{
				return _name;
			}

			void SetName(const std::string& name)
			{
				_name = name;
			}

			void SetAddress(const NetAddress& address)
			{
				_address = address;
			}

			const NetAddress& GetAddress() const
			{
				return _address;
			}

			Status GetStatus() const
			{
				return _status;
			}

			void SetStatus(Status status)
			{
				_status = status;
			}

			void Alive()
			{
				_lastLiveTime = time_t(0);
			}

			Status UpdateStatus()
			{
				time_t currentTime = 0;
				if (_lastLiveTime - currentTime > 9)
				{
					_status = Status::Dead;
				}
				return _status;
			}
		private:
			std::string _name;
			NetAddress _address;
			Status _status;
			time_t _lastLiveTime;
		};
	}
}