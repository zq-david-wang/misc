#include<stdio.h>

/*
 * 0---n => 0-99..99 + 10..00-n
 * 0..00-9..99
 * 10..00-19..99
 */
int fn[10];
int tn[10];
int dc[10];
char ds[16];
void build() {
    int i, j;
    fn[0]=0;
    dc[0]=1; for (i=1; i<10; i++) dc[i]=dc[i-1]*10;
    for (i=1; i<10; i++) {
        fn[i]=0;
        for (j=0; j<=9; j++) {
            if (j==4) fn[i]+=dc[i-1];
            else fn[i]+=fn[i-1];
        }
    }
    tn[0]=0;
    for (i=1; i<10; i++) {
        tn[i]=tn[i-1];
        for (j=1; j<=9; j++) {
            if (j==4) tn[i]+=dc[i-1];
            else tn[i]+=fn[i-1];
        }
    }
    // for (i=0; i<10; i++) printf("%d: dc: %d, fn: %d, tn: %d\n", i, dc[i], fn[i], tn[i]);
}
int main() {
    int n, c, i, on, j, k;
    build();
    while(1) {
        scanf("%d", &n); if (n==0) break; on=n;
        i=0; while(n) { ds[i]=n%10; n/=10; i++; }
        c = tn[i-1];
        for (j=i-1; j>=0; j--) {
            for (k=(j==i-1); k<ds[j]; k++) {
                if (k==4) c+=dc[j];
                else c+=fn[j];
            }
        }
        printf("%d: %d\n", on, on-c);
    }
    return 0;
}
