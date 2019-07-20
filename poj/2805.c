#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char map[5][8];
char dp[2097152];
int calc(char (*m)[8]) {
    int s=0, i, j;
    for (i=0; i<5; i++) for (j=0; j<5; j++) {
        if (m[i][j]=='#') continue;
        s=s*2+m[i][j];
    }
    return s;
}
void build(int s, char (*m)[8]) {
    int i, j;
    for (i=4; i>=0; i--) for (j=4; j>=0; j--) {
        m[i][j] = map[i][j];
        if (m[i][j]=='#') continue;
        m[i][j]=s&1; s>>=1;
    }
}
char dfs(int s) {
    if (dp[s]!=-1) return dp[s];
    char tmap[5][8];
    build(s, tmap);
    int i, j, r=0, t, ts;
    // for (i=0; i<5; i++) { for (j=0;j<5; j++) printf("%d ", tmap[i][j]); printf("\n"); }
    for (i=0; i<5; i++) for (j=0; j<5; j++) if (tmap[i][j]==1) r++;
    for (i=0; i<5; i++) for (j=0; j<5; j++) {
        if (tmap[i][j]!=1) continue;
        if (i>1&&tmap[i-1][j]==1&&tmap[i-2][j]==0) {
            tmap[i][j]=0; tmap[i-1][j]=0; tmap[i-2][j]=1;
            ts = calc(tmap);
            t = dfs(ts); if (t<r)r=t;
            tmap[i][j]=1; tmap[i-1][j]=1; tmap[i-2][j]=0;
        }
        if (i<3&&tmap[i+1][j]==1&&tmap[i+2][j]==0) {
            tmap[i][j]=0; tmap[i+1][j]=0; tmap[i+2][j]=1;
            ts = calc(tmap);
            t = dfs(ts); if (t<r)r=t;
            tmap[i][j]=1; tmap[i+1][j]=1; tmap[i+2][j]=0;
        }
        // 
        if (j>1&&tmap[i][j-1]==1&&tmap[i][j-2]==0) {
            tmap[i][j]=0; tmap[i][j-1]=0; tmap[i][j-2]=1;
            ts = calc(tmap);
            t = dfs(ts); if (t<r)r=t;
            tmap[i][j]=1; tmap[i][j-1]=1; tmap[i][j-2]=0;
        }
        if (j<3&&tmap[i][j+1]==1&&tmap[i][j+2]==0) {
            tmap[i][j]=0; tmap[i][j+1]=0; tmap[i][j+2]=1;
            ts = calc(tmap);
            t = dfs(ts); if (t<r)r=t;
            tmap[i][j]=1; tmap[i][j+1]=1; tmap[i][j+2]=0;
        }
    }
    dp[s]=r;
    return r;
}
int main() {
    int tc, ti, i, j, s, k;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        s=0; k=1;
        for (i=0; i<5; i++) {
            scanf("%s", map[i]);
            for (j=0; j<5; j++) {
                if (map[i][j]=='#') continue;
                if (map[i][j]=='.') s=s*2;
                else s=s*2+1;
                k*=2;
            }
        }
        memset(dp, 0xff, k*sizeof(dp[0]));
        i = dfs(s);
        printf("The best case ends with %d pegs.\n", i);
    }
    return 0;
}


