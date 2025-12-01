#include "../shared_lib/include/FileReader.h"
#include "../shared_lib/include/FileWriter.hpp"
#include "../shared_lib/include/shared_lib.hpp"
#include "../shared_lib/external/fmt/include/fmt/core.h"

int main()
{
    fmt::println("Day1");
    fmt::println("------------");

    SharedLib sl{};

    FileReader fr{};
    fr.LoadFile("input.txt");

    FileWriter writer("../day1/output.txt");
    writer.WriteLine("Day1");

    int dial{50};
    int zero_counter{0};

    const int total_line_count = fr.LineCount();
    for (int line_idx = 0; line_idx < total_line_count; ++line_idx)
    {
        std::string input_str = fr.Cin();
        std::string first_char_str{input_str.at(0)};
        std::string input_dial_change_str = input_str.substr(1);
        int input_dial_change = std::stoi(input_dial_change_str);

        input_dial_change = input_dial_change % 100;

        if (first_char_str == "L")
        {
            dial -= input_dial_change;
        }
        else
        {
            dial += input_dial_change;
        }

        if (dial > 99)
        {
            dial = dial - 100;
        }
        if (dial < 0)
        {
            dial = dial + 100;
        }

        if (dial == 0)
        {
            zero_counter++;
        }

        writer.WriteLine(fmt::format("{}", dial));
    }

    writer.WriteLine(fmt::format("----------"));
    writer.WriteLine(fmt::format("zeroes: {}", zero_counter));
    writer.WriteLine(fmt::format("dial: {}", dial));
    writer.Close();

    fmt::println("------------");
    fmt::println("dial: {}", dial);
    fmt::println("zeroes: {}", zero_counter);
}
