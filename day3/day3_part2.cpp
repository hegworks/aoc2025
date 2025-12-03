#include "../shared_lib/include/file_reader.hpp"
#include "../shared_lib/include/file_writer.hpp"
#include "../shared_lib/external/fmt/include/fmt/core.h"

#include <assert.h>
#include <algorithm>

bool ExistsInIntVec(const std::vector<int>& vec, int to_find)
{
    return std::find(vec.begin(), vec.end(), to_find) != vec.end();
}

int CharToInt(char c) { return c - '0'; }

int DigitFromIntStr(int idx, const std::string& s) { return CharToInt(s.at(idx)); }

int GetBiggestNumIdx(const std::string& input_str, int start_idx, std::vector<int> ignore_idxs)
{
    int biggest_digit = 0;
    int biggest_digit_idx = -1;
    int digit_count = (int)input_str.size();
    for (int digit_idx = start_idx; digit_idx < digit_count; ++digit_idx)
    {
        if (ExistsInIntVec(ignore_idxs, digit_idx))
        {
            continue;
        }

        int digit_int = DigitFromIntStr(digit_idx, input_str);
        if (digit_int > biggest_digit)
        {
            biggest_digit = digit_int;
            biggest_digit_idx = digit_idx;
        }
    }
    return biggest_digit_idx;
}

int main()
{
    fmt::println("day3_part2");
    fmt::println("------------");

    FileReader fr{};
    fr.LoadFile("input.txt");

    FileWriter writer("../day3/part2/output.txt");
    writer.WriteLine("day3_part2");

    uint64_t sum{0};

    const int total_line_count = fr.LineCount();
    for (int line_idx = 0; line_idx < total_line_count; ++line_idx)
    {
        std::vector<int> found_idxs{};
        std::string input_str = fr.Cin();
        writer.WriteLine(fmt::format("line: {}", line_idx));
        writer.WriteLine(input_str);
        const int num_length = (int)input_str.size();

        constexpr int digits_to_find_count = 12;
        int start_idx = 0;
        for (int i = 0; i < digits_to_find_count; ++i)
        {
            int biggest_digit_idx = GetBiggestNumIdx(input_str, start_idx, found_idxs);
            assert(biggest_digit_idx != -1);
            found_idxs.emplace_back(biggest_digit_idx);

            bool found_starting_idx{false};
            for (int j = (int)found_idxs.size() - 1; j >= 0; j--)
            {
                bool can_find_biggest = GetBiggestNumIdx(input_str, found_idxs.at(j), found_idxs) != -1;
                if (can_find_biggest)
                {
                    start_idx = found_idxs.at(j);
                    found_starting_idx = true;
                    break;
                }
            }
            if (!found_starting_idx)
            {
                start_idx = 0;
            }
        }

        std::string indicators = "";
        for (int i = 0; i < num_length; ++i)
        {
            indicators += ExistsInIntVec(found_idxs, i) ? "^" : " ";
        }
        writer.WriteLine(indicators);

        std::sort(found_idxs.begin(), found_idxs.end());

        std::string str_combined{};
        for (int i = 0; i < digits_to_find_count; ++i)
        {
            const int digit_int = DigitFromIntStr(found_idxs.at(i), input_str);
            std::string digit_str = std::to_string(digit_int);
            str_combined += digit_str;
        }
        writer.WriteLine(fmt::format("result: {}", str_combined));

        uint64_t int_combined = std::stoull(str_combined);
        sum += int_combined;

        writer.WriteLine("");
    }
    writer.WriteLine("------------");
    writer.WriteLine(fmt::format("{}", sum));
    writer.Close();

    fmt::println(fmt::format("{}", sum));
}
