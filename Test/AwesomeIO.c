#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "thread.h"
void FilePrint(int id);

int main()
{
    printf("beginning...\n");
    clock_t begin = clock();
    int i, j, pid;
    for(i = 0; i < 20000; i++)
    {
        create(FilePrint);
    }
    join();
    printf("success!time:%fs\n", (float)(clock() - begin) / CLOCKS_PER_SEC);
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
