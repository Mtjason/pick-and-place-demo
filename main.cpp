#include <iostream>
#include <thread>
#include <chrono>
#include "sensor.hpp"
#include "actuator.hpp"
#include "logger.hpp"

// 定義狀態流程
// enum 是「列舉（enumeration）」的縮寫，用來定義一組命名常數，通常代表一組有限且相關的狀態或選項。
enum class State {
    IDLE,
    WAIT_SENSOR,
    PICK,
    MOVE,
    PLACE,
    RETURN
};

// 取得狀態對應的文字描述
std::string stateToString(State s) {
    switch (s) {
        case State::IDLE: return "IDLE";
        case State::WAIT_SENSOR: return "WAIT_SENSOR";
        case State::PICK: return "PICK";
        case State::MOVE: return "MOVE";
        case State::PLACE: return "PLACE";
        case State::RETURN: return "RETURN";
        default: return "UNKNOWN";
    }
}

int main() {
    State currentState = State::IDLE;
    Sensor sensor;
    Actuator actuator;

    int totalAttempts = 0;
    int successCount = 0;
    int failCount = 0;

    while (true) {
        Logger::log("[STATE] " + stateToString(currentState));
        //std::cout << "[STATE] " << stateToString(currentState) << std::endl;

        switch (currentState) {
            case State::IDLE:
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                currentState = State::WAIT_SENSOR;
                break;

            case State::WAIT_SENSOR: {
                bool ready = false;
                int wait_count = 0;

                // 每秒檢查一次，最多等 5 次
                while (!ready && wait_count < 5) {
                    /*
                    // For continue retrying case
                    Logger::log("  → Checking sensor...");
                    ready = sensor.isChipReady();
                    if (!ready) {
                        Logger::log("    Chip not ready.");
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        wait_count++;
                    }
                    */
                    ready = sensor.isChipReady();
                    if (!ready) {
                        Logger::log("    Chip is not ready.");
                        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        wait_count++;
                    }
                }

                if (ready) {
                    Logger::log("    Chip detected.");
                    currentState = State::PICK;
                    totalAttempts++;
                    currentState = State::PICK;
                } else {
                    Logger::log("    (!) Timeout. Return to IDLE.");
                    failCount++;
                    currentState = State::IDLE;
                }   
                break;
            }

            case State::PICK:
                // bool pickSuccess = actuator.pick();
                if (!actuator.pick()) {
                    Logger::log("    (!) Process aborted due to pick failure.");
                    failCount++;
                    currentState = State::IDLE;
                } else {
                    currentState = State::MOVE;
                }
                break;
                currentState = State::MOVE;
                break;

            case State::MOVE:
                actuator.move();
                currentState = State::PLACE;
                break;

            case State::PLACE:
                actuator.place();
                currentState = State::RETURN;
                break;

            case State::RETURN:
                actuator.goHome();
                successCount++;
                Logger::log("  Operation success! [Summary] Success: " + std::to_string(successCount) +
                            ", Fail (!): " + std::to_string(failCount) +
                            ", Total: " + std::to_string(totalAttempts) +
                            ", Success Rate: " + std::to_string((successCount * 100.0 / totalAttempts)) + "%");
                currentState = State::IDLE;
                break;
        }
    }

    return 0;
}
