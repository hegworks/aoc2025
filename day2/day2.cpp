#include "../shared_lib/include/file_reader.hpp"
#include "../shared_lib/include/file_writer.hpp"
#include "../shared_lib/include/shared_lib.hpp"
#include "../shared_lib/external/fmt/include/fmt/core.h"
#include "../shared_lib/include/helpers.hpp"

// #define PART1
#define PART2

#ifdef PART1
bool HasPattern(uint64_t num)
{
    constexpr int part_count = 2;

    std::string num_str = std::to_string(num);
    int digit_count = (int)num_str.size();

    if (digit_count % part_count != 0)
    {
        return false;
    }

    uint64_t part_length = digit_count / part_count;
    std::string first_part_str = num_str.substr(0, part_length);
    std::string next_part_str = num_str.substr(part_length, num_str.back());
    return first_part_str == next_part_str;
}

void Part1()
{
    fmt::println("day2_part1");
    fmt::println("------------");

    FileReader fr{};
    fr.LoadFile("input.txt");

    FileWriter writer("../day2/part1/output.txt");
    writer.WriteLine("day2_part1");

    std::string input = fr.Cin();
    std::vector<std::string> ranges_str = InlineHelpers::split_string(input, ",");

    uint64_t sum{0};
    int detected_count{0};

    const int range_count = (int)ranges_str.size();
    for (int range_idx = 0; range_idx < range_count; ++range_idx)
    {
        std::string range_str = ranges_str.at(range_idx);
        std::vector<std::string> range_nums_str = InlineHelpers::split_string(range_str, "-");
        const uint64_t range_start = std::stoull(range_nums_str.at(0));
        const uint64_t range_end = std::stoull(range_nums_str.at(1));

        for (uint64_t num = range_start; num <= range_end; ++num)
        {
            if (HasPattern(num))
            {
                // fmt::println("{}", num);
                sum += num;
                detected_count++;
                writer.WriteLine(fmt::format("{}", num));
            }
        }
    }

    writer.Close();

    fmt::println("sum: {}", sum);
    fmt::println("detecteds: {}", detected_count);
}
#endif

#ifdef PART2
bool HasPattern(uint64_t num, uint64_t part_length)
{
    std::string num_str = std::to_string(num);
    int digit_count = (int)num_str.size();

    if (digit_count % part_length != 0)
    {
        return false;
    }

    uint64_t part_count = digit_count / part_length;
    std::string first_part_str = num_str.substr(0, part_length);
    for (uint64_t i = 1; i < part_count; ++i)
    {
        std::string next_part_str;
        next_part_str = num_str.substr(i * part_length, part_length);

        if (first_part_str != next_part_str)
        {
            return false;
        }
    }

    return true;
}

void Part2()
{
    fmt::println("day2_part2");
    fmt::println("------------");

    FileReader fr{};
    fr.LoadFile("input.txt");

    FileWriter writer("../day2/part2/output.txt");
    writer.WriteLine("day2_part2");

    std::string input = fr.Cin();
    std::vector<std::string> ranges_str = InlineHelpers::split_string(input, ",");

    uint64_t sum{0};
    int detected_count{0};

    const int range_count = (int)ranges_str.size();
    for (int range_idx = 0; range_idx < range_count; ++range_idx)
    {
        std::string range_str = ranges_str.at(range_idx);
        std::vector<std::string> range_nums_str = InlineHelpers::split_string(range_str, "-");
        const uint64_t range_start = std::stoull(range_nums_str.at(0));
        const uint64_t range_end = std::stoull(range_nums_str.at(1));

        for (uint64_t num = range_start; num <= range_end; ++num)
        {
            std::string num_str = std::to_string(num);
            uint64_t digit_count = num_str.size();
            uint64_t part_length = (int)ceil((float)digit_count / 2.0f);
            while (part_length > 0)
            {
                if (HasPattern(num, part_length))
                {
                    // fmt::println("{}", num);
                    sum += num;
                    detected_count++;
                    writer.WriteLine(fmt::format("{}", num));
                    break;
                }
                part_length--;
            }
        }
    }

    writer.Close();

    fmt::println("sum: {}", sum);
    fmt::println("detecteds: {}", detected_count);
}
#endif

int main()
{
#ifdef PART1
    Part1();
#elif defined(PART2)
    Part2();
#endif
}
