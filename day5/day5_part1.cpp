#include "../shared_lib/include/file_reader.hpp"
#include "../shared_lib/include/file_writer.hpp"
#include "../shared_lib/include/helpers.hpp"
#include "../shared_lib/external/fmt/include/fmt/core.h"

#include <unordered_set>

int main()
{
    fmt::println("day5_part1");
    fmt::println("------------");

    FileReader fr{};
    fr.LoadFile("input.txt");

    FileWriter writer("../day5/part1/output.txt");
    writer.WriteLine("day5_part1");

    auto chrono_start = std::chrono::high_resolution_clock::now();

    std::vector<std::pair<uint64_t, uint64_t>> fresh_ranges{};

    const int total_line_count = fr.LineCount();
    bool seen_empty_line{false};
    int fresh_count{0};

    for (int line_idx = 0; line_idx < total_line_count; ++line_idx)
    {
        std::string input_str = fr.Cin();

        if (input_str.empty())
        {
            seen_empty_line = true;
            continue;
        }

        // adding ranges
        if (!seen_empty_line)
        {
            std::vector<std::string> range_str_vec = split_string(input_str, "-");
            const std::string& range_start_str = range_str_vec.at(0);
            const std::string& range_end_str = range_str_vec.at(1);
            uint64_t range_start_uint = std::stoull(range_start_str);
            uint64_t range_end_uint = std::stoull(range_end_str);
            fresh_ranges.emplace_back(range_start_uint, range_end_uint);
        }
        // checking numbers
        else
        {
            uint64_t num = std::stoull(input_str);
            for (const auto& fresh_range : fresh_ranges)
            {
                if (num >= fresh_range.first && num <= fresh_range.second)
                {
                    fresh_count++;
                    break;
                }
            }
        }
    }

    writer.Close();

    fmt::println("{}", fresh_count);

    auto chrono_end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(chrono_end - chrono_start);
    fmt::println(fmt::format("{} ms", duration.count()));
}
