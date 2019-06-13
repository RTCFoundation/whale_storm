
#include"F:\whale_storm\whale_storm.h"
#include"F:\whale_storm\base\OutputCollector.h"
#include"F:\whale_storm\topology\ITopology.h"
#include<iostream>

namespace whale_storm
{
	namespace base
	{
		void OutputCollector::Emit(const Values& values)
		{
			if (_strategy == Strategy
				::Global)
			{
				if (_commander)
					_commander->SendTuple(this->_taskIndex, values);
			}
			else if (_strategy == Strategy::Random) {
				this->RandomDestination();
				_commander->SendTuple(this->_taskIndex, values);
			}
			else if (_strategy == Strategy::Group) {
				this->GroupDestination();
				_commander->SendTuple(this->_taskIndex, values);
			}
		}
	}
}
