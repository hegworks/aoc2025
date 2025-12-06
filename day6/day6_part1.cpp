#include "../shared_lib/include/file_reader.hpp"
#include "../shared_lib/include/file_writer.hpp"
#include "../shared_lib/include/helpers.hpp"
#include "../shared_lib/include/chronometer.hpp"
#include "../shared_lib/external/fmt/include/fmt/core.h"

int main()
{
    fmt::println("day6_part1");
    fmt::println("------------");

    FileReader reader{};
    reader.LoadFile("input.txt");

    FileWriter writer("../day6/part1/output.txt");
    writer.WriteLine("day6_part1");

    Chronometer chronometer{"day6_part1"};

    const int total_line_count = reader.LineCount();
    for (int line_idx = 0; line_idx < total_line_count; ++line_idx)
    {
        std::string input_str = reader.Cin();
    }

    writer.Close();
}
