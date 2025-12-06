#include "../shared_lib/include/file_reader.hpp"
#include "../shared_lib/include/file_writer.hpp"
#include "../shared_lib/include/helpers.hpp"
#include "../shared_lib/include/chronometer.hpp"
#include "../shared_lib/external/fmt/include/fmt/core.h"

struct Group
{
    std::vector<uint64_t> m_numbers_int{};
    std::vector<std::string> m_numbers_str{};
    char m_operation{};
};

struct Line
{
    std::vector<uint64_t> m_numbers_int{};
    std::vector<std::string> m_numbers_str{};
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
    for (int input_line_idx = 0; input_line_idx < line_count; ++input_line_idx)
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
            for (int operation_idx = 0; operation_idx < (int)operations.size(); ++operation_idx)
            {
                Group& group = groups.emplace_back();
                group.m_operation = operations.at(operation_idx);
                for (int line_idx = 0; line_idx < (int)lines.size(); ++line_idx)
                {
                    group.m_numbers_int.emplace_back(lines.at(line_idx).m_numbers_int.at(operation_idx));
                }
            }
        }
    }

    uint64_t grand_total{0};

    for (int group_idx = 0; group_idx < (int)groups.size(); ++group_idx)
    {
        Group& g = groups.at(group_idx);
        if (g.m_operation == '+')
        {
            uint64_t total{0};
            for (int num_idx = 0; num_idx < (int)g.m_numbers_int.size(); ++num_idx)
            {
                total += g.m_numbers_int.at(num_idx);
            }
            grand_total += total;
        }
        else if (g.m_operation == '*')
        {
            uint64_t total{1};
            for (int num_idx = 0; num_idx < (int)g.m_numbers_int.size(); ++num_idx)
            {
                total *= g.m_numbers_int.at(num_idx);
            }
            grand_total += total;
        }
    }

    writer.Close();

    fmt::println("{}", grand_total);
}
