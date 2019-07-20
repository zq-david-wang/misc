#include<stdio.h>
typedef struct {int v, c;}CNode;
CNode cs[24];
int collect(int s, int r, int c) {
    if (r==0) return c;
    if (s<0) return 0;
    int nr, cc, ccc, nccc, total=0;
    nr = r % cs[s].v;
    cc = r / cs[s].v;
    if (cc) ccc = cs[s].c / cc;
    else ccc = c;
    if (ccc>c) ccc = c;
    nccc = collect(s-1, nr, ccc);
    cs[s].c -= cc*nccc;
    total += nccc;
    if (total == c) return total;
    cc = (r+cs[s].v-1)/cs[s].v;
    ccc = cs[s].c / cc;
    if (total+ccc >= c) {
        ccc = c-total;
    }
    cs[s].c -= ccc*cc;
    total += ccc;
    if (total == c) return total;
    nccc = collect(s-1, r-cs[s].c*cs[s].v, 1);
    if (nccc) cs[s].c = 0;
    total += nccc;
    if (total == c) return total;
    nccc = collect(s-1, r, c-total);
    return nccc+total;
}
int main() {
    int n, c, i, j;
    int rc = 0;
    CNode t;
    scanf("%d %d", &n, &c);
    for (i=0; i<n; i++) scanf("%d %d", &cs[i].v, &cs[i].c);
    for (i=1; i<n; i++) {
        t = cs[i];
        for (j=i-1; j>=0; j--) {
            if (cs[j].v<=t.v) break;
            cs[j+1] = cs[j];
        }
        cs[j+1] = t;
    }
    for (i=n-1; i>=0; i--) {
        if (cs[i].c==0) continue;
        if (cs[i].v >= c) rc += cs[i].c;
        else break;
    }
    rc += collect(i, c, 100000000);
    printf("%d\n", rc);
    return 0;
}
