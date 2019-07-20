#include<stdio.h>

int map[100][100];
int dis[100][100];
char flag[100][100];
int heapi[100][100];
#define INF 0x7fffffff
typedef struct {short r, c;}HNode;
HNode heap[100*100];
int hpc;
char step[4][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
};
void heapify(int s) {
    int ms=s, ns;
    ns = s*2+1;
    if (ns>=hpc) return;
    if (dis[heap[ms].r][heap[ms].c]>dis[heap[ns].r][heap[ns].c]) ms=ns;
    ns = s*2+2;
    if (ns<hpc && dis[heap[ms].r][heap[ms].c]>dis[heap[ns].r][heap[ns].c]) ms=ns;
    if (ms==s) return;
    HNode t;
    t = heap[ms]; heap[ms]=heap[s]; heap[s] = t;
    heapi[heap[ms].r][heap[ms].c] = ms;
    heapi[heap[s].r][heap[s].c] = s;
    heapify(ms);
}

void adjust(int s) {
    HNode t;
    int p;
    while(s>0) {
        p = (s-1)/2;
        if (dis[heap[s].r][heap[s].c]>=dis[heap[p].r][heap[p].c]) break;
        t = heap[s]; heap[s] = heap[p]; heap[p] = t;
        heapi[heap[p].r][heap[p].c] = p;
        heapi[heap[s].r][heap[s].c] = s;
        s = p;
    }
}
int check(int l, int n) {
    int i, j;
    HNode p;
    hpc = 0;
    for (i=0; i<n; i++) for (j=0; j<n; j++) { 
        dis[i][j] = INF;
        flag[i][j] = 0;
        heapi[i][j]=hpc;
        heap[hpc].r = i;
        heap[hpc].c = j;
        hpc++;
    }
    dis[n-1][n-1] = map[n-1][n-1];
    heapi[0][0] = hpc-1;
    heapi[n-1][n-1] = 0;
    heap[0].r = n-1; heap[0].c = n-1;
    heap[hpc-1].r = 0; heap[hpc-1].c = 0;
    int md, r, c, nr, nc;
    while(1) {
        if (hpc==0) break;
        p = heap[0];
        r = p.r; c = p.c;
        md = dis[r][c];
        if (md==INF) break;
        hpc--; heap[0] = heap[hpc];
        heapi[heap[0].r][heap[0].c] = 0;
        heapify(0);
        flag[r][c] = 1;
        if (r==0 && c==0) break;
        for (i=0; i<4; i++) {
            nr = r+step[i][0];
            nc = c+step[i][1];
            if (nr<0||nr>=n||nc<0||nc>=n) continue;
            if (flag[nr][nc]) continue;
            if (map[nr][nc]<l) continue;
            if (map[nr][nc]<=md) {
                dis[nr][nc]=md;
                adjust(heapi[nr][nc]);
            } else {
                if (dis[nr][nc]>map[nr][nc]) {
                    dis[nr][nc] = map[nr][nc];
                    adjust(heapi[nr][nc]);
                }
            }
        }
    }
    if (dis[0][0]==INF) return -1;
    return dis[0][0];
}
int main() {
    int n, i, j, ml;
    scanf("%d", &n);
    for (i=0; i<n; i++) for (j=0; j<n; j++) scanf("%d", &map[i][j]);
    ml = map[0][0]; if (ml>map[n-1][n-1])ml=map[n-1][n-1];
    int md=256, d;
    for (i=ml; i>=0; i--) {
        j = check(i, n);
        if (j<0) continue;
        d = j-i;
        if (md>d) md = d;
    }
    printf("%d\n", md);
    return 0;
}
