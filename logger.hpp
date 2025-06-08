#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>

// Adding timestamp
class Logger {
public:
    // 印出有時間戳的訊息
    static void log(const std::string& msg) {
        std::cout << "[" << currentTime() << "] " << msg << std::endl;
    }

private:
    // 取得目前時間字串，格式 HH:MM:SS（含毫秒
    /*
    static std::string currentTime() {
        using namespace std::chrono;
        auto now = system_clock::now();
        std::time_t timeNow = system_clock::to_time_t(now);
        std::tm* timeInfo = std::localtime(&timeNow);
        std::ostringstream oss;
        oss << std::put_time(timeInfo, "%H:%M:%S");
        return oss.str();
    }
    */

    // 取得目前時間字串，格式 HH:MM:SS.sss（含毫秒）
    static std::string currentTime() {
        using namespace std::chrono;

        auto now = system_clock::now();
        std::time_t timeNow = system_clock::to_time_t(now);
        std::tm* timeInfo = std::localtime(&timeNow);

        // std::localtime() 本身不能直接取得毫秒
        auto milliseconds = duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        std::ostringstream oss;
        oss << std::put_time(timeInfo, "%H:%M:%S")
            << '.' << std::setw(3) << std::setfill('0') << milliseconds.count();

        return oss.str();
    }


};

#endif
