#include<stdio.h>
#include<string.h>

long long cs[33][24];
int vs[64];
int rs[64], gs[64];
long long calc(int a, int b) {
    if (cs[a][b]!=-1) return cs[a][b];
    long long r; 
    if (b==0||b==a) r = 1;
    else if (b==1) r =  a;
    else r = calc(a-1, b-1)+calc(a-1, b);
    cs[a][b] = r;
    return r;
}
int main() {
    int n, i, j, k,  q, m, c;
    char b[32];
    for (i=0; i<=32; i++) for (j=0; j<=32; j++) cs[i][j]=-1;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        for (i=0; i<n; i++) scanf("%d", &vs[i]);
        scanf("%d", &q);
        for (i=0; i<q; i++) {
            scanf("%s", b);
            c=0; j=0; while(b[j]!=0) { c=c*2+b[j]-'0'; j++; }
            m = n/2; k=0;
            for (j=0; j<n; j++) {
                if (m==0) break;
                if (c<calc(n-j-1, m-1)) { rs[k++]=vs[j]; m--; }
                else c-=calc(n-j-1, m-1);
            }
            m = n/2;
            for (; k<m; k++) rs[k] = vs[j++];
            for (k=0; k<m; k++) scanf("%d", &gs[k]);
            for (k=1; k<m; k++) {
                c = gs[k];
                for (j=k-1; j>=0; j--) {
                    if (gs[j]<=c) break;
                    gs[j+1] = gs[j];
                }
                gs[j+1] = c;
            }
            for (k=1; k<m; k++) {
                c = rs[k];
                for (j=k-1; j>=0; j--) {
                    if (rs[j]<=c) break;
                    rs[j+1] = rs[j];
                }
                rs[j+1] = c;
            }
            for (k=0; k<m; k++) if (rs[k]!=gs[k]) break;
            if (k<m) printf("FALSE\n");
            else printf("TRUE\n");
        }
    }
}
