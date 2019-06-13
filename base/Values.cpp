#include"F:\whale_storm\base\Values.h"
#include"F:\whale_storm\base\base\Variant.h"

namespace whale_storm
{
	namespace base
	{
		Variant Value::ToVariant() const
		{
			if (_type == Type::Int8)
				return Variant(static_cast<int32_t>(ToInt8()));
			else if (_type == Type::Int16) {
				return Variant(static_cast<int32_t>(ToInt16()));
			}
			else if (_type == Type::Int32) {
				return Variant(ToInt32());
			}
			else if (_type == Type::String) {
				return Variant(ToString());
			}

			return Variant();
		}

		Value Value::FromVariant(const Variant& variant)
		{
			if (variant.GetType() == Variant::Type::Integer)
			{
				return Value(variant.GetIntValue());
			}
			else if (variant.GetType() == Variant::Type::String) {
				return Value(variant.GetStringValue());
			}

			return Value();
		}
	}
}