#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

#define NICE_0_LOAD 1024
#define NR_RUNNING 8
#define TIME_SLICE 10
#define TIME_EXEC 100

const unsigned long sched_prio_to_wmult[40] = {
 /* -20 */     48388,     59856,     76040,     92818,    118348,
 /* -15 */    147320,    184698,    229616,    287308,    360437,
 /* -10 */    449829,    563644,    704093,    875809,   1099582,
 /*  -5 */   1376151,   1717300,   2157191,   2708050,   3363326,
 /*   0 */   4194304,   5237765,   6557202,   8165337,  10153587,
 /*   5 */  12820798,  15790321,  19976592,  24970740,  31350126,
 /*  10 */  39045157,  49367440,  61356676,  76695844,  95443717,
 /*  15 */ 119304647, 148102320, 186737708, 238609294, 286331153,
};

static unsigned long __calc_delta(unsigned long delta_exec, unsigned long weight, unsigned int inv_weight)
{
    unsigned long fact = weight;
    int shift = 32;

    /* hint to use a 32x32->64 mul */
    fact = (unsigned long)(unsigned int)fact * inv_weight;

    while (fact >> 32)
    {
        fact >>= 1;
        shift--;
    }

    return (unsigned long)(((unsigned int)delta_exec * fact) >> shift);
}

struct task
{
    int pid;
    unsigned long delta_exec;
    unsigned long vruntime;
    int prior;
    unsigned long weight;
    unsigned long inv_weight;
    struct task *next;
};

int main()
{
    struct bst_node *root = NULL;

    struct task tasks[NR_RUNNING];

    for (int i = 0; i < NR_RUNNING; ++i)
    {
        struct task temp = {
            .pid = i,
            .inv_weight = sched_prio_to_wmult[20 + i]};
        tasks[i] = temp;
        root = insert(root, temp.pid, 0);
    }

    while (root)
    {
        int pid = delete_min(&root);

        printf("running pid %d task!\n", pid);

        tasks[pid].vruntime += __calc_delta(TIME_SLICE, NICE_0_LOAD, tasks[pid].inv_weight);
        tasks[pid].delta_exec += TIME_SLICE;

        printf("current pid %d vruntime: %ld\n",pid , tasks[pid].vruntime);

        if (tasks[pid].delta_exec < TIME_EXEC)
            root = insert(root, pid, tasks[pid].vruntime);
        else
            printf("pid %d task finish\n", pid);

    }

    // destroy_tree(root);

    return 0;
}