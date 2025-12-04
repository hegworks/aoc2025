#include "../shared_lib/include/file_reader.hpp"
#include "../shared_lib/include/file_writer.hpp"
#include "../shared_lib/include/helpers.hpp"
#include "../shared_lib/external/fmt/include/fmt/core.h"

#define PART_2

int GetExistingNeighbourCount(int row_idx, int column_idx, int deepness, const std::vector<std::vector<int>>& map_2d)
{
    const int column_size = (int)map_2d.size();
    const int row_size = (int)map_2d.at(0).size();

    const int initial_x = std::max(0, column_idx - deepness);
    int y = std::max(0, row_idx - deepness);
    int x = initial_x;
    int neighbours_found{0};
    while (true)
    {
        if ((!(x == column_idx && y == row_idx)) && map_2d[y][x] == 1)
        {
            neighbours_found++;
        }

        x++;
        if (x == column_size || x > column_idx + deepness)
        {
            x = initial_x;
            y++;
            if (y == row_size || y > row_idx + deepness)
            {
                break;
            }
        }
    }
    return neighbours_found;
}

int main()
{
    fmt::println("day4_part1");
    fmt::println("------------");

    FileReader fr{};
    fr.LoadFile("input.txt");

    FileWriter writer("../day4/part1/output.txt");
    writer.WriteLine("day4_part1");

    const int row_count = fr.LineCount();
    const int column_count = (int)fr.GetLine(0).size();

    std::vector map_2d(row_count, std::vector<int>(column_count));

    for (int row_idx = 0; row_idx < row_count; ++row_idx)
    {
        std::string input_str = fr.Cin();
        for (int column_idx = 0; column_idx < column_count; ++column_idx)
        {
            map_2d[row_idx][column_idx] = input_str.at(column_idx) == '@' ? 1 : 0;
        }
    }

    int found_count{0};

    for (int row_idx = 0; row_idx < row_count; ++row_idx)
    {
        for (int column_idx = 0; column_idx < column_count; ++column_idx)
        {
            if (map_2d[row_idx][column_idx] == 1)
            {
                const int found_neighbors_count = GetExistingNeighbourCount(row_idx, column_idx, 1, map_2d);
                if (found_neighbors_count < 4)
                {
#if defined(PART_2)
                    map_2d[row_idx][column_idx] = 0;
                    row_idx = 0;
                    column_idx = 0;
#endif
                    found_count++;
                }
            }
        }
    }

    writer.Close();

    fmt::println(fmt::format("{}", found_count));
}
