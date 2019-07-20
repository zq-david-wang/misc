#include<stdio.h>

int xs[771], ys[771];
int main() {
    int n, i, j, k, c=0;
    int dx, dy;
    scanf("%d", &n);
    for (i=1; i<=n; i++) {
        scanf("%d %d", &xs[i], &ys[i]);
    }
    for (i=1; i<n; i++) {
        for (j=i+1; j<n; j++) {
            dx = xs[j]-xs[i];
            dy = ys[j]-ys[i];
            for (k=j+1; k<=n; k++) {
               if (dy*(xs[k]-xs[j])==dx*(ys[k]-ys[j])) c++; 
            }
        }
    }
    printf("%d\n", c);
    for (i=1; i<n; i++) {
        for (j=i+1; j<n; j++) {
            dx = xs[j]-xs[i];
            dy = ys[j]-ys[i];
            for (k=j+1; k<=n; k++) {
               if (dy*(xs[k]-xs[j])==dx*(ys[k]-ys[j])) {
                   printf("%d %d %d\n", i, j, k);
               }
            }
        }
    }
    return 0;
}
