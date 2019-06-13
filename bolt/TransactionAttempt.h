#pragma once

namespace whale_storm
{
	namespace bolt
	{
		class TransactionAttempt
		{
		public:
			TransactionAttempt(int transactionId,int attemptId):
				_transactionId(transactionId), _attemptId(attemptId) {}

			int GetTransactionId() const
			{
				return _transactionId;
			}

			int GetAttempId() const
			{
				return _attemptId;
			}
		private:
			int _transactionId;
			int _attemptId;
		};
	}
}