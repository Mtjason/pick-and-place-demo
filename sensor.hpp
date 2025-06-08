
/* 
#ifndef / #define / #endif 是 巨集條件編譯（Macro Guards）
能：防止這個檔案被 重複 include 而造成錯誤（重複定義類別）
當 SENSOR_HPP 尚未定義，才會編譯中間的內容
*/
#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <random>
#include <chrono>
#include "logger.hpp"

// hpp normally doe not use impentation; unless it's some simple type
class Sensor {
public:
    // 模擬晶片是否到位（隨機 50% 機率）
    bool isChipReady() {
        Logger::log("  Checking sensor...");
        using namespace std::chrono;
        auto seed = high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 rng(seed); // Generate a radom number 0 ~ 4,294,,967,295

        std::uniform_int_distribution<int> dist(0, 1); //分布接受-2,147,483,648 ~ 2,147,483,647數值
        /* 背後做法（簡化版邏輯）：int result = a + (rng() % (b - a + 1)); */
        return dist(rng) == 1;
    }
};

#endif
