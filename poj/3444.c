#include<stdio.h>

int vs[256];
int tvs[256];
int main() {
    int n, i, k;
    while(1) {
        scanf("%d", &n); if (n==0) break;
        for (i=0; i<n; i++) scanf("%d", &vs[i]);
        k=1; while(k<n) {
            for (i=0; i<k*2; i++) tvs[i]=vs[i];
            for (i=0; i<k; i++) {
                vs[i*2] = (tvs[i]+tvs[i+k])/2;
                vs[i*2+1] = (tvs[i]-tvs[i+k])/2;
            }
            k *= 2;
        }
        for (i=0; i<n; i++) {
            if (i>0) printf(" ");
            printf("%d", vs[i]);
        } printf("\n");
    }
    return 0;
}
