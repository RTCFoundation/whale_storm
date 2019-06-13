#include"F:\whale_storm\whale_storm.h"
#include"F:\whale_storm\message\SupervisorCommander.h"
#include"F:\whale_storm\base\base\ByteArray.h"
#include"F:\whale_storm\base\base\DataPackage.h"
#include"F:\whale_storm\spout\Command.h"

using whale_storm::base::NetAddress;
using whale_storm::base::ByteArray;
using whale_storm::base::DataPackage;

const int DATA_BUFFER_SIZE = 65535;

namespace whale_storm
{
	namespace message
	{
		void SupervisorCommander::Join() {
			Connect();

			Command command(Command::Type::Join, {
				_supervisorName
				});
			DataPackage messagePackage = command.ToDataPackage();
			ByteArray message = messagePackage.Serialize();

			char resultBuffer[DATA_BUFFER_SIZE];
			int32_t resultSize =
				_connector->SendAndReceive(message.data(), message.size(), resultBuffer, DATA_BUFFER_SIZE);

			ByteArray result(resultBuffer, resultSize);
			DataPackage resultPackage;
			resultPackage.Deserialize(result);
			command = Command(resultPackage);

			std::cout << command.GetType() << std::endl;
			std::cout << command.GetArg(0).GetStringValue() << std::endl;
		}

		void SupervisorCommander::Alive() {
			Connect();

			Command command(Command::Type::Alive, {
				_supervisorName
				});
			DataPackage messagePackage = command.ToDataPackage();
			ByteArray message = messagePackage.Serialize();

			char resultBuffer[DATA_BUFFER_SIZE];
			int32_t resultSize =
				_connector->SendAndReceive(message.data(), message.size(), resultBuffer, DATA_BUFFER_SIZE);

			ByteArray result(resultBuffer, resultSize);
			DataPackage resultPackage;
			resultPackage.Deserialize(result);
			command = Command(resultPackage);
		}

		void SupervisorCommander::SendTuple(int taskIndex,
			const base::Values& values) {
			Connect();

			base::Variants args = { _supervisorName, _taskIndex };
			for (const base::Value& value : values) {
				args.push_back(value.ToVariant());
			}

			Command command(Command::Type::Data, args);

			DataPackage messagePackage = command.ToDataPackage();
			ByteArray message = messagePackage.Serialize();

			char resultBuffer[DATA_BUFFER_SIZE];
			int32_t resultSize =
				_connector->SendAndReceive(message.data(), message.size(), resultBuffer, DATA_BUFFER_SIZE);

			ByteArray result(resultBuffer, resultSize);
			DataPackage resultPackage;
			resultPackage.Deserialize(result);
			command = Command(resultPackage);

			std::cout << command.GetType() << std::endl;
			std::cout << command.GetArg(0).GetStringValue() << std::endl;
		}
		void SupervisorCommander::RandomDestination(const std::string srcType, int32_t srcIndex,
			std::string * host, int * port, int* destIndex)
		{
			Connect();

			Command command(Command::Type::RandomDestination, {
				_supervisorName, srcType, srcIndex
				});
			DataPackage messagePackage = command.ToDataPackage();
			ByteArray message = messagePackage.Serialize();

			char resultBuffer[DATA_BUFFER_SIZE];
			int32_t resultSize =
				_connector->SendAndReceive(message.data(), message.size(), resultBuffer, DATA_BUFFER_SIZE);

			ByteArray result(resultBuffer, resultSize);
			DataPackage resultPackage;
			resultPackage.Deserialize(result);
			command = Command(resultPackage);

			*host = command.GetArg(1).GetStringValue();
			*port = command.GetArg(2).GetIntValue();
			*destIndex = command.GetArg(3).GetIntValue();
		}

		void SupervisorCommander::GroupDestination(const std::string srcType, int srcIndex,
			std::string * host, int * port, int * destIndex,
			int fieldIndex)
		{
			Connect();

			Command command(Command::Type::RandomDestination, {
				_supervisorName, srcType, srcIndex, fieldIndex
				});
			DataPackage messagePackage = command.ToDataPackage();
			ByteArray message = messagePackage.Serialize();

			char resultBuffer[DATA_BUFFER_SIZE];
			int32_t resultSize =
				_connector->SendAndReceive(message.data(), message.size(), resultBuffer, DATA_BUFFER_SIZE);

			ByteArray result(resultBuffer, resultSize);
			DataPackage resultPackage;
			resultPackage.Deserialize(result);
			command = Command(resultPackage);

			*host = command.GetArg(1).GetStringValue();
			*port = command.GetArg(2).GetIntValue();
			*destIndex = command.GetArg(3).GetIntValue();
		}
	}
}