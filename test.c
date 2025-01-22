#include <unistd.h>
#include <stdio.h>

int main()
{
    for (size_t i = 0; i < 100; i++)
    {
        write(1, "\a", 1);
        usleep(10000);
    }
    
}