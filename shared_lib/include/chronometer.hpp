#pragma once
#include <chrono>

class Chronometer
{
public:
    Chronometer(const std::string& name)
    {
        m_name = name;
        m_chrono_start = std::chrono::high_resolution_clock::now();
    }
    ~Chronometer()
    {
        const auto chrono_end = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration<double, std::milli>(chrono_end - m_chrono_start);
        std::printf("\nChronometer::%s : %f ms\n", m_name.c_str(), duration.count());
    }

    Chronometer(const Chronometer& other) = delete;
    Chronometer(Chronometer&& other) noexcept = delete;
    Chronometer& operator=(const Chronometer& other) = delete;
    Chronometer& operator=(Chronometer&& other) noexcept = delete;

private:
    std::chrono::time_point<std::chrono::steady_clock> m_chrono_start{};
    std::string m_name{};
};