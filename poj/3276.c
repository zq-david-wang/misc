#include<stdio.h>

char bs[5000];
char ms[5000];
int main() {
    int n, i, j, c, k, m=0xffffff, cc;
    char b[8];
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%s", b);
        if (b[0]=='B')bs[i] = 1;
        else bs[i] = 0;
    }
    for (i=n; i>=1; i--) {
        c = 0; cc = 0;
        for (j=0; j<=n-i; j++) {
            ms[j] = 0;
            if (j>=i) c-=ms[j-i];
            if (((bs[j]+c)&1) == 1) {
                c++;
                cc++;
                ms[j] = 1;
            }
        }
        for (; j<n; j++) {
            if (j>=i) c-=ms[j-i];
            if (((bs[j]+c)&1)==1) break;
        }
        if (j==n) {
            if (cc<=m) {
                m = cc;
                k = i;
            }
        }
    }
    printf("%d %d\n", k, m);
    return 0;
}
