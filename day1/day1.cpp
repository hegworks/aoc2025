#include "../shared_lib/include/FileReader.h"
#include "../shared_lib/include/shared_lib.hpp"

#include <iostream>

int main()
{
    SharedLib sl{};

    FileReader fr{};
    fr.LoadFile("input.txt");

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
    }

    printf("\n");
    printf("------------");
    printf("\n");
    printf("zeroes: %d", zero_counter);
    printf("\n");
    printf("dial: %d", dial);

    printf("\n");
}
