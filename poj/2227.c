#include<stdio.h>
#include<stdlib.h>

int hs[300][300];
char eflag[300][300];
int queue[300*300];

typedef struct _T {
    struct _T *p, *n;
    short r, c;
}HNode;
HNode gpool[300*300*2];
int gpc;
HNode *alloc(int r, int c) {
    HNode *p = &gpool[gpc++];
    p->r = r;
    p->c = c;
    p->p = NULL;
    p->n = NULL;
    return p;
}
HNode *loc[300][300];
HNode *heads[300*300];
HNode *tails[300*300];
int hvs[300*300];
int hvc;

char step[4][2] = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1},
};
int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}
int findhi(int h) {
    int s=0, e=hvc-1, m;
    while(s<=e) {
        m = (s+e)/2;
        if (hvs[m]==h) return m;
        if (hvs[m]>h) e = m-1;
        else s = m+1;
    }
    return -1;
}
int main() {
    int w, h, i, j, v, hi;
    int mh, ch, touch, ni, nj, d;
    long long rc = 0;
    HNode *p;
    gpc = 0;
    scanf("%d %d", &w, &h);
    for (i=0; i<h; i++) for (j=0; j<w; j++) {
        scanf("%d", &hs[i][j]);
        eflag[i][j] = 0;
    }
    int head=0, tail=0;
    for (i=0; i<h; i++) {
        eflag[i][0] = 1;
        queue[head++] = i<<16;
        eflag[i][w-1] = 1;
        queue[head++] = (i<<16) | (w-1);
    }
    for (i=1; i<w-1; i++) {
        eflag[0][i] = 1;
        queue[head++] = i;
        eflag[h-1][i] = 1;
        queue[head++] = ((h-1)<<16) | i;
    }
    while(tail<head) {
        v = queue[tail++];
        i = v>>16; j = v&0xffff;
        for (d=0; d<4; d++) {
            ni = i+step[d][0];
            nj = j+step[d][1];
            if (ni<0||ni>=h||nj<0||nj>=w) continue;
            if (eflag[ni][nj]) continue;
            if (hs[ni][nj]>=hs[i][j]) {
                eflag[ni][nj]=1;
                queue[head++] = (ni<<16)|nj;
            }
        }
    }
    // for (i=0; i<h; i++) { for (j=0; j<w; j++) printf("%d ", eflag[i][j]);printf("\n"); }
    hvc = 0;
    for (i=1; i<h-1; i++) for (j=1; j<w-1; j++) {
        if (eflag[i][j]) continue;
        hvs[hvc++] = hs[i][j];
    }
    qsort(hvs, hvc, sizeof(hvs[0]), mycmp);
    j = 0; for (i=0; i<hvc; i++) {
        if (i>1 && hvs[i]==hvs[i-1]) continue;
        hvs[j++] = hvs[i];
    }
    hvc = j;
    for (i=0; i<hvc; i++) heads[i] = NULL;
    for (i=0; i<hvc; i++) {
        heads[i] = alloc(0, 0);
        tails[i] = alloc(0, 0);
        heads[i]->n = tails[i];
        tails[i]->p = heads[i];
    }
    for (i=1; i<h-1; i++) for (j=1; j<w-1; j++) {
        if (eflag[i][j]) continue;
        hi = findhi(hs[i][j]);
        p = alloc(i, j);
        loc[i][j] = p;
        p->n = heads[hi]->n;
        p->p = heads[hi];
        p->n->p = p;
        p->p->n = p;
    }
    int ii=0; while(ii<hvc) {
        if (heads[ii]==NULL || heads[ii]->n==tails[ii]) {ii++; continue;}
        p = heads[ii]->n;
        i = p->r; j = p->c; ch = hs[i][j]; mh=-1; touch=0;
        // printf("start with %d,%d %d\n", i, j ,ch);
        // bfs area, recording lowest bar around them and whether the bar is leaky
        head=tail=0;
        queue[head++] = (i<<16)|j;
        eflag[i][j] = 2;
        while(tail<head) {
            v = queue[tail++];
            i = v>>16; j = v&0xffff;
            for (d=0; d<4; d++) {
                ni = i+step[d][0];
                nj = j+step[d][1];
                if (ni<0||ni>=h||nj<0||nj>=w) continue;
                if (eflag[ni][nj]==1 && hs[ni][nj]<=ch) {
                    mh = ch;
                    touch = 1;
                }
                if (hs[ni][nj]>ch) {
                    if (mh<0 || mh>hs[ni][nj]) {
                        mh = hs[ni][nj];
                        touch = 0;
                    }
                    if (hs[ni][nj]==mh && eflag[ni][nj]==1) touch=1;
                    continue;
                }
                if (eflag[ni][nj]>0) continue;
                eflag[ni][nj] = 2;
                queue[head++] = (ni<<16) | nj;
            }
        }
        // printf("collect %d block, from %d to %d, touch %d\n", head, ch, mh, touch);
        // raise level to lowest bar
        rc += head*(mh-ch);
        // if bar is leaky, mark leaky and remove those points
        // else adjust the heap
        if (touch) {
            for (tail=0; tail<head; tail++) {
                v = queue[tail];
                i = v>>16; j = v&0xffff;
                eflag[i][j] = 1;
                hs[i][j] = mh;
                p = loc[i][j];
                p->n->p = p->p;
                p->p->n = p->n;
            }
        } else {
            hi = findhi(mh);
            for (tail=0; tail<head; tail++) {
                v = queue[tail];
                i = v>>16; j = v&0xffff;
                eflag[i][j] = 0;
                hs[i][j] = mh;
                p = loc[i][j];
                p->n->p = p->p;
                p->p->n = p->n;
                p->n = heads[hi]->n;
                p->p = heads[hi];
                p->p->n = p;
                p->n->p = p;
            }
        }
    }
    printf("%lld\n", rc);
    return 0;
}
