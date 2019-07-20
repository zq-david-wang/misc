#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char line[262144+4];
char buf[262144*4];
int gc;
int dfs(int nc, int zc, int d) {
    if (nc==zc) return line[0]==1;
    int r = 0;
    d /= 2;
    if (zc) r += dfs(nc-1, zc-1, d);
    int bi=gc; gc += (d*2);
    int i;
    for (i=0; i<d*2; i++) buf[bi+i]=line[i];
    for (i=0; i<d; i++) {
        line[i] += line[i+d];
        line[i] &= 1;
    }
    r += dfs(nc-1, zc, d);
    for (i=0; i<d*2; i++) line[i]=buf[bi+i];
    gc = bi;
    return r;
}
int main() {
    int ti, tc, i, n, k, c;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d %d %s", &n, &k, line);
        c = strlen(line);
        for (i=0; i<c; i++) line[i]-='0';
        gc = 0;
        i = dfs(n, n-k, c);
        printf("%d\n", i);
    }
    return 0;
}


