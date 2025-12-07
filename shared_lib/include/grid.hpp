#pragma once

#include "../external/fmt/include/fmt/core.h"

#include <cstdint>
#include <vector>
#include <string>

template <typename T>
class Grid
{
public:
    std::uint64_t m_row_count{0};
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