#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int i, v;
}INode;
INode cows[10000];
char flag[10000];
// int ind[10000];
int ary[10000];

int mycmp(const void *a, const void *b) {
    return ((const INode*)a)->v - ((const INode*)b)->v;
}
int main() {
    int n, i, j, k, ac, mv;
    long long s = 0, ms, ms2;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &cows[i].v);
        cows[i].i = i;
        flag[i] = 0;
    }
    qsort(cows, n, sizeof(cows[0]), mycmp);
    // for (i=0; i<n; i++) ind[cows[i].i] = i;
    for (i=0; i<n; i++) {
        if (flag[i]) continue;
        ac=0; ary[ac++] = i; flag[i] = 1;
        ms = 0;
        mv = -1;
        while(1) {
            j = ary[ac-1];
            ms += cows[j].v;
            if (mv<0 || mv>cows[j].v) mv = cows[j].v;
            k = cows[j].i;
            if (flag[k]) break;
            flag[k] = 1;
            ary[ac++] = k;
        }
        // printf("group count %d, mv %d, ms %lld\n", ac, mv, ms);
        // in loop min 
        if (ac==1) {}
        else if (ac==2) s+=ms;
        else {
            ms2 = mv+cows[0].v+ms+cows[0].v*(ac-1)+cows[0].v;
            ms += mv*(ac-2);
            if (ms2<ms) ms = ms2;
            s += ms;
        }
    }
    printf("%lld\n", s);
    return 0;
}
