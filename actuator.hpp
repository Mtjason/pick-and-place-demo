#ifndef ACTUATOR_HPP
#define ACTUATOR_HPP

#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include "logger.hpp"

class Actuator {
public:
    bool pick() {
        Logger::log("  Picking up chip..." );
        //std::cout << "  → Picking up chip..." << std::endl;
        simulateAction();
        if (randomFail(0.1)) {
            Logger::log("    (!) Pick failed.");
            return false;
        }

        Logger::log("    Pick completed.");
        return true;
    }

    void move() {
        Logger::log("  Moving to target...");
        //std::cout << "  → Moving to target..." << std::endl;
        simulateAction();
        Logger::log("    Move completed.");
    }

    void place() {
        Logger::log("  Placing chip...");
        simulateAction();
        Logger::log("    Place completed.");
    }

    void goHome() {
        Logger::log("  Returning to home...");
        simulateAction();
        Logger::log("    Return completed.");
    }

private:
    void simulateAction(int milliseconds = 500) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    bool randomFail(double failRate) {
        static std::random_device rd;
        static std::mt19937 rng(rd());
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        return dist(rng) < failRate;
    }
};

#endif
