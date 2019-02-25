#include "include/Environment.h"
#include "include/Debug.h"

#include <iostream>

int main(int argc, char const *argv[])
{
    dprintf("\nInvasive Computing Simulator\n\n\n");

    Environment *env_0 = new Environment(atoi(argv[1]));
    env_0->start_environment();

    dprintf("DEBUG: Running %s steps...\n", argv[2]);
    env_0->step(atoi(argv[2]));

    return 0;
}
