#include<stdio.h>

char seq[8][8];
char flag[8];
int gn, gl;
char buf[64];
char len[8];
void dfs(int c, int l) {
    if (c==gn) {
        if (gl>l) gl = l;
        return;
    }
    int i, j, k, m; for (i=0; i<gn; i++) {
        if (flag[i]) continue;
        flag[i] = 1;
        m = l; if (m>len[i]) m = len[i];
        for (j=m; j>=0; j--) {
            for (k=0; k<j; k++) {
                if (buf[l-j+k] != seq[i][k]) break;
            }
            if (k==j)break;
        }
        for (j=k; j<len[i]; j++) buf[l+j-k] = seq[i][j];
        dfs(c+1, l+len[i]-k);
        flag[i] = 0;
    }
}
int main() {
    int n, i, j;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%s", seq[i]);
        j = 0; while(seq[i][j]!=0) j++;
        len[i] = j;
        flag[i] = 0;
    }
    gn = n;
    gl = 1024;
    dfs(0, 0);
    printf("%d\n", gl);
    return 0;
}
