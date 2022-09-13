#include<time.h>
#include<stdio.h>
#include<pthread.h>

#define UINT64 unsigned long long
#define INTENSIVE_WORK  UINT64(*)(const UINT64)
#define TNUM 4
#define NUM 5000000000

struct sNum{
    UINT64 startNum;
    UINT64 nNum;
    UINT64 sum;
};

void *work(void *arg){
    struct sNum *_sNum=(struct sNum *)arg;
    UINT64 temp=0; //使用临时变量进行密集计算，提高速度
    for(; _sNum->startNum<=_sNum->nNum; ++(_sNum->startNum)) temp+=_sNum->startNum;
    _sNum->sum=temp;
    // printf("thread %llu: sum:%llu\n",pthread_self(), _sNum->sum);
}

UINT64 multiThreadsCal(const UINT64 nNum){
    UINT64 field=nNum/TNUM;
    pthread_t pt[TNUM];
    struct sNum _sNum[TNUM];
    for(int i=0; i<TNUM; ++i){
        _sNum[i].sum=0;
        _sNum[i].startNum=field*i+1;
        _sNum[i].nNum=field*(i+1);
        int ret=pthread_create(&pt[i], NULL, work, &_sNum[i]);
        if(ret!=0){
            printf("Create threads error.\n");
            return -1;
        }
    }
    UINT64 SUM=0;
    for(int i=0; i<TNUM; ++i){
        pthread_join(pt[i], NULL);
        SUM+=_sNum[i].sum;
    }
    return SUM;
}

int main()
{
    clock_t beginTime=clock();
    printf("calculating...\n");
    printf("%llu\n",multiThreadsCal(NUM));
    printf("time: %ld ms.\n", (clock()-beginTime)/1000);
    getchar();
    return 0;
}
//gcc .\compute-intensive-linux.c -o test -lpthread
