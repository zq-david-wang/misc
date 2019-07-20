#include<stdio.h>
#include<stdlib.h>

typedef struct {int h, w; }MNode;
MNode mem[1004];
struct {int w, i;}ws[1004];
int vs[1004];
int mycmp(const void *a, const void *b) {
    const MNode *pa = (const MNode*)a;
    const MNode *pb = (const MNode*)b;
    if (pa->h != pb->h) return pa->h-pb->h;
    return pa->w-pb->w;
}

int main() {
    int n, a, b, c;
    int i, c1, j, k, m;
    int h, w, mh, mw;
    scanf("%d %d %d %d", &n, &a, &b, &c);
    for (i=0; i<n; i++) scanf("%d %d", &mem[i].h, &mem[i].w);
    qsort(mem, n, sizeof(mem[0]), mycmp);
    // for (i=0; i<n; i++) printf("%d: %d,%d\n", i, mem[i].h, mem[i].w);
    int r = 0, wn = 0;
    for (i=0,j=0;i<n;i++) {
        if (i+r>n) break;
        mh = mem[i].h;
        while(j<n) {
            if ((mem[j].h-mh)*a > c) break;
            // insert w to ws
            for (k=wn-1; k>=0; k--) {
                if (ws[k].w<=mem[j].w) break;
                ws[k+1] =ws[k];
            }
            ws[k+1].w = mem[j].w;
            ws[k+1].i = j;
            wn++;
            j++;
        }
        // count it
        for (k=0; k<wn; k++) vs[k] = (mem[ws[k].i].h-mh)*a;
        for (k=0; k<wn; k++) {
            if (ws[k].w>mem[i].w) break;
            if ((mem[i].w-ws[k].w)*b > c) continue;
            c1 = 0;
            for (m=k; m<wn; m++) {
                if (vs[m]+(ws[m].w-ws[k].w)*b <=c) c1++;
            }
            if (r<c1) r = c1;
        }
        // remove mem[i].w
        for (k=0; k<wn; k++) if (ws[k].i == i) break;
        for (; k<wn-1; k++) ws[k] = ws[k+1]; wn--;
    }
    printf("%d\n", r);
    return 0;
}
