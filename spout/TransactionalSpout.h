#pragma once

#include"F:\whale_storm\spout\Coordinator.h"
#include"F:\whale_storm\bolt\Emitter.h"

namespace whale_storm
{
	namespace spout
	{
		class TransactionalSpout
		{
		public:
			virtual whale_storm::spout::Coordinator* GetCoordinatior() = 0;
			virtual whale_storm::bolt::Emitter* GetEmitter() = 0;
		};
	}
}