#include<stdio.h>

int map[52][52];
int rmap[52][52];
int flow[52][52];
int cap[52][52];
int parse(char *b, int n) {
    if (b[0]=='+') return 0;
    if (b[0]=='-') return n+1;
    n=0; int i=0; while(b[i]) {
        n=n*10+b[i]-'0'; i++;
    }
    return n;
}
int nei[52][52];
int neic[52];
char path[100], flag[100];
int gcap;
char dfs(int s, int e, int pc, int charge) {
    int i;
    if (s==e) {
        gcap += charge;
        for (i=0; i<pc-1; i++) cap[path[i]][path[i+1]] += charge;
        return 1;
    }
    int b, cc; for (i=0; i<neic[s]; i++) {
        b = nei[s][i];
        cc = map[s][b]; if (cc<charge) cc=charge;
        path[pc]=b;
        if (dfs(b, e, pc+1, cc)==0) return 0;
    }
    return neic[s]>0;
}

int dfs2(int s, int e, int cap) {
    if (s==e) return cap;
    int i, b, d; for (i=0; i<neic[s]; i++) {
        b = nei[s][i];
        if (flag[b]) continue;
        if (flow[b][s]) d=flow[b][s];
        else d=rmap[s][b]-flow[s][b];
        if (d==0) continue;
        if (d>cap) d=cap;
        flag[b]=1; path[b]=s;
        d = dfs2(b, e, d);
        if (d) return d;
    }
    return 0;
}
#define INF 0x7ffffff
int findpath(int s, int e) {
    int i; for (i=0; i<=51; i++) flag[i]=0;
    flag[s]=1;
    return dfs2(s, e, INF);
}
int maxflow(int s, int e) {
    int r=0, f, a, b;
    while(1) {
        f = findpath(s, e);
        if (f==0) break;
        r+=f;
        b=e;
        while(b!=s) {
            a=path[b];
            if (flow[b][a]) flow[b][a]-=f;
            else flow[a][b]+=f;
            b=a;
        }
    }
    return r;
}
int main() {
    int n, m, i, j, a, b, c;
    char b1[16], b2[16];
    while(1) {
        scanf("%d %d", &n, &m); if (n==0&&m==0) break;
        for (i=0; i<=n+1; i++) for (j=0; j<=n+1; j++) cap[i][j]=map[i][j]=0;
        for (i=0; i<=n+1; i++) { neic[i]=0;}
        for (i=0; i<m; i++) {
            scanf("%s %s %d", b1, b2, &c);
            a=parse(b1, n); b=parse(b2, n);
            map[a][b]=c;
            nei[a][neic[a]++] = b;
        }
        path[0]=0; gcap=0;
        a = dfs(0, n+1, 1, 0);
        if (a==0) printf("impossible\n");
        else {
            // build 
            for (i=0; i<=n+1; i++) { neic[i]=0;}
            for (i=0; i<=n+1; i++) {
                for (j=0; j<=n+1; j++) { 
                    if (cap[i][j]<map[i][j]) { j=-1; break; }
                    rmap[j][i]=cap[i][j]-map[i][j];
                    flow[i][j]=0;
                    if (rmap[j][i]) {
                        nei[i][neic[i]++]=j;
                        nei[j][neic[j]++]=i;
                    }
                }
                if (j==-1) break;
            }
            if (j==-1) printf("impossible\n");
            else {
                // for (i=0; i<=n+1; i++) { for (j=0; j<=n+1; j++) printf("%d ", rmap[i][j]); printf("\n"); }
                gcap -= maxflow(n+1, 0);
                printf("%d\n", gcap);
            }
        }
    }
    return 0;
}
