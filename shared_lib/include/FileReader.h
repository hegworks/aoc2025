#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class FileReader
{
public:
	void LoadFile(std::string path)
	{
		loadedFileLines.clear();
		std::ifstream file(path);
		if(file.is_open())
		{
			std::string line;
			while(std::getline(file, line))
			{
				loadedFileLines.push_back(line);
			}
			file.close();
		}
		else
		{
			std::cout << "ERROR::Unable to open file " << path;
		}
	}

	std::string Cin()
	{
		return loadedFileLines[readLine++];
	}

private:
	std::vector<std::string> loadedFileLines;
	int readLine = 0;
};
