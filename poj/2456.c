#include<stdio.h>
#include<stdlib.h>

int pos[100000];
int dif[100000];

int mycmp(const void*a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}

int poss(int s, int c, int n) {
    int d = 0, i, cc=1;
    for (i=0; i<n-1; i++) {
        d += dif[i];
        if (d>=s) {
            d = 0;
            cc++;
            if (cc>=c) return 1;
        }
    }
    return 0;
}
int main() {
    int n, c, i;
    int l, h, m;
    scanf("%d %d", &n, &c);
    for (i=0; i<n; i++) scanf("%d", &pos[i]);
    qsort(pos, n, sizeof(pos[0]), mycmp);
    for (i=0; i<n-1; i++) dif[i] = pos[i+1]-pos[i];
    l = 0;
    h = pos[n-1]-pos[0];
    while(l<=h) {
        m = (l+h)/2;
        if (poss(m, c, n)){ if (l==m) break; l = m; }
        else h = m-1;
    }
    while (poss(l+1, c, n))l++;
    printf("%d\n", l);
    return 0;
}
