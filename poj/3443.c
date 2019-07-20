#include<stdio.h>
#include<string.h>

char mark[500];
char lmark[26];
char seg[3][26];
int gs, gn, gl, gtc;
int sticks[3], cs[3];
int ss[16];
char flag[3][16];
int dfs2(int r, int c, int l) {
    if (c==cs[r]) { r++; c=0; l=0;}
    if (r==3) return 1;
    int i, nl, tt; for (i=0; i<cs[r]; i++) {
        if (flag[r][i]) continue;
        nl = l+seg[r][i];
        if (nl<sticks[0] && mark[nl]) continue;
        mark[nl]=1;
        flag[r][i]=1;
        tt = dfs2(r, c+1, nl);
        flag[r][i]=0;
        mark[nl]=0;
        if (tt) return 1;
    }
    return 0;
}
void verify() {
    if (dfs2(0, 0, 0)) gl = sticks[0];
}
void dfs(int s) {
    if (s>=gn) {
        if (gtc>5) {
            char sl = (sticks[0]==sticks[1]&&sticks[1]==sticks[2]);
            if (sl) {
                if (cs[0]>1&&cs[1]>1&&cs[2]>1) {
                    if (gl<sticks[0]) {
                        verify();
                    }
                }
            }
        }
        return;
    }
    char sm = lmark[ss[s]];
    int i, tl; for (i=sm; i<3; i++) {
        tl = sticks[i]+ss[s];
        if (tl>gs) continue;
        sticks[i] += ss[s];
        seg[i][cs[i]++] = ss[s];
        lmark[ss[s]]=i;
        gtc++;
        dfs(s+1);
        sticks[i] -= ss[s];
        cs[i]--;
        gtc--;
        if (gtc==0) break;
    }
    lmark[ss[s]]=3;
    dfs(s+1);
    lmark[ss[s]]=sm;

}
int main() {
    int n, i, s, ci=0, j, v;
    memset(flag, 0, sizeof(flag));
    memset(mark, 0, sizeof(mark));
    while(1) {
        scanf("%d", &n); if (n==0) break; ci++;
        s=0; for (i=0; i<n; i++) {
            scanf("%d", &v); s += v; ss[i]=v;
        }
        for (i=0; i<3; i++) cs[i]=sticks[i]=0;
        for (i=0; i<=25; i++) lmark[i]=0;
        gs = s/3; gn=n; gl=0; gtc=0;
        if (n>=6) dfs(0);
        printf("Case %d: %d\n", ci, gl);
    }
    return 0;
}
