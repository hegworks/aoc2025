#include "../shared_lib/include/file_reader.hpp"
#include "../shared_lib/include/file_writer.hpp"
#include "../shared_lib/external/fmt/include/fmt/core.h"

#include <assert.h>

int CharToInt(char c) { return c - '0'; }

int DigitFromIntStr(int idx, const std::string& s) { return CharToInt(s.at(idx)); }

int GetBiggestNumIdx(const std::string& input_str, int start_idx, int end_idx)
{
    int biggest_digit = 0;
    int biggest_digit_idx = -1;
    for (int digit_idx = start_idx; digit_idx <= end_idx; ++digit_idx)
    {
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

    int sum{0};

    const int total_line_count = fr.LineCount();
    for (int line_idx = 0; line_idx < total_line_count; ++line_idx)
    {
        std::string input_str = fr.Cin();
        writer.WriteLine(input_str);
        const int num_length = (int)input_str.size();
        int first_biggest_num_idx = GetBiggestNumIdx(input_str, 0, num_length - 1);
        const bool is_last_digit = first_biggest_num_idx == num_length - 1;
        int second_biggest_num_idx = is_last_digit ? GetBiggestNumIdx(input_str, 0, num_length - 2)
                                                   : GetBiggestNumIdx(input_str, first_biggest_num_idx + 1, num_length - 1);
        assert(first_biggest_num_idx != second_biggest_num_idx);

        std::string spaces_0 = "";
        for (int i = 0; i < first_biggest_num_idx; ++i)
        {
            spaces_0 += " ";
        }
        spaces_0 += "-";

        std::string spaces_1 = "";
        for (int i = 0; i < second_biggest_num_idx; ++i)
        {
            spaces_1 += " ";
        }
        spaces_1 += "-";
        writer.WriteLine(spaces_0);
        writer.WriteLine(spaces_1);

        if (is_last_digit)
        {
            int temp = first_biggest_num_idx;
            first_biggest_num_idx = second_biggest_num_idx;
            second_biggest_num_idx = temp;
        }

        writer.WriteLine(fmt::format("idx_0: {}", first_biggest_num_idx));
        writer.WriteLine(fmt::format("idx_1: {}", second_biggest_num_idx));
        const int int_1 = DigitFromIntStr(first_biggest_num_idx, input_str);
        const int int_2 = DigitFromIntStr(second_biggest_num_idx, input_str);
        std::string str_1 = std::to_string(int_1);
        std::string str_2 = std::to_string(int_2);
        std::string str_combined = str_1 + str_2;
        writer.WriteLine(fmt::format("result: {}", str_combined));
        int int_combined = std::stoi(str_combined);
        sum += int_combined;

        writer.WriteLine(" ");
    }
    writer.WriteLine("------------");
    writer.WriteLine(fmt::format("{}", sum));
    writer.Close();

    fmt::println(fmt::format("{}", sum));
}
