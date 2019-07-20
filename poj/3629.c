#include<stdio.h>
#include<stdlib.h>

int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}

#define MAX 200000
int cards[MAX];
int mycards[100000];
int main() {
    int n, k, p, i, j, ii, mc=0;
    scanf("%d %d %d", &n, &k, &p);
    int head=0, tail=0;
    for (tail=0; tail<k; tail++) cards[tail] = tail+1;
    j = 0; for (i=0; i<k; i++) {
        if (j==n-1) {
            mycards[mc++] = cards[head];
        }
        j++; j %= n;
        head++; head %= MAX;
        for (ii=0; ii<p; ii++) {
            cards[tail++] = cards[head++];
            tail %= MAX; head %= MAX;
        }
    }
    qsort(mycards, mc, sizeof(mycards[0]), mycmp);
    for (i=0; i<mc; i++) printf("%d\n", mycards[i]);
    return 0;
}
