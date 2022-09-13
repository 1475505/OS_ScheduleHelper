#include <stdio.h>
#include <unistd.h>

int x[1024][1024] = {0};

int main()
{
    int i, j, pid;
    for(i = 0; i < 10; i++)
    {
        pid = fork();
    }
    for(i = 0; i < 1024; i++)
    {
        for(j = 0; j < 1024; j++)
        {
            x[i][j] = pid;
        }
    }
    return 0;
}