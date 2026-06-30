#pragma once

#include <chrono>

struct Timer {
    std::chrono::steady_clock::time_point start_time;

    Timer() : start_time(
                  std::chrono::steady_clock::now()
              ) {}

    double elapsed_ms() const {
        auto current_time = std::chrono::steady_clock::now();

        return std::chrono::duration<double, std::milli>(current_time - start_time).count();
    }

};