#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char pn[20][5][8];
char rs[8];
char mm[5][8];
int cs[5];
int gn;
void dfs(int s, int c, int cn, int sn) {
    // printf("dfs %d,%d  %d,%d\n", s, c, cn, sn);
    int i, j, k;
    if (c==cn||sn-s==cn-c) {
        for (i=c; i<cn; i++) {
            rs[i]=s++;
        }
        for (i=0; i<5; i++) for (j=0; j<5; j++) mm[i][j]=0;
        for (k=0; k<cn; k++) {
            for (i=0; i<5; i++) for (j=0; j<5; j++) if (pn[rs[k]][i][j]) mm[i][j]=1;
        }
        mm[2][2]=0;
        char ccs[5];
        for (i=0; i<5; i++) ccs[i]=0;
        for (i=0; i<5; i++) for (j=0; j<5; j++) ccs[i]+=mm[j][i];
        int cc=0;
        for (i=0; i<5; i++) if (ccs[i]>cs[i]) cc+=(ccs[i]-cs[i]);
        if (gn<0||gn>cc) gn=cc;
        return;
    }
    rs[c]=s;
    dfs(s+1, c+1, cn, sn);
    dfs(s+1, c, cn, sn);
}
int main() {
    int tc, ti, i, j, k, x, y;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        for (i=0; i<5; i++) scanf("%d", &cs[i]);
        scanf("%d %d", &x, &y);
        for (i=0; i<5; i++) {
            for (j=0; j<x; j++) {
                scanf("%s", pn[j][i]);
                for (k=0; k<5; k++) {
                    if (pn[j][i][k]=='X') pn[j][i][k]=1;
                    else pn[j][i][k]=0;
                }
            }
        }
        gn = -1;
        dfs(0, 0, y, x);
        printf("%d\n", gn);
    }
    return 0;
}


