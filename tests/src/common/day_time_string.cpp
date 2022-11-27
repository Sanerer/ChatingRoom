#include "day_time_string.h"

#include <chrono>
#include <sstream>
#include <string>
#include <ctime>

std::string DayTimeString() {
    auto now = std::chrono::system_clock::now();
    std::time_t today_time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream stream;
    stream << std::ctime(&today_time);
    return stream.str();

}  // namespace