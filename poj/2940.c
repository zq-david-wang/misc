#include<stdio.h>

int vs[1000000];
int main() {
    int n, i;
    long long c, s;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        for (i=0; i<n; i++) scanf("%d", &vs[i]);
        c = 0; s=0;
        for (i=0; i<n; i++) {
            if (s>0) c+=s;
            else c-=s;
            s += vs[i];
        }
        printf("%lld\n", c);
    }
    return 0;
}
