#include "../shared_lib/include/FileReader.h"
#include "../shared_lib/include/shared_lib.hpp"

#include <iostream>

int main()
{
    SharedLib sl{};

    FileReader fr{};
    fr.LoadFile("input.txt");

    std::cout << fr.Cin();

    printf("\n");
}
