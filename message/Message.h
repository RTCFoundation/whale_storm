#pragma once
#include<cstdint>

//系统消息定义

namespace whale_storm
{
	namespace message
	{
		class Message
		{
		public:
			struct Type
			{
				enum
				{
					stop=0
				};
			};
			Message(int32_t type) :_type(type) {

			}
			virtual ~Message() {

			}
			int32_t GetType() const
			{
				return _type;
			}
			void SetType(int32_t type)
			{
				_type = type;
			}
		private:
			int32_t _type;
		};
	}
}