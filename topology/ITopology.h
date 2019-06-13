#pragma once

#include"F:\whale_storm\base\Values.h"

#include<string>
#include<memory>
#include<map>

namespace whale_storm
{
	namespace spout
	{
		class ISpout;
	}
	namespace bolt
	{
		class IBolt;
	}

	namespace topology
	{
		class ITopology
		{
			~ITopology() {}

			virtual void SetSpouts(std::map<std::string, std::shared_ptr<spout::ISpout>> spouts) = 0;
			virtual void SetBolts(std::map<std::string, std::shared_ptr<bolt::IBolt>> bolts) = 0;
			virtual void SetNetwork(std::map<std::string, std::vector<std::string>> network) = 0;
			virtual void EmitFrom(const std::string& src, const base::Values& values) = 0;

			virtual const std::map<std::string, std::shared_ptr<spout::ISpout>>& GetSpouts() const = 0;
			virtual const std::map<std::string, std::shared_ptr<bolt::IBolt>>& GetBolts() const = 0;
			virtual const std::map<std::string, std::vector<std::string>>& GetNetwork() const = 0;

			virtual void Start() = 0;
		};
	}
}