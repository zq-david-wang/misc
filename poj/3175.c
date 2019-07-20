#include<stdio.h>
#include<math.h>
#define DC 9
#define MOD 1000000000
typedef struct { unsigned int ds[8]; int c; }BNum;

int main() {
    int l, i, v, s, r, j, k;
    char c[32];
    BNum a, b;
    long long v1, vr, nv1, nv2;;
    scanf("%d %s", &l, c);
    v = 0;  s = 1;
    for (i=0; i<l; i++) {
        v = v*10 + c[i]-'0';
        s *= 10;
    }
    r = 1; for (i=0; i<DC-l; i++) r *= 10;
    for (i=0; i<100000 ; i++) {
        a.ds[0] = v + s*(i%r);
        a.ds[1] = 0;
        a.c = 1;
        if (i/r) { a.ds[1] = i/r; a.c = 2; }
        // calc a*a, assuming a.c <= 2;
        for (j=0; j<4; j++) b.ds[j] = 0;
        for (j=0; j<2; j++) {
            vr = 0;
            for (k=0; k<2; k++) {
                v1 = a.ds[j]; v1 *= a.ds[k]; v1 += vr; v1 += b.ds[j+k];
                vr = v1 / MOD;
                b.ds[j+k] = v1 % MOD;
            }
            b.ds[j+k] += vr;
        }
        // calc interger part
        sprintf(c, "%d%09d%09d%09d", b.ds[3], b.ds[2], b.ds[1], b.ds[0]);
        for (j=0; j<l+l; j++) if (c[28-j-1]!='0') break;
        nv1 = 0; for (j=0; j<28-l-l; j++) nv1 = 10*nv1+c[j]-'0';
        if (j==l+l) {
            printf("%lld\n", nv1);
            break;
        }
        a.ds[0]++; if (a.ds[0]==MOD) { a.ds[0] = 0; a.ds[1]++; }
        // calc a*a, assuming a.c <= 2;
        for (j=0; j<4; j++) b.ds[j] = 0;
        for (j=0; j<2; j++) {
            vr = 0;
            for (k=0; k<2; k++) {
                v1 = a.ds[j]; v1 *= a.ds[k]; v1 += vr; v1 += b.ds[j+k];
                vr = v1 / MOD;
                b.ds[j+k] = v1 % MOD;
            }
            b.ds[j+k] += vr;
        }
        // calc interger part
        sprintf(c, "%d%09d%09d%09d", b.ds[3], b.ds[2], b.ds[1], b.ds[0]);
        nv2 = 0; for (j=0; j<28-l-l; j++) nv2 = 10*nv2+c[j]-'0';
        // printf("%s:%lld\n\n", c, nv2);
        for (j=0; j<l+l; j++) if (c[28-j-1]!='0') break;
        if (j==l+l&&nv1+1==nv2) continue;
        if (nv1<nv2) { 
            nv1++;
            printf("%lld\n", nv1); break;
        }
    }
    return 0;
}
