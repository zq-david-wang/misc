#include<stdio.h>
#include<string.h>

char map[1001];
int pms[512], pc;

void build() {
    pc = 0;
    memset(map, 0, sizeof(map));
    int i,j; for (i=2; i<sizeof(map); i++) {
        if (map[i]==1) continue;
        pms[pc++] = i; 
        for (j=i+i; j<sizeof(map); j+=i) map[j]=1;
    }
    return;
}

typedef struct { short fs[4]; char cs[4]; int c; } Number;
Number ks[100][2];
int fcs[200];
int main() {
    build();
    int m, n, k, i;
    int num, den, j, c, p;
    int fcc, ccc, pi;
    while(1) {
        scanf("%d", &m);
        if (m==0) break;
        scanf("%d %d", &n, &k);
        // printf("m %d, n %d, k %d\n", m, n, k);
        for (i=0; i<k; i++) {
            scanf("%d %d", &num, &den);
            // printf("%d: %d/%d\n", i, num, den);
            ks[i][0].c=0; ks[i][1].c=0;
            for (j=0; j<pc; j++) {
                p = pms[j]; c=0;
                if (p>num) break;
                while((num%p)==0) { c++; num/=p; }
                if (c) {
                    ks[i][0].fs[ks[i][0].c]=j;
                    ks[i][0].cs[ks[i][0].c]=c;
                    ks[i][0].c++;
                }
            }
            for (j=0; j<pc; j++) {
                p = pms[j]; c=0;
                if (p>den) break;
                while((den%p)==0) { c++; den/=p; }
                if (c) {
                    ks[i][1].fs[ks[i][1].c]=j;
                    ks[i][1].cs[ks[i][1].c]=c;
                    ks[i][1].c++;
                }
            }
        }
        for (i=0; i<pc; i++) fcs[i] = 0;
        fcc = 0;
        for (i=0; i<pc; i++) {
            p = pms[i]; c=0;
            if (p>n) break;
            while((n%p)==0) { c++; n/=p; }
            fcs[i] = c;
            if (c) fcc++;
        }
        ccc = 0;
        if (fcc==1&&fcs[0]) { ccc++; printf("%d", fcs[0]); } 
        else if (fcc==0) { ccc++; printf("0"); }
        int rr=0;
        while(1) {
            rr++;
            for (i=0; i<k; i++) {
                // if (ks[i][1].c==0&&ks[i][0].c==0) continue;
                c = ks[i][1].c;
                for (j=0; j<c; j++) {
                    pi = ks[i][1].fs[j];
                    if (fcs[pi]<ks[i][1].cs[j]) break;
                }
                if (j==c) {
                    for (j=0; j<c; j++) {
                        pi = ks[i][1].fs[j];
                        fcs[pi] -= ks[i][1].cs[j];
                        if (fcs[pi]==0) fcc--;
                    }
                    c = ks[i][0].c;
                    for (j=0; j<c; j++) {
                        pi = ks[i][0].fs[j];
                        if (fcs[pi]==0) fcc++;
                        fcs[pi] += ks[i][0].cs[j];
                    }
                    if (fcc==1 && fcs[0]) {
                        if (ccc==0) printf("%d", fcs[0]);
                        else printf(" %d", fcs[0]);
                        ccc++;
                    } else if (fcc==0) {
                        if (ccc==0) printf("0");
                        else printf(" 0");
                        ccc++;
                    }
                    break;
                }
            }
            if (ccc >= m) break;
            if (i==k) break;
        }
        printf("\n");
    }
    return 0;
}
