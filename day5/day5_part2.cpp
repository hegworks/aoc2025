#include "../shared_lib/include/file_reader.hpp"
#include "../shared_lib/include/file_writer.hpp"
#include "../shared_lib/include/helpers.hpp"
#include "../shared_lib/external/fmt/include/fmt/core.h"

static uint64_t CalcOverlapRangeSize(uint64_t a_begin, uint64_t a_end, uint64_t b_begin, uint64_t b_end) {}

int main()
{
    fmt::println("day5_part2");
    fmt::println("------------");

    FileReader fr{};
    fr.LoadFile("input.txt");

    FileWriter writer("../day5/part2/output.txt");
    writer.WriteLine("day5_part2");

    auto chrono_start = std::chrono::high_resolution_clock::now();

    std::vector<std::pair<uint64_t, uint64_t>> fresh_ranges{};
    const int total_line_count = fr.LineCount();
    uint64_t non_overlapping_ranges_size{0};

    for (int line_idx = 0; line_idx < total_line_count; ++line_idx)
    {
        std::string input_str = fr.Cin();

        if (input_str.empty())
        {
            break;
        }

        std::vector<std::string> range_str_vec = split_string(input_str, "-");
        const std::string& range_start_str = range_str_vec.at(0);
        const std::string& range_end_str = range_str_vec.at(1);
        uint64_t range_start_uint = std::stoull(range_start_str);
        uint64_t range_end_uint = std::stoull(range_end_str);
        fresh_ranges.emplace_back(range_start_uint, range_end_uint);
    }

    const int fresh_ranges_count = (int)fresh_ranges.size();
    for (int range_idx = 0; range_idx < fresh_ranges_count; ++range_idx)
    {
        uint64_t range_begin = fresh_ranges.at(range_idx).first;
        uint64_t range_end = fresh_ranges.at(range_idx).second;
        uint64_t range_size = range_end - range_begin;

        uint64_t total_overlap_size{0};
        for (int other_range_idx = 0; other_range_idx < fresh_ranges_count; ++other_range_idx)
        {
            if (other_range_idx == range_idx)
            {
                continue;
            }

            uint64_t other_range_begin = fresh_ranges.at(other_range_idx).first;
            uint64_t other_range_end = fresh_ranges.at(other_range_idx).second;

            uint64_t overlap_range_size = CalcOverlapRangeSize(range_begin, range_end, other_range_begin, other_range_end);
            total_overlap_size += overlap_range_size;
        }

        uint64_t range_with_reduced_overlap = range_size - total_overlap_size;
        if (range_with_reduced_overlap > 0)
        {
            non_overlapping_ranges_size += range_with_reduced_overlap;
        }
    }

    writer.Close();

    fmt::println("non_overlapping_ranges_size: {}", non_overlapping_ranges_size);

    auto chrono_end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(chrono_end - chrono_start);
    fmt::println(fmt::format("{} ms", duration.count()));
}
