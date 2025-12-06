#include "../shared_lib/include/file_reader.hpp"
#include "../shared_lib/include/file_writer.hpp"
#include "../shared_lib/include/helpers.hpp"
#include "../shared_lib/include/chronometer.hpp"
#include "../shared_lib/external/fmt/include/fmt/core.h"

struct Group
{
    std::vector<uint64_t> m_numbers_int_p1{};
    std::vector<uint64_t> m_numbers_int_p2{};
    std::vector<std::string> m_numbers_str_f0{};
    std::vector<std::string> m_numbers_str_f1{};
    uint64_t m_num_str_length{};
    char m_operation{};
};

struct Line
{
    std::vector<uint64_t> m_numbers_int{};
};

static std::vector<uint64_t> ExtractNumbers(const std::string& input_str)
{
    std::vector<std::string> numbers_str = split_string(input_str, " ");
    std::vector<uint64_t> numbers_int{};
    numbers_int.reserve(numbers_str.size());
    for (auto& number_str : numbers_str)
    {
        if (number_str.empty() || number_str.at(0) == ' ')
        {
            continue;
        }

        numbers_int.emplace_back(std::stoull(number_str));
    }
    return numbers_int;
}

static std::vector<char> ExtractOperations(const std::string& input_str)
{
    std::vector<std::string> chars_str = split_string(input_str, " ");
    std::vector<char> chars{};
    chars.reserve(chars_str.size());
    for (auto& char_str : chars_str)
    {
        if (char_str.empty() || char_str.at(0) == ' ')
        {
            continue;
        }

        chars.emplace_back(char_str.at(0));
    }
    return chars;
}

static uint64_t CalcRangeStart(const std::vector<Group>& groups, uint64_t group_idx)
{
    uint64_t result{0};

    for (uint64_t i = 0; i < group_idx; ++i)
    {
        result += groups.at(i).m_num_str_length + 1;
    }

    return result;
}

int main()
{
    fmt::println("day6_part2");
    fmt::println("------------");

    FileReader reader{};
    reader.LoadFile("input.txt");

    FileWriter writer("../day6/part2/output.txt");
    writer.WriteLine("day6_part2");

    Chronometer chronometer{"day6_part2"};

    std::vector<Group> groups{};
    std::vector<Line> lines{};

    const int line_count = reader.LineCount();
    for (uint64_t input_line_idx = 0; input_line_idx < (uint64_t)line_count; ++input_line_idx)
    {
        std::string input_str = reader.Cin();
        if (input_str.at(0) != '*' && input_str.at(0) != '+')
        {
            Line& line = lines.emplace_back();
            line.m_numbers_int = ExtractNumbers(input_str);
        }
        else
        {
            std::vector<char> operations = ExtractOperations(input_str);
            for (uint64_t operation_idx = 0; operation_idx < operations.size(); ++operation_idx)
            {
                Group& group = groups.emplace_back();
                group.m_operation = operations.at(operation_idx);
                for (uint64_t line_idx = 0; line_idx < lines.size(); ++line_idx)
                {
                    group.m_numbers_int_p1.emplace_back(lines.at(line_idx).m_numbers_int.at(operation_idx));
                }
            }
        }
    }

    const uint64_t input_number_line_count = lines.size();

    for (uint64_t group_idx = 0; group_idx < groups.size(); ++group_idx)
    {
        Group& g = groups.at(group_idx);
        const uint64_t max_num = *std::max_element(g.m_numbers_int_p1.begin(), g.m_numbers_int_p1.end());
        const std::string max_num_str = std::to_string(max_num);
        const uint64_t num_str_length = max_num_str.size();
        g.m_num_str_length = num_str_length;

        const uint64_t range_start = CalcRangeStart(groups, group_idx);
        for (uint64_t input_line_idx = 0; input_line_idx < input_number_line_count; ++input_line_idx)
        {
            const std::string input_line_str = reader.GetLine(input_line_idx);
            const std::string num_str = input_line_str.substr(range_start, num_str_length);
            g.m_numbers_str_f0.emplace_back(num_str);
        }

        for (uint64_t g_column_idx = 0; g_column_idx < num_str_length; ++g_column_idx)
        {
            g.m_numbers_str_f1.emplace_back(input_number_line_count, ' ');
            for (uint64_t g_row_idx = 0; g_row_idx < input_number_line_count; ++g_row_idx)
            {
                g.m_numbers_str_f1.at(g_column_idx).at(g_row_idx) = g.m_numbers_str_f0.at(g_row_idx).at(g_column_idx);
            }
        }

        for (uint64_t numbers_str_f1_idx = 0; numbers_str_f1_idx < g.m_numbers_str_f1.size(); ++numbers_str_f1_idx)
        {
            g.m_numbers_int_p2.emplace_back(std::stoull(g.m_numbers_str_f1.at(numbers_str_f1_idx)));
        }
    }

    uint64_t grand_total{0};

    for (uint64_t group_idx = 0; group_idx < groups.size(); ++group_idx)
    {
        Group& g = groups.at(group_idx);
        if (g.m_operation == '+')
        {
            uint64_t total{0};
            for (uint64_t num_idx = 0; num_idx < g.m_numbers_int_p2.size(); ++num_idx)
            {
                total += g.m_numbers_int_p2.at(num_idx);
            }
            grand_total += total;
        }
        else if (g.m_operation == '*')
        {
            uint64_t total{1};
            for (uint64_t num_idx = 0; num_idx < g.m_numbers_int_p2.size(); ++num_idx)
            {
                total *= g.m_numbers_int_p2.at(num_idx);
            }
            grand_total += total;
        }
    }

    writer.Close();

    fmt::println("{}", grand_total);
}
