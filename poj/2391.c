#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int cows[201], cap[201];
int map[201][201];
long long spath[201][201];
long long ddd[200*200+4];
char flag[404];
int mycmp(const void* a, const void *b) {
    long long va = *((const long long*)a);
    long long vb = *((const long long*)b);
    if (va>vb) return 1;
    if (va<vb) return -1;
    return 0;
}
void dij(int s, int n) {
    int i, pi; for (i=1; i<=n; i++) flag[i] = 0;
    long long p;
    spath[s][s] = 0;
    while(1) {
        p = -1;
        for (i=1; i<=n; i++) {
            if (flag[i]) continue;
            if (spath[s][i]==-1) continue;
            if (p==-1 || p>spath[s][i]) {
                p = spath[s][i];
                pi = i;
            }
        }
        if (p==-1) break;
        flag[pi] = 1;
        for (i=1; i<=n; i++) {
            if (flag[i]) continue;
            if (map[pi][i]==-1) continue;
            if (spath[s][i]==-1 || p+map[pi][i]<spath[s][i]) {
                spath[s][i] = p+map[pi][i];
            }
        }
    }
}

#define INF -1
int flow[404][404];
int fmap[404][404];
int fneic[404];
int fnei[404][404];
int rpath[404];
/*
char fflag[404];
char dfs(int s, int n) {
    if (s==n) return 1;
    int i, b; for(i=0; i<fneic[s]; i++) {
        b = fnei[s][i];
        if (fflag[b]) continue;
        if (flow[s][b] == fmap[s][b] && flow[b][s]==0) continue;
        rpath[b] = s;
        fflag[b] = 1;
        if (dfs(b, n)) return 1;
    }
    return 0;
}
char findpath(int n) {
    memset(fflag, 0, n+1);
    fflag[0] = 1;
    return dfs(0, n);
}
*/
int queue[404];
char findpath2(int n) {
    if (n>=404) printf("error\n");
    int h=0, t=0;
    int i, a, b;
    queue[h++] = 0;
    memset(flag, 0, n+1);
    flag[0] = 1;
    while(t<h) {
        a = queue[t++];
        for (i=0; i<fneic[a]; i++) {
            b = fnei[a][i];
            if (b<0 || b>n) printf("error\n");
            if (flag[b]) continue;
            if (flow[a][b] == fmap[a][b] && flow[b][a]==0) continue;
            rpath[b] = a;
            flag[b] = 1;
            if (b==n) return 1;
            queue[h++] = b;
        }
    }
    if (h>=sizeof(queue)/sizeof(queue[0])) printf("error\n");
    return 0;
}
long long maxflow(long long th, int n) {
    // build fmap
    int i, j;
    long long f, r=0;
    memset(flow, 0, sizeof(flow));
    memset(fmap, 0, sizeof(fmap));
    for (i=0; i<=n+n+1; i++) fneic[i] = 0;
    for (i=1; i<=n; i++) {
        fmap[0][i] = cows[i];
        fnei[0][fneic[0]++] = i;
        fnei[i][fneic[i]++] = 0;

        fmap[n+i][n+n+1] = cap[i];
        fnei[n+i][fneic[n+i]++] = n+n+1;
        fnei[n+n+1][fneic[n+n+1]++] = n+i;
    }
    for (i=1; i<=n; i++) {
        for (j=1; j<=n; j++) {
            if (spath[i][j]==-1) continue;
            if (spath[i][j]>th) continue;
            // fmap[i][j+n] = cows[i];
            fmap[i][j+n] = INF;
            fnei[i][fneic[i]++] = j+n;
            fnei[j+n][fneic[j+n]++] = i;
        }
    }
    // for (i=0; i<=n+1+n; i++) { for (j=0; j<=n+1+n; j++) printf("%d ", fmap[i][j]); printf("\n"); }
    int b, d, a;
    char m;
    while(1) {
        m = findpath2(n+n+1);
        if (m==0) break;
        b = n+n+1;
        f = -1;
        while(b != 0) {
            a = rpath[b];
            if (fmap[a][b]==INF) { b = a; continue; }
            if (fmap[a][b] > flow[a][b]) d =  fmap[a][b]-flow[a][b];
            else d = flow[b][a];
            if (f==-1 || f>d) f = d;
            b = a;
        }
        // printf("find path:%lld\n", f);
        r += f;
        b = n+n+1;
        while(b != 0) {
            a = rpath[b];
            if (fmap[a][b]==INF) flow[a][b] += f;
            else if (flow[a][b]+f>fmap[a][b]) flow[b][a] -= f;
            else flow[a][b] += f;
            b = a;
        }
    }
    // printf("maxflow for %lld, n %d is %lld\n", th, n, r);
    return r;
}
int main() {
    int f, p, i, j;
    int a, b, d;
    long long s=0, mf;
    scanf("%d %d", &f, &p);
    for (i=1; i<=f; i++) scanf("%d %d", &cows[i], &cap[i]);
    for (i=1; i<=f; i++) s += cows[i];
    memset(map, 0xff, sizeof(map));
    for (i=0; i<p; i++) {
        scanf("%d %d %d", &a, &b, &d);
        if (map[a][b]==-1 || map[a][b]>d) {
            map[a][b] = d;
            map[b][a] = d;
        }
    }
    memset(spath, 0xff, sizeof(spath));
    for (i=1; i<=f; i++) dij(i, f);
    // for (i=1; i<=f; i++) { for (j=1; j<=f; j++) printf("%lld ", spath[i][j]); printf("\n"); }
    int dc = 0; ddd[dc++] = 0;
    for (i=1; i<=f; i++) {
        for (j=i+1; j<=f; j++) {
            if (spath[i][j]==-1) continue;
            ddd[dc++] = spath[i][j];
        }
    }
    qsort(ddd, dc, sizeof(ddd[0]), mycmp);
    j=0; for (i=0; i<dc; i++) {
        if (i>0 && ddd[i-1]==ddd[i]) continue;
        if (j!=i) ddd[j] = ddd[i];
        j++;
    }
    dc = j;
    // for (i=0; i<dc; i++) printf("%lld ", ddd[i]); printf("\n");
    int  l, h, m;
    l = 0; h = dc-1;
    while(l<=h) {
        m = (l+h)/2;
        mf = maxflow(ddd[m], f);
        // printf("checking %lld, maxflow: %lld(s: %lld)\n", ddd[m], mf, s);
        if (mf>=s) {
            if (h==m) break;
            h = m;
        } else {
            l = m+1;
        }
    }
    if (h==dc-1 && l>h) printf("-1\n");
    else printf("%lld\n", ddd[m]);
    return 0;
}
