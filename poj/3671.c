#include<stdio.h>


int cs1[30002], cs2[30002];
int main() {
    int n, i, p;
    int c1=0, c2=0;
    scanf("%d", &n);
    cs1[0] = cs2[0] = 0;
    for (i=0; i<n; i++) {
        scanf("%d", &p);
        if (p==1) c1++;
        else c2++;
        cs1[i+1] = c1;
        cs2[i+1] = c2;
    }
    int mc = n, c;
    for (i=0; i<=n; i++) {
        c = cs2[i]+ (c1-cs1[i]);
        if (c<mc) mc = c;
    }
    printf("%d\n", mc);

    return 0;
}
