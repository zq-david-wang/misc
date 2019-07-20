#include<stdio.h>

struct { short t, c; } ts[32];
int cts[3], cp[3][16], ccs[3];
char gps[32], tgps[32];
int gpc, gscore, gn;
void dfs(int s, int c, int score) {
    int r = gn-s+c;
    if (r<gpc) return;
    if (r==gpc&&score>gscore) return;
    int i=s, j;
    if (i<gn) for (j=0; j<3; j++) {
        if (cts[j]+ts[i].t>300) continue;
        cts[j]+=ts[i].t; cp[j][ccs[j]++]=i;
        dfs(i+1, c+1, score+cts[j]);
        cts[j]-=ts[i].t; ccs[j]--;
        if (c==0) break;
    }
    // check it.
    if (c<gpc) return;
    if (c==gpc&&score>gscore) return;
    int ogpc=gpc;
    gpc=0;
    int cct[3], cci[3], mt, nt, cpid;
    for (i=0; i<3; i++) cct[i]=cci[i]=0;
    char pid;
    while(1) {
        i=-1;
        for (j=0; j<3; j++) {
            if (cci[j]>=ccs[j]) continue;
            nt = cct[j]+ts[cp[j][cci[j]]].t;
            cpid = ts[cp[j][cci[j]]].c;
            if (i<0||mt>nt||(mt==nt&&pid>cpid)) {
                mt = nt; i=j; pid=cpid;
            }
        }
        if (i<0) break;
        cct[i] = mt; cci[i]++; 
        tgps[gpc++] = pid;
    }
    if (ogpc !=gpc || gscore!=score) { for (i=0; i<gpc; i++) gps[i]=tgps[i]; }
    else {
        for (i=0; i<gpc; i++) if (tgps[i]!=gps[i]) break;
        if (i<gpc&&tgps[i]<gps[i]) for (i=0; i<gpc; i++) gps[i]=tgps[i];
    }
    gscore=score;
    return;
}
int main() {
    int n, c, i, j, t, k;
    scanf("%d", &c);
    for (i=1; i<=c; i++) {
        scanf("%d", &n);
        for (j=0; j<n; j++) { 
            scanf("%d", &t);
            for (k=j-1; k>=0; k--) {
                if (ts[k].t<=t) break;
                ts[k+1]=ts[k];
            }
            ts[k+1].t=t;
            ts[k+1].c = j+'A';
        }
        // for (j=0; j<n; j++) printf("%c:%d\n", ts[j].c, ts[j].t);
        cts[0]=cts[1]=cts[2]=0;
        ccs[0]=ccs[1]=ccs[2]=0;
        gscore=0; gpc=0; gn=n;
        dfs(0, 0, 0);
        printf("Data set %d:", i);
        for (j=0; j<gpc; j++) printf(" %c", gps[j]);
        printf(" %d %d\n", gpc, gscore);
    }
    return 0;
}
