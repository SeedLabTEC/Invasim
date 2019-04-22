#include "include/Environment.h"

int main(int argc, char const *argv[])
{
    dprintf("\nInvasive Computing Simulator\n\n\n");

    srand(1);

    Environment *env_0 = new Environment(atoi(argv[1]),
                                         atoi(argv[2]),
                                         0.80,
                                         "/home/dennis/Documents/Invasim/bin",
                                         1);
    env_0->start_environment();

    dprintf("DEBUG: Running %s steps...\n", argv[3]);
    env_0->step(atoi(argv[3]));

    return 0;
}
