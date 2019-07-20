#include<stdio.h>


int vs[10000];
int si[10000];
int main() {
    int n, i, s, j;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d", &vs[i]);
    for (i=0; i<n; i++) si[i]=-1;
    s=0; for (i=0; i<n; i++) {
        s+=vs[i]; s%=n;
        if (s==0) {
            printf("%d\n", i+1);
            for (j=0; j<=i; j++) printf("%d\n", vs[j]);
            break;
        }
        if (si[s]==-1) si[s]=i;
        else {
            j=si[s]+1;
            printf("%d\n", i-j+1);
            for (; j<=i; j++) printf("%d\n", vs[j]);
            break;
        }
    }
    return 0;
}
