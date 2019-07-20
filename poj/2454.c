#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct {int i, c; }Cow;
Cow cows[180];

int mycmp(const void *a, const void *b) {
    return ((const Cow*)b)->c - ((const Cow *)a)->c;
}

int main() {
    int k, i, n, s1, s2, t, j;
    scanf("%d", &k);
    n = k*3;
    for (i=0; i<n; i++) {
        scanf("%d", &cows[i].c);
        cows[i].i = i+1;
    }
    qsort(cows, n, sizeof(cows[0]), mycmp);
    // for (i=0; i<n; i++) printf("%d:%d\n", cows[i].i, cows[i].c);
    n = k*2;
    s1=0; for (i=0; i<k; i++) s1 += cows[i].c;
    s2=0; for (i=k; i<n; i++) s2 += cows[i].c;
    n = 500*k+1;
    while(1) {
        if (s1>=n && s2>=n) break;
        i = rand() % k;
        j = rand() % k;
        s1 += (cows[j+k].c-cows[i].c);
        s2 += (cows[i].c-cows[j+k].c);
        t=cows[i].i; cows[i].i=cows[k+j].i;cows[k+j].i=t;
        t=cows[i].c; cows[i].c=cows[k+j].c;cows[k+j].c=t;
    }
    int s; s = 0; for (i=0; i<k; i++) s+=cows[i].c; if (s<=500*k) printf("error1! %d < %d\n", s, 500*k);
    s = 0; for (i=0; i<k; i++) s+=cows[i+k].c; if (s<=500*k) printf("error2! %d < %d\n", s, 500*k);
    n = k*3;
    for (i=0; i<n; i++) {
        printf("%d\n", cows[i].i);
    }
    return 0;
}
