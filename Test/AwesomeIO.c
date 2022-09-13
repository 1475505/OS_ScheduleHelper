#include <stdio.h>
#include <unistd.h>
#include "thread.h"
void FilePrint(int id);

int main()
{
    
    int i, j, pid;
    for(i = 0; i < 8000; i++)
    {
        create(FilePrint);
    }
    join();
    return 0;
}

void FilePrint(int id)
{
    int i;
    FILE * fp = fopen("test.txt", "w");
    for(i = 0; i < 8192; i++)
    {
        fprintf(fp, "%d\n", id);
    }
    fclose(fp);
}
// gcc AwesomeIO.c -lpthread
// ./a.out