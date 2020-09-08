#include "include/Environment.h"

int main(int argc, char const *argv[])
{
    dprintf("\nInvasive Computing Simulator\n\n\n");

    srand(1);

    Environment *env_0 = new Environment(atoi(argv[1]),
                                         atoi(argv[2]),
                                         0.80,
                                         "/home/jerodso/Invasim/Invasim/bin",
                                         1);
    env_0->start_environment();

    dprintf("DEBUG: Running %s steps...\n", argv[3]);
    env_0->step(atoi(argv[3]));

    return 0;
}
// // Remove a file
// #include <iostream>
// #include <fstream>
// #include <stdio.h> //for remove( ) and rename( )

// int main(void)
// {
//     std::string file;
//     std::cout << "Enter name of file to delete: ";
//     std::cin >> file;
//     if (remove(file.c_str()) != 0)
//         std::cout << "Remove operation failed" << std::endl;
//     else
//         std::cout << file << " has been removed." << std::endl;
//     return 0;
// }
