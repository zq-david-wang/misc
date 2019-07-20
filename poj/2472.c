#include<stdio.h>
#include<string.h>

char chs[101][101];
double md[101];
char flag[101];

void dij(int s, int n) {
    int i; for(i=1; i<=n; i++) { 
        flag[i] = 0;    
        md[i] = -1;
    }
    md[s] = 1;
    double mmd, nd;
    int mmi;
    while (1) {
        mmd = -1;
        for (i=1; i<=n; i++) {
            if (flag[i]) continue;
            if (md[i] < 0) continue;
            if (mmd < md[i]) {
                mmd = md[i];
                mmi = i;
            }
        }
        if (mmd<0) break;
        flag[mmi] = 1;
        for (i=1; i<=n; i++) {
            if (flag[i]) continue;
            if (chs[mmi][i] < 0) continue;
            nd = mmd*chs[mmi][i]/100;
            if (nd > md[i]) md[i] = nd;
        }
    }

}
int main() {
    int n, m, i;
    int a, b, p;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        scanf("%d", &m);
        memset(chs, 0xff, sizeof(chs));
        for (i=0; i<m; i++) {
            scanf("%d %d %d", &a, &b, &p);
            chs[a][b] = p;
            chs[b][a] = p;
        }
        dij(1, n);
        printf("%.6f percent\n", md[n]*100);
    }
    return 0;
}
