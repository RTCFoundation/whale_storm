#include"F:\whale_storm\whale_storm.h"

#include"F:\whale_storm\message\SupervisorCommander.h"
#include"F:\whale_storm\base\base\ByteArray.h"
#include"F:\whale_storm\base\base\DataPackage.h"
#include"F:\whale_storm\spout\Command.h"
#include"F:\whale_storm\message\NimbusCommander.h"

using whale_storm::base::NetAddress;
using whale_storm::base::ByteArray;
using whale_storm::base::DataPackage;

const int DATA_BUFFER_SIZE = 65535;

namespace whale_storm
{
	namespace message
	{
		void  NimbusCommander::StartSpout(const std::string& spoutName, int executorIndex)
		{
			Connect();

			Command command(Command::Type::StartSpout, { spoutName,executorIndex });
			DataPackage messagePackage = command.ToDataPackage();
			ByteArray message = messagePackage.Serialize();

			char reaultBuffer[DATA_BUFFER_SIZE];
			int32_t resultSize = _connector->SendAndReceive(message.data(), message.size(), reaultBuffer, DATA_BUFFER_SIZE);

			ByteArray result(reaultBuffer, resultSize);
			DataPackage resultPackage;
			resultPackage.Deserialize(result);
			command = Command(resultPackage);

			std::cout << command.GetType() << std::endl;
			std::cout << command.GetArg(0).GetStringValue() << std::endl;
		}

		void NimbusCommander::StartBolt(const std::string& boltName, int executorIndex)
		{
			Connect();

			Command command(Command::Type::StartBolt, {
				boltName, executorIndex
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
	}
}