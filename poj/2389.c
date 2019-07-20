#include<stdio.h>

typedef struct {
    unsigned int ds[16];
    int c;
}BNumber;
#define MOD 1000000000
BNumber ba, bb, bc;
char a[64], b[64];
void print(BNumber *n) {
    printf("%d", n->ds[n->c-1]);
    int i; for (i=n->c-2; i>=0; i--) printf("%09d", n->ds[i]);
    printf("\n");
}
int main() {
    scanf("%s %s", a, b);
    int l1 = 0; while(a[l1]!=0) l1++;
    int l2 = 0; while(b[l2]!=0) l2++;
    int i, j, k, n, v, base;
    k = 0; base=1; v=0; n=0;
    for (i=l1-1; i>=0; i--) {
        v += base*(a[i]-'0');
        base *= 10; k++;
        if (k==9) {
            ba.ds[n++] = v;
            v = 0; base=1; k=0;
        }
    }
    if (k) ba.ds[n++] = v;
    ba.c = n;
    k = 0; base=1; v=0; n=0;
    for (i=l2-1; i>=0; i--) {
        v += base*(b[i]-'0');
        base *= 10; k++;
        if (k==9) {
            bb.ds[n++] = v;
            v = 0; base=1; k=0;
        }
    }
    if (k) bb.ds[n++] = v;
    bb.c = n;
    for (i=0; i<16; i++) bc.ds[i] = 0;
    unsigned long long vr, va, vb, vp;
    for (i=0; i<bb.c; i++) {
        va = bb.ds[i];
        vr = 0;
        for (j=0; j<ba.c; j++) {
            vb = ba.ds[j];
            vp = va*vb+vr;
            vr = vp / MOD;
            vp = vp % MOD;
            bc.ds[i+j] += vp;
            vr += (bc.ds[i+j] / MOD);
            bc.ds[i+j] %= MOD;
        }
        bc.ds[i+j] += vr;
        bc.ds[i+j+1] += (bc.ds[i+j]/MOD);
        bc.ds[i+j] %= MOD;
    }
    for (i=15; i>=0; i--) if (bc.ds[i])break;
    bc.c = i+1;
    print(&bc);
    return 0;
}
