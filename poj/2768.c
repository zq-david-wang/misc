#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char trap[50002], neic[50002];
int neis[50002][3];
int tc[50002];
int build(int r, int p) {
    int i; for (i=0; i<neic[r]; i++) if (neis[r][i]==p) break;
    if (i<neic[r]) {
        // keep order
        int temp[4];
        int j, k=0; for (j=i+1; j<neic[r]; j++) temp[k++]=neis[r][j];
        for (j=0; j<i; j++) temp[k++] = neis[r][j];
        for (j=0; j<k; j++) neis[r][j]=temp[j];
        neic[r]=k;
    }
    tc[r] = trap[r];
    for (i=0; i<neic[r]; i++) {
        tc[r] += build(neis[r][i], r);
    }
    return tc[r];
}
int count(int r, int c) {
    // printf("count %d, tr %d\n", r, tc[r]);
    int rr;
    if (tc[r]==0) rr = (c+1)&1;
    else if (trap[r]) rr= 0;
    else {
        int c1, c2;
        if (neic[r]==1) {
            c1 = neis[r][0];
            rr = count(c1, c);
        } else {
            c1 = neis[r][0];
            c2 = neis[r][1];
            if (tc[c1]&&tc[c2]) rr = count(c1, 0)+count(c2, 0);
            else if (tc[c1]) { 
                if (tc[c1]==1) rr = (c+1)&1;
                else rr = count(c1, 1)+((c+1)&1);
            } else {
                if (tc[c2]==1) rr = (c+1)&1;
                rr = count(c2, 1)+((c+1)&1);
            }
        }
    }
    // printf("count %d,%d -->  %d\n", r, c, rr);
    return rr;
}
int main() {
    int n, m, i, c, b, j;
    while(1) {
        scanf("%d %d", &n, &m); if (n==0&&m==0) break;
        for (i=1; i<=n; i++) {
            scanf("%d", &c);
            for (j=0; j<c; j++) {
                scanf("%d", &b);
                neis[i][j]=b;
            }
            neic[i]=c;
            trap[i]=0;
        }
        for (i=0; i<m; i++) {
            scanf("%d", &b); trap[b]=1;
        }
        build(1, 0);
        c = count(1, 0);
        printf("%d\n", c);
    }
    return 0;
}


