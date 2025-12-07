#include "../shared_lib/include/file_reader.hpp"
#include "../shared_lib/include/file_writer.hpp"
#include "../shared_lib/include/helpers.hpp"
#include "../shared_lib/include/chronometer.hpp"
#include "../shared_lib/external/fmt/include/fmt/core.h"

#include <unordered_set>

template <typename T>
class Grid
{
public:
    uint64_t m_row_count{0};
    uint64_t m_column_count{0};
    std::vector<std::vector<T>> m_grid{};

    Grid(uint64_t row_count, uint64_t column_count)
    {
        m_row_count = row_count;
        m_column_count = column_count;
        m_grid = std::vector<std::vector<T>>(row_count, std::vector<T>(column_count));
    }

    T Get(uint64_t row_idx, uint64_t column_idx) const { return m_grid[row_idx][column_idx]; }
    void Set(uint64_t row_idx, uint64_t column_idx, T val) { m_grid[row_idx][column_idx] = val; }
    T& At(uint64_t row_idx, uint64_t column_idx) { return m_grid[row_idx][column_idx]; }
    bool IsValid(uint64_t row_idx, uint64_t column_idx) const { return row_idx < m_row_count && column_idx < m_column_count; }

    void PrintFmt() const { fmt::println(GetPrintStr()); }

    std::string GetPrintStr(const std::string& spacer = "") const
    {
        std::string ret{};
        for (uint64_t row = 0; row < m_row_count; ++row)
        {
            for (uint64_t col = 0; col < m_column_count; ++col)
            {
                ret += fmt::format("{}{}", Get(row, col), spacer);
            }
            ret += "\n";
        }
        return ret;
    }
};

int main()
{
    fmt::println("day7_part2");
    fmt::println("------------");

    FileReader reader{};
    reader.LoadFile("input.txt");

    FileWriter writer("../day7/part2/output.txt");
    writer.WriteLine("day7_part2");

    Chronometer chronometer{"day7_part2"};

    // const uint64_t line_count = reader.LineCount();
    const uint64_t row_count = reader.LineCount();
    const uint64_t column_count = (uint64_t)reader.GetLine(0).size();

    Grid<char> grid(row_count, column_count);
    Grid<uint64_t> int_grid(row_count, column_count);

    for (uint64_t row_idx = 0; row_idx < row_count; ++row_idx)
    {
        std::string input_str = reader.Cin();
        for (uint64_t column_idx = 0; column_idx < column_count; ++column_idx)
        {
            grid.At(row_idx, column_idx) = input_str.at(column_idx);
        }
    }

    uint64_t unique_beam_count{0};
    uint64_t split_count{0};

    for (uint64_t row_idx = 0; row_idx < row_count; ++row_idx)
    {
        std::vector<uint64_t> row_beams_col_idx{};
        std::unordered_set<uint64_t> next_row_split_result_col_idx{};
        for (uint64_t col_idx = 0; col_idx < column_count; ++col_idx)
        {
            const char c = grid.Get(row_idx, col_idx);
            if (c == '.')
            {
                continue;
            }
            else if (c == 'S')
            {
                grid.Set(row_idx + 1, col_idx, '|');
                int_grid.Set(row_idx, col_idx, 1);
                int_grid.Set(row_idx + 1, col_idx, 1);
                break;
            }
            else if (c == '|')
            {
                row_beams_col_idx.push_back(col_idx);
                continue;
            }
        }
        for (uint64_t beam_idx = 0; beam_idx < (uint64_t)row_beams_col_idx.size(); ++beam_idx)
        {
            uint64_t beam_col_idx = row_beams_col_idx.at(beam_idx);
            if (grid.IsValid(row_idx + 1, beam_col_idx))
            {
                char below_beam_char = grid.Get(row_idx + 1, beam_col_idx);
                if (below_beam_char == '.' || below_beam_char == '|')
                {
                    grid.Set(row_idx + 1, beam_col_idx, '|');
                    int_grid.At(row_idx + 1, beam_col_idx) += int_grid.Get(row_idx, beam_col_idx);
                }
                else if (below_beam_char == '^')
                {
                    split_count++;
                    if (grid.IsValid(row_idx + 1, beam_col_idx - 1))
                    {
                        grid.Set(row_idx + 1, beam_col_idx - 1, '|');
                        int_grid.At(row_idx + 1, beam_col_idx - 1) += int_grid.Get(row_idx, beam_col_idx);
                        next_row_split_result_col_idx.insert(beam_col_idx - 1);
                    }
                    if (grid.IsValid(row_idx + 1, beam_col_idx + 1))
                    {
                        grid.Set(row_idx + 1, beam_col_idx + 1, '|');
                        int_grid.At(row_idx + 1, beam_col_idx + 1) += int_grid.Get(row_idx, beam_col_idx);
                        next_row_split_result_col_idx.insert(beam_col_idx + 1);
                    }
                }
                // else if (below_beam_char == '|')
                //{
                // int_grid.At(row_idx + 1, beam_col_idx) += int_grid.Get(row_idx, beam_col_idx);
                //}
            }
            else
            {
                break;
            }
        }
        unique_beam_count += (uint64_t)next_row_split_result_col_idx.size();

        writer.WriteLine(fmt::format("unique_beam_count: {}", unique_beam_count));
        writer.WriteLine(fmt::format("split_count: {}", split_count));
        writer.Write(grid.GetPrintStr());
        writer.WriteLine("");

        // fmt::println("unique_beam_count:{}", unique_beam_count);
        // grid.PrintFmt();
        // fmt::println("");
    }

    writer.WriteLine(fmt::format("unique_beam_count: {}", unique_beam_count));
    writer.WriteLine(fmt::format("split_count: {}", split_count));
    fmt::println("unique_beam_count: {}", unique_beam_count);
    fmt::println("split_count: {}", split_count);

    uint64_t timelines{0};
    uint64_t last_row_idx = row_count - 1;
    for (uint64_t col_idx = 0; col_idx < column_count; ++col_idx)
    {
        const uint64_t i = int_grid.Get(last_row_idx, col_idx);
        timelines += i;
    }

    writer.Write(int_grid.GetPrintStr(" "));

    writer.WriteLine(fmt::format("timelines: {}", timelines));
    fmt::println("timelines:{}", timelines);

    writer.Close();
}
