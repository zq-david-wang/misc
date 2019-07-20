#include<stdio.h>


long long b1[1024], b2[1024];
int main() {
    long long n, m, t, c, *p1, *p2, *tp;
    int i, j;
    while(1) {
        scanf("%lld %lld", &n, &m);
        if (n==0&&m==0) break;
        n++; m++;
        p1=b1; p2=b2;
        if (n>m) { t=n; n=m; m=t; }
        if (n==1) c = 1;
        else if (n==2) c=m;
        else {
            for (i=0; i<n; i++) p1[i]=1;
            for (i=1; i<m; i++) {
                for (j=n-1; j>=0; j--) {
                    p2[j]=p1[j];
                    if (j<n-1) p2[j]+=p2[j+1];
                }
                tp=p1; p1=p2; p2=tp;
            }
            c = p1[0];
        }
        printf("%lld\n", c);
    }
    return 0;
}
