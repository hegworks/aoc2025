#include "../shared_lib/include/FileReader.h"
#include "../shared_lib/include/FileWriter.hpp"
#include "../shared_lib/include/shared_lib.hpp"
#include "../shared_lib/external/fmt/include/fmt/core.h"

int main()
{
    fmt::println("Day2");
    fmt::println("------------");

    SharedLib sl{};

    FileReader fr{};
    fr.LoadFile("input.txt");

    FileWriter writer("../day2/output.txt");
    writer.WriteLine("Day2");

    int dial{50};
    int zero_at_end_counter{0};
    int zero_during_counter{0};

    const int total_line_count = fr.LineCount();
    for (int line_idx = 0; line_idx < total_line_count; ++line_idx)
    {
        std::string input_str = fr.Cin();
        std::string first_char_str{input_str.at(0)};
        std::string input_dial_change_str = input_str.substr(1);
        int input_dial_change = std::stoi(input_dial_change_str);

        for (int i = 0; i < input_dial_change; ++i)
        {
            if (first_char_str == "L")
            {
                dial--;
                if (dial < 0)
                {
                    dial = 99;
                }
            }
            else
            {
                dial++;
                if (dial > 99)
                {
                    dial = 0;
                }
            }

            if (dial == 0)
            {
                zero_during_counter++;
            }
        }

        writer.WriteLine(fmt::format("{}", dial));
    }

    writer.WriteLine(fmt::format("----------"));
    writer.WriteLine(fmt::format("dial: {}", dial));
    writer.WriteLine(fmt::format("zero_during_counter: {}", zero_during_counter));
    writer.WriteLine(fmt::format("zero_at_end_counter: {}", zero_at_end_counter));
    writer.WriteLine(fmt::format("zeroes_total: {}", zero_at_end_counter + zero_during_counter));
    writer.Close();

    fmt::println("------------");
    fmt::println("dial: {}", dial);
    fmt::println("zero_during_counter: {}", zero_during_counter);
    fmt::println("zero_at_end_counter: {}", zero_at_end_counter);
    fmt::println("zeroes_total: {}", zero_at_end_counter + zero_during_counter);
}
