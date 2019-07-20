#include<stdio.h>
#include<string.h>

int im[8];
struct { int k, ss[10], ts[10]; }ps[12];
int cost[3][12];
int pt[12];
int mt[4];
int gmin, gn, gm;
typedef struct {
    int m, ts ,te;
}RNode;
RNode grs[12], crs[12];
char assign[3][12], ac[3];
char temp[12];
void dfs(int s) {
    int i;
    if (s==gn) {
        int ti, t, tt, j, c, cc=0, ct, k;
        for (i=0; i<gm; i++) {
            c = ac[i];
            for (j=0; j<c; j++) temp[j]=assign[i][j];
            for (j=1; j<c; j++) {
                ti = temp[j]; t = cost[i][ti];
                for (k=j-1; k>=0; k--) {
                    tt = cost[i][temp[k]];
                    if (tt<=t) break;
                    temp[k+1] = temp[k];
                }
                temp[k+1] = ti;
            }
            ct=0;
            for (j=0; j<c; j++) {
               ti = temp[j]; t = cost[i][ti]; 
               crs[ti].m = i; crs[ti].ts=ct; ct+=t; crs[ti].te=ct;
               cc += ct;
            }
        }
        if (gmin<0||gmin>cc) {
            gmin = cc;
            memcpy(grs, crs, sizeof(crs));
        }
        return;
    }
    for (i=0; i<gm; i++) {
        if (cost[i][s]!=-1) {
            assign[i][ac[i]++] = s;
            dfs(s+1);
            ac[i]--;
        }
    }
}

int main() {
    int m, n, i, k, j, ii;
    int s, t;
    int ci=0;
    double r;
    while(1) {
        scanf("%d %d", &m, &n);
        if (m==0) break;
        ci++;
        for (i=0; i<m; i++) { 
            scanf("%d", &im[i]);
            ac[i] = 0;
        }
        for (i=0; i<n; i++) {
            scanf("%d", &k);
            ps[i].k = k;
            for (ii=0; ii<m; ii++) cost[ii][i] = -1;
            for (j=0; j<k; j++) {
                scanf("%d %d", &s, &t);
                ps[i].ss[j] = s; ps[i].ts[j] = t;
                for (ii=0; ii<m; ii++) if (im[ii]>=s) cost[ii][i]=t;
            }
        }
        gmin=-1; gn=n; gm=m;
        dfs(0);
        r = gmin; r/=gn; r+=0.0001;
        printf("Case %d\n", ci);
        printf("Average solution time = %.2f\n", r);
        for (i=0; i<n; i++) {
            printf("Problem %d is solved by member %d from %d to %d\n", i+1, grs[i].m+1, grs[i].ts, grs[i].te);
        }
        printf("\n");
    }
    return 0;
}
