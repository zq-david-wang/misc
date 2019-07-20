#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 182
#define MMAX 32768
int cs[4][MMAX];
void init() {
    int s, ns, nns, nnns;
    memset(cs, 0, sizeof(cs));
    int i, j, k, m;
    for (i=1; i<MAX; i++) {
        s = i*i; if (s>=MMAX) break;
        cs[0][s]++;
        for (j=i; j<MAX; j++) {
            ns = s+j*j; if (ns>=MMAX) break;
            cs[1][ns]++;
            for (k=j; k<MAX; k++) {
                nns = ns+k*k; if (nns>=MMAX) break;
                cs[2][nns]++;
                for (m=k; m<MAX; m++) {
                    nnns= nns+m*m; if (nnns>=MMAX) break;
                    cs[3][nnns]++;
                }
            }
        }
    }
}
int main() {
    int n;
    init();
    while(1) {
        scanf("%d", &n); if (n==0) break;
        printf("%d\n", cs[0][n]+cs[1][n]+cs[2][n]+cs[3][n]);
    }
    return 0;
}


