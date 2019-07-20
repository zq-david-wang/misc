#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char map[10][128];
char pos[10][16];
char line[128];
int readline(char *b) {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        b[i++] = c;
    }
    b[i]=0;
    return i;
}
char neim[6];
struct {char r, c;}neis[6];
void buildNei(int r, int c) {
    int mc; if (r<5) mc=r+5; else mc=9-(r-4);
    neim[0]=0; if (c>0) { neim[0]=1; neis[0].r=r; neis[0].c=c-1; }
    neim[1]=0; if (c<mc-1) { neim[1]=1; neis[1].r=r; neis[1].c=c+1; }
    neim[2]=neim[3]=0; if (r>0) {
        if (r<=4) {
            if (c>0) { neim[2]=1; neis[2].r=r-1; neis[2].c=c-1; }
            if (c<mc-1) { neim[3]=1; neis[3].r=r-1; neis[3].c=c; }
        } else {
            neim[2]=1; neis[2].r=r-1; neis[2].c=c;
            neim[3]=1; neis[3].r=r-1; neis[3].c=c+1;
        }
    }
    neim[4]=neim[5]=0; if (r<8) {
        if (r>=4) {
            if (c>0) { neim[4]=1; neis[4].r=r+1; neis[4].c=c-1; }
            if (c<mc-1) { neim[5]=1; neis[5].r=r+1; neis[5].c=c; }
        } else {
            neim[4]=1; neis[4].r=r+1; neis[4].c=c;
            neim[5]=1; neis[5].r=r+1; neis[5].c=c+1;
        }
    }
}
char bmap[10][16];
char wins[4][4];
char costs[128];
#define MOD 1000
#define INF 0x7fffffff
struct {char r, c;}queue[MOD];
int dis[10][16];
char inque[10][16];
int process(int r1, int c1, int r2, int c2) {
    // printf("(%d,%d) -> (%d,%d)\n", r1, c1, r2, c2);
    if (pos[r1][c1]==0||pos[r2][c2]!=0||map[r2][c2]=='U') return -1;
    memset(bmap, 0, sizeof(bmap));
    char t = pos[r1][c1]>>4;
    char op1 = pos[r1][c1]&0xf, op2;
    int r, c, mc, d, nr, nc, k, tt;
    for (r=0; r<9; r++) {
        if (r<5) mc=r+5; else mc=9-(r-4);
        for (c=0; c<mc; c++) {
            if (map[r][c]=='U') { bmap[r][c]=1; continue; }
            tt = pos[r][c];
            if (tt==0||(tt>>4)==t) continue;
            bmap[r][c]=1;
            op2 = tt&0xf;
            if (wins[op2][op1]==0) continue;
            buildNei(r, c);
            for (k=0; k<6; k++) {
                if (neim[k]==0) continue;
                bmap[neis[k].r][neis[k].c]=1;
            }
        }
    }
    // spfa
    for (r=0; r<9; r++) {
        if (r<5) mc=r+5; else mc=9-(r-4);
        for (c=0; c<mc; c++) dis[r][c]=INF;
    }
    dis[r1][c1]=0;
    int head=0, tail=0;
    queue[head].r=r1; queue[head].c=c1; head++; inque[r1][c1]=1;
    while(head != tail) {
        r = queue[tail].r;
        c = queue[tail].c;
        tail++; tail %= MOD;
        inque[r][c]=0;
        buildNei(r, c);
        for (k=0; k<6; k++) {
            if (neim[k]==0) continue;
            nr = neis[k].r;
            nc = neis[k].c;
            if (bmap[nr][nc]) continue;
            d = costs[map[nr][nc]];
            if (dis[nr][nc]>d+dis[r][c]) {
                dis[nr][nc] = d+dis[r][c];
                queue[head].r = nr;
                queue[head].c = nc;
                inque[nr][nc]=1;
                head++; head%=MOD;
            }
        }
    }
    // printf("%d,%d  -> %d\n", r2, c2, dis[r2][c2]);
    // check near last point
    buildNei(r2, c2);
    d = costs[map[r2][c2]];
    // printf("d %d(%c), dis %d\n", d, map[r2][c2], dis[r2][c2]);
    for (k=0; k<6; k++) {
        if (neim[k]==0) continue;
        nr = neis[k].r; nc = neis[k].c;
        if (bmap[nr][nc]) continue;
        if (dis[nr][nc]==INF) continue;
        if (dis[r2][c2]>d+dis[nr][nc]) {
            dis[r2][c2] = d+dis[nr][nc];
        }
    }
    if (dis[r2][c2]>10) return -1;
    return 10-dis[r2][c2];
}
int main() {
    int tc, ti, i, j, k, c1, c2, r1, r2, n;
    char ts[8], ps[8], tt, sps[8];
    for (i=0; i<128; i++) costs[i]=0;
    costs['F']=1;
    costs['W']=2;
    costs['H']=3;
    costs['M']=4;

    for (i=0; i<4; i++) for (j=0; j<4; j++) wins[i][j]=0;
    wins[1][3]=1; wins[2][1]=1; wins[3][2]=1;
    readline(line); sscanf(line, "%d", &tc); for (ti=1; ti<=tc; ti++) {
        printf("Game #%d\n", ti);
        for (i=0; i<9; i++) {
            readline(map[i]);
            j=k=0; while(map[i][j]) {
                if (map[i][j]!=' ')map[i][k++] = map[i][j];
                j++;
            } map[i][k]=0;
            // printf("%s\n", map[i]);
        }
        readline(line); sscanf(line, "%d %d", &c1, &c2);
        memset(pos, 0, sizeof(pos));
        for (i=0; i<c1; i++) {
            readline(line); sscanf(line, "%s %s", ts, ps);
            if (ts[0]=='G') tt=1;
            else if (ts[0]=='M') tt=2;
            else tt=3;
            j=ps[0]-'A'; k=ps[1]-'1'; if (j<4) k-= (4-j);
            pos[j][k] = (0<<4) | tt;
        }
        for (i=0; i<c2; i++) {
            readline(line); sscanf(line, "%s %s", ts, ps);
            if (ts[0]=='G') tt=1;
            else if (ts[0]=='M') tt=2;
            else tt=3;
            j=ps[0]-'A'; k=ps[1]-'1'; if (j<4) k-= (4-j);
            pos[j][k] = (1<<4) | tt;
        }
        readline(line); sscanf(line, "%d", &n);
        // printf("c1 is %d, c2 is %d, n is %d\n", c1, c2, n);
        for (i=1; i<=n; i++) {
            readline(line);
            sscanf(line, "%s %s", sps, ps);
            r1=sps[0]-'A'; c1=sps[1]-'1'; if (r1<4) c1-=(4-r1);
            r2=ps[0]-'A'; c2=ps[1]-'1'; if (r2<4) c2-=(4-r2);
            k = process(r1, c1, r2, c2);
            if (k<0) printf("Move #%d (%s -> %s): Unsuccessful\n", i, sps, ps);
            else { 
                j = pos[r1][c1]; pos[r1][c1]=0; pos[r2][c2]=j;
                printf("Move #%d (%s -> %s): Successful (%d points left)\n", i, sps, ps, k);
            }
        }
    }
    return 0;
}


