#include<stdio.h>
#include<stdlib.h>

#define MAX 1000000
int dis[100][100], md[100][100];
char flag[100];
int ds[10000+4];

int mycmp(const void*a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}

void dij(int s, int n) {
    int i;  for (i=0; i<n; i++) {
        md[s][i] = MAX;
        flag[i] = 0;
    }
    md[s][s] = 0;
    int mind, mi;
    while(1) {
        mind = MAX;
        for (i=0; i<n; i++) {
            if (flag[i]) continue;
            if (mind > md[s][i]) {
                mind = md[s][i]; mi = i;
            }
        }
        if (mind == MAX) break;
        flag[mi] = 1;
        for (i=0; i<n; i++) {
            if (flag[i]) continue;
            if (dis[mi][i] < 0) continue;
            if (mind+dis[mi][i] < md[s][i]) md[s][i] = mind+dis[mi][i];
        }
    }
}
int main() {
    int n, i, p, c, j, k, m;
    scanf("%d", &n);
    for (i=1; i<=n; i++) {
        scanf("%d %d", &p, &c);
        for (j=0; j<c; j++) for (k=0; k<c; k++) scanf("%d", &dis[j][k]);
        for (j=0; j<c; j++) dij(j, c);
        m=0; for (j=0; j<c; j++) for (k=0; k<c; k++){
            if (k==j) continue;
            ds[m++] = md[j][k];
        }
        qsort(ds, m, sizeof(int), mycmp);
        // for (j=0; j<m; j++) printf("%d ", ds[j]);printf("\n");
        j = m*p/100; if (j*100<m*p)j++;
        j--;
        printf("Scenario #%d:\n%d\n\n", i, ds[j]);
    }
    return 0;
}
