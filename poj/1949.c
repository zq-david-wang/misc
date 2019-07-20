#include<stdio.h>

int ts[10001];
int main() {
    int n, i, j, m, k;
    scanf("%d", &n);
    int mmt = 0, mt, ct;
    for (i=1; i<=n; i++) {
        ts[i] = 0;
        scanf("%d %d", &ct, &m);
        mt = 0;
        for (j=0; j<m; j++) {
            scanf("%d", &k);
            if (mt<ts[k]) mt = ts[k];
        }
        ts[i] = mt+ct;
        if (mmt<ts[i]) mmt = ts[i];
    }
    printf("%d\n", mmt);
    return 0;
}
