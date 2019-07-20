#include<stdio.h>
#include<stdlib.h>

int ls[20000];
int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}
int findi(int v, int s, int e) {
    int m, os=s;
    while(s<=e) {
        m = (s+e)/2;
        if (ls[m]>v) e=m-1;
        else {
            if (s==m) break;
            s=m;
        }
    }
    if (ls[s]>v) return 0;
    if (ls[s+1]<=v) s++;
    return s-os+1;
}
int main() {
    int n, i, s, c=0;
    scanf("%d %d", &n, &s);
    for (i=0; i<n; i++)scanf("%d", &ls[i]);
    qsort(ls, n, sizeof(ls[0]), mycmp);
    // for (i=0; i<n; i++) printf("%d ", ls[i]);printf("\n");
    for (i=0; i<n-1; i++) {
        if (ls[i]>=s) break;
        c += findi(s-ls[i], i+1, n-1);
    }
    printf("%d\n", c);
    return 0;
}
