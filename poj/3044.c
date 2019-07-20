#include<stdio.h>

char flag[50001];
int prev[50001];
int hs[50000];
int main() {
    int i,n, w, x, hi;
    scanf("%d %d", &n, &w);
    for (i=0; i<n; i++) {
        scanf("%d %d", &x, &hs[i]);    
    }
    prev[0] = -1;
    flag[0] = 1;
    for (i=1; i<n; i++) {
        flag[i] = 1;
        prev[i] = i-1;
        hi = prev[i];
        while(hi>=0) {
            if (hs[hi]==hs[i])  flag[hi] = 0;
            if (hs[hi]<hs[i]) break;
            hi = prev[hi];
        }
        prev[i] = hi;
    }
    w = 0;
    for (i=0; i<n; i++) if (flag[i]&&hs[i]>0) w++;
    printf("%d\n", w);
    return 0;
}
