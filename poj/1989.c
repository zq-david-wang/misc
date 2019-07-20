#include<stdio.h>
char mark[10001];
int main() {
    int n, k, i, a, c, r=0, j;
    scanf("%d %d", &n, &k);
    for (i=1; i<=k; i++) mark[i] = 0;
    c = 0;
    for (i=0; i<n; i++) {
        scanf("%d", &a);
        if (mark[a]) continue;
        mark[a] = 1;
        c++;
        if (c==k) {
            r++;
            c = 0;
            for (j=1; j<=k; j++) mark[j] = 0;
        }
    }
    r++;
    printf("%d\n", r);
    return 0;
}
