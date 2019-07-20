#include<stdio.h>
#include<string.h>

int hs[500][500];
int gs[500][500];
int queue[500*500];
int step[4][2] = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
};
typedef struct _T {
    struct _T *cs[2];
}NNode;
NNode gpool[6000000];
int ins[250000], outs[250000];
int gpc;
NNode *alloc() {
    NNode *r = &gpool[gpc++];
    r->cs[0] = r->cs[1] = NULL;
    if (gpc>=sizeof(gpool)/sizeof(gpool[0])) printf("eror\n");
    return r;
}
void init() {
    gpc = 0;
}

NNode *gnodes[250000];
int gn;
void addedge(int h, int l) {
    // printf("add edge %d-->%d\n", h, l);
    int f = 1;
    if (gnodes[h] ==NULL) {
        f = 0;
        gnodes[h] = alloc();
    }
    NNode *p = gnodes[h];
    int i, v = l; for (i=0; i<gn; i++) {
        if (p->cs[v&1]==NULL) {
            f = 0;
            p->cs[v&1] = alloc();
        }
        p = p->cs[v&1];
        v >>= 1;
    }
    if (f==0) {
        // printf("connecting %d,%d\n", h, l);
        outs[h]++;
        ins[l]++;
    }
}
int main() {
    int w, l;
    scanf("%d %d", &w, &l);
    int i, j, g=0;
    int head, tail, v;
    int ci, cj, ni, nj, d;
    for (j=0; j<l; j++) for (i=0; i<w; i++) scanf("%d", &hs[j][i]);
    memset(gs, 0xff, sizeof(gs));
    for (i=0; i<l; i++) for (j=0; j<w; j++) {
        if (gs[i][j]>=0)continue;
        g++;
        head = tail = 0;
        queue[head++] = (i<<16) | j;
        gs[i][j] = g;
        while(tail<head) {
            v = queue[tail++];
            ci = v>>16;
            cj = v&0xffff;
            for (d=0; d<4; d++) {
                ni = ci+step[d][0];
                nj = cj+step[d][1];
                if (ni<0||ni>=l||nj<0||nj>=w) continue;
                if (gs[ni][nj]>=0) continue;
                if (hs[ni][nj] != hs[ci][cj]) continue;
                gs[ni][nj] = g;
                queue[head++] = (ni<<16)|nj;
            }
        }
    }
    if (g<=1) printf("0\n");
    else {
        init();
        gn = 0; j = 1;
        while(j<g) { j*=2; gn++; }
        for (i=1; i<=g; i++) {
            ins[i]=outs[i] = 0;
            gnodes[i] = NULL;
        }
        for (i=0; i<l; i++) for (j=0; j<w-1; j++) {
            ci = gs[i][j]; cj = gs[i][j+1];
            if (ci==cj) continue;
            if (hs[i][j]>hs[i][j+1])addedge(ci, cj);
            else addedge(cj, ci);
        }
        for (j=0; j<w; j++) for (i=0; i<l-1; i++) {
            ci = gs[i][j]; cj = gs[i+1][j];
            if (ci==cj) continue;
            if (hs[i][j]>hs[i+1][j])addedge(ci, cj);
            else addedge(cj, ci);
        }
        cj = 0; ci = 0; for (i=1; i<=g; i++) {
            if (ins[i]==0) ci++;
            if (outs[i]==0) cj++;
        }
        if (ci<cj) ci = cj;
        printf("%d\n", ci);
    }
    return 0;
}
