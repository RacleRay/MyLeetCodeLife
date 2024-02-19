#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// ===
// Context Switch test
// ===

// sudo perf sched record -- sleep 10
// sudo perf sched latency -s switch
// sudo perf sched timehist -p 'pid'

// vmstat 1  

// pidstat -w -p 'pid'

// == CPU affinity
// taskset -cp 0,1,2 'pid'
// taskset -c 0,1,2 a.out
// taskset -pc 'pid'
// taskset -a -c 1,2 ./a.out


int main() {
    printf("hello, pid=%d\n", getpid());

    while (1) {
        printf("begin sleep, pid = %d\n", getpid());
        usleep(1000);
    }

    return 0;
}