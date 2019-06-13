#pragma once

#include"F:\whale_storm\base\base\DataPackage.h"
#include<memory>

namespace meshy
{
	class TcpConnection;
}

namespace whale_storm
{
	namespace message
	{
		class Command
		{
		public:
			class Type
			{
			public:
				enum Values
				{
					Invalid = 0,
					Join = 1,
					Alive = 2,
					Leave = 3,
					StartTopology = 4,
					StartSpout = 6,
					StopSpout = 7,
					StartBolt = 8,
					StopBolt = 9,
					RandomDestination = 10,
					GroupDestination = 11,
					Response = 254,
					Data = 255
				};
			};

			Command() :_type(Command::Type::Invalid) {}

			Command(Command::Type::Values type, const whale_storm::base::Variants& args) :
				_type(type), _args(args)
			{}

			Command(const whale_storm::base::DataPackage& dataPackag)
			{
				const whale_storm::base::Variants variants = dataPackag.GetVariants();
				_type = Command::Type::Values(variants[0].GetIntValue());
				_args = variants;
				_args.erase(_args.begin());
			}

			whale_storm::base::DataPackage ToDataPackage() const
			{
				whale_storm::base::DataPackage dataPackage;
				dataPackage.AddVariant(int(_type));
				for (auto arg : _args)
				{
					dataPackage.AddVariant(arg);
				}
				return dataPackage;
			}
			Command::Type::Values GetType() const {
				return _type;
			}

			void SetType(Command::Type::Values type) {
				_type = type;
			}

			const whale_storm::base::Variant& GetArg(int index) const {
				return _args[index];
			}

			whale_storm::base::Variant& GetArg(int index) {
				return _args[index];
			}

			const whale_storm::base::Variants& GetArgs() const {
				return _args;
			}

			void SetArgs(const whale_storm::base::Variants& args) {
				_args = args;
			}

			void PushArg(const whale_storm::base::Variant& arg) {
				_args.push_back(arg);
			}

			const whale_storm::base::Variant PopArg() {
				whale_storm::base::Variant arg = _args.back();
				_args.pop_back();

				return arg;
			}

			std::shared_ptr<meshy::TcpConnection> GetSrc() const {
				return _src;
			}

			void SetSrc(std::shared_ptr<meshy::TcpConnection> src) {
				_src = src;
			}
		private:
			Command::Type::Values _type;
			whale_storm::base::Variants _args;
			std::shared_ptr<meshy::TcpConnection> _src;
		};
	}
}