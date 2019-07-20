#include<stdio.h>

int hs[100002];
int ri[100002], li[100002];
int main() {
    int n, i, j;
    long long s, cs;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        for (i=1; i<=n; i++) scanf("%d", &hs[i]); hs[0]=0; hs[n+1]=0;
        li[0]=-1; li[1]=0;
        for (i=2; i<=n; i++) {
            j=i-1; while(j>0) {
                if (hs[j]<hs[i]) break;
                j = li[j];
            } li[i]=j;
        }
        ri[n+1]=-1; ri[n]=n+1;
        for (i=n-1; i>=1; i--) {
            j=i+1; while(j<=n) {
                if (hs[j]<hs[i]) break;
                j = ri[j];
            } ri[i]=j;
        }
        s=0; for (i=1; i<=n; i++) {
            cs=hs[i]; cs*=(ri[i]-li[i]-1);
            if (s<cs) s=cs;
        }
        printf("%lld\n", s);
    }
    return 0;
}
