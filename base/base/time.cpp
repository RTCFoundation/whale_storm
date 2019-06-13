#include"F:\whale_storm\dep\utils\time.h"
#include<sstream>
#include<assert.h>

namespace whale_stormUtils
{
	// TODO: Add special implementation for put_time in Linux
	std::string GetCurrentTimeStamp()
	{
		// get current time
		auto currentTime = std::chrono::system_clock::now();
		// get milliseconds
		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()) % 1000;

		auto currentTimePoint = std::chrono::system_clock::to_time_t(currentTime);

		// output the time stamp
		std::ostringstream stream;

#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__)) && !defined(__MINGW32__)
		stream << std::put_time(std::localtime(&currentTimePoint), "%T");
#else
		char buffer[80];
		auto success = std::strftime(buffer, 80, "%T", std::localtime(&currentTimePoint));
		assert(0 != success);
		stream << buffer;
#endif

		stream << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();

		return stream.str();
	}
}