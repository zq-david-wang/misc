#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char gline[128];
char map[128][128];
int readline(char *line) {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        line[i++] =c;
    }
    line[i]=0;
    return i;
}
typedef struct { double d; int i, j;} HNode;
HNode heap[100*100];
double dis[100][100];
char flag[100][100];
int hpc;
int heapi[100][100];
#define INF 0x7fffffff
#define eps 0.000005
void heapify(int s) {
    int ni, mi=s;
    ni = s*2+1;
    if (ni>=hpc) return;
    if (heap[ni].d < heap[mi].d) mi=ni;
    ni = s*2+2;
    if (ni<hpc&&heap[ni].d<heap[mi].d)mi=ni;
    if (mi==s) return;
    HNode t;
    t=heap[mi];heap[mi]=heap[s];heap[s]=t;
    heapi[heap[mi].i][heap[mi].j]=mi;
    heapi[heap[s].i][heap[s].j]=s;
    heapify(mi);
}
void adjust(int s) {
    int p;
    HNode t;
    while(s) {
        p=(s-1)/2;
        if (heap[p].d<=heap[s].d) break;
        t=heap[p]; heap[p]=heap[s]; heap[s]=t;
        heapi[heap[p].i][heap[p].j]=p;
        heapi[heap[s].i][heap[s].j]=s;
        s=p;
    }
}
int main() {
    int tc, ti, rc, cc, i, j;
    int si, sj, ei, ej; 
    double target, l, h, m, d, dd;
    readline(gline);
    sscanf(gline, "%d", &tc); for (ti=1; ti<=tc; ti++) {
        readline(gline); sscanf(gline, "%lf %d", &target, &rc);
        for(i=0; i<rc; i++) { 
            cc = readline(map[i]);
            for (j=0; j<cc ;j++) {
                if (map[i][j]=='S') { si=i; sj=j; map[i][j]=' ';}
                if (map[i][j]=='E') { ei=i; ej=j; map[i][j]=' ';}
            }
        }
        l = 0; h=1000;
        while(l<=h) {
            m = (l+h)/2;
            // build heap
            heap[0].i=si; heap[0].j=sj; heap[0].d=0; hpc=1; heapi[si][sj]=0;
            dis[si][sj]=0;
            for (i=0; i<rc; i++) for (j=0; j<cc; j++) {
                if (i==si&&j==sj) continue;
                if (map[i][j]=='#') continue;
                heap[hpc].i=i; heap[hpc].j=j; heap[hpc].d=INF; heapi[i][j]=hpc; hpc++; 
                flag[i][j]=0;
                dis[i][j]=INF;
            }
            while(hpc) {
                i=heap[0].i; j=heap[0].j; d = heap[0].d; 
                if ((d-INF)>eps) break;
                if (i==ei&&j==ej) break;
                hpc--; heap[0]=heap[hpc]; heapi[heap[0].i][heap[0].j]=0;
                heapify(0);
                flag[i][j]=1;
                if (i>0&&flag[i-1][j]==0&&map[i-1][j]==' ') {
                    if (dis[i-1][j]>dis[i][j]+m) {
                        dis[i-1][j]=dis[i][j]+m;
                        heap[heapi[i-1][j]].d=dis[i-1][j];
                        adjust(heapi[i-1][j]);
                    }
                }
                if (i<rc-1&&flag[i+1][j]==0&&map[i+1][j]==' ') {
                    if (dis[i+1][j]>dis[i][j]+m) {
                        dis[i+1][j]=dis[i][j]+m;
                        heap[heapi[i+1][j]].d=dis[i+1][j];
                        adjust(heapi[i+1][j]);
                    }
                }
                if (j>0&&flag[i][j-1]==0&&map[i][j-1]==' ') {
                    if (dis[i][j-1]>dis[i][j]+1) {
                        dis[i][j-1]=dis[i][j]+1;
                        heap[heapi[i][j-1]].d=dis[i][j-1];
                        adjust(heapi[i][j-1]);
                    }
                }
                if (j<cc-1&&flag[i][j+1]==0&&map[i][j+1]==' ') {
                    if (dis[i][j+1]>dis[i][j]+1) {
                        dis[i][j+1]=dis[i][j]+1;
                        heap[heapi[i][j+1]].d=dis[i][j+1];
                        adjust(heapi[i][j+1]);
                    }
                }
            }
            dd = (d-target);
            if (dd>eps) h = m-eps;
            else if (dd<-eps) l=m+eps;
            else break;
        }
        printf("Case #%d: %.3f%%\n", ti, m*100);
    } 
    return 0;
}


