#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    /* inline assembly */
    //asm volatile("ecall");
    /* write something to stdout */
    printf("Counting\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", i);        
    }
    float a = 25.0;
    float b = 2.0;
    float c = (a / b) * (b / a) * (2.05 * b * a);
    printf("Program done! %f\n", c);
    return EXIT_SUCCESS;
}
