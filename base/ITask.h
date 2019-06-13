
#pragma once
#include"Fields.h"

//ITask接口定义



namespace whale_storm
{
	namespace base
	{
		class ITask {
		public:
			struct Strategy {
				enum Values {
					Global = 0,
					Random = 1,
					Group = 2
				};
			};

			virtual ~ITask() {}

			virtual Fields DeclareFields() const = 0;

			Strategy::Values GetStrategy() const {
				return _strategy;
			}

			void SetStrategy(Strategy::Values strategy) {
				_strategy = strategy;
			}

		private:
			Strategy::Values _strategy;
		};
	}
}