#pragma once
#include"F:\whale_storm\base\Values.h"
#include"F:\whale_storm\message\Message.h"

namespace whale_storm
{
	namespace bolt
	{
		class BoltMessage :public whale_storm::message::Message
		{
		public:
			struct MessageType
			{
				enum
				{
					Data=0x1000
				};

			};

			BoltMessage(const base::Values& values):
				whale_storm::message::Message(MessageType::Data), _values(values) {}

			const base::Values& GetValues() const
			{
				return _values;
			}
			void SetValues(const base::Values& values)
			{
				_values = values;
			}
		private:
			base::Values _values;
		};
	}
}