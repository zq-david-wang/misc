#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int vs[100][100];
char flag[101];
int main() {
    int i, j, n, m, ci, cj, bi, bj;
    while(scanf("%d", &n)==1) {
        m =n;
        n = n*n;
        for (i=0; i<n; i++) for (j=0; j<n; j++) scanf("%d", &vs[i][j]);
        for (i=0; i<n; i++) {
            for (j=1; j<=n; j++) flag[j]=0;
            for (j=0; j<n; j++) {
                if (vs[i][j]==0) continue;
                if (flag[vs[i][j]]) break;
                flag[vs[i][j]]=1;
            }
            if (j<n) break;
        }
        if (i<n) { printf("INCORRECT\n"); continue; }
        for (i=0; i<n; i++) {
            for (j=1; j<=n; j++) flag[j]=0;
            for (j=0; j<n; j++) {
                if (vs[j][i]==0) continue;
                if (flag[vs[j][i]]) break;
                flag[vs[j][i]]=1;
            }
            if (j<n) break;
        }
        if (i<n) { printf("INCORRECT\n"); continue; }
        for (bi=0; bi<m; bi++) { for (bj=0; bj<m; bj++) {
            for (i=1; i<=n; i++) flag[i]=0;
            for (ci=0; ci<m; ci++){
                for (cj=0; cj<m; cj++) {
                    i = bi*m+ci; j=bj*m+cj;
                    if (vs[i][j]==0) continue;
                    if (flag[vs[i][j]]) break;
                    flag[vs[i][j]]=1;
                }
                if (cj<m) break;
            }
            if (ci<m) break;
        }
        if (bj<m) break;
        }
        if (bi<m) { printf("INCORRECT\n"); continue; }
        printf("CORRECT\n");
    }
    return 0;
}


