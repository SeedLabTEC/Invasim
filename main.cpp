/*// bernoulli_distribution::param
#include <iostream>
#include <random>
using namespace std;
int main()
{
  std::default_random_engine generator;
  std::bernoulli_distribution d1(0.7);
  std::bernoulli_distribution d2(d1.param());
  cout << d1 << endl;
  cout << d2 << endl;

  // print two independent values:
  std::cout << std::boolalpha;
  std::cout << d1(generator) << std::endl;
  std::cout << d2(generator) << std::endl;

  return 0;
}*/
#include "include/Environment.h"

int main(int argc, char const *argv[])
{
    dprintf("\nInvasive Computing Simulator\n\n\n");

    srand(1);

    Environment *env_0 = new Environment(atoi(argv[1]),
                                         atoi(argv[2]),
                                         0.80,
                                         "/home/dennis/Documents/Invasim/bin");
    env_0->start_environment();

    dprintf("DEBUG: Running %s steps...\n", argv[3]);
    env_0->step(atoi(argv[3]));

    return 0;
}
