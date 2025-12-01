#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class FileReader
{
public:
    void LoadFile(const std::string& path)
    {
        m_loaded_file_lines.clear();
        std::ifstream file(path);
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {
                m_loaded_file_lines.push_back(line);
            }
            file.close();
        }
        else
        {
            std::cout << "ERROR::Unable to open file " << path;
        }
    }

    std::string Cin() { return m_loaded_file_lines[line_num++]; }

    int LineCount() const { return static_cast<int>(m_loaded_file_lines.size()); }

private:
    std::vector<std::string> m_loaded_file_lines;
    int line_num = 0;
};
