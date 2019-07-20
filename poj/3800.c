#include<stdio.h>
#include<string.h>
#include<math.h>

double xs[16], ys[16];
#define EPS 0.00000001
char dpm[65536][17];
double dpv[65536][17];
int neic[17];
int neim[17][256*64];
int gn, gm;
char tm[65536];
double tv[65536];
double dfs(int m, int c) {
    if (m==gm) return 0;
    if (c==0) return -1;
    if (dpm[m][c]) return dpv[m][c];
    int i, n=gn, k, rc; for (i=0; i<n; i++) if ((m&(1<<i))==0) break;
    rc=1; k=i; for (k++; k<n; k++) if ((m&(1<<k))==0) rc++;
    double r=-1;
    if (rc<=c) r = 0;
    else {
        double d;    
        for (k=0; k<neic[i]; k++) {
            d = dfs(m|neim[i][k], c-1); if (d<-EPS) continue;
            if (d<tv[neim[i][k]]) d=tv[neim[i][k]];
            if (r<0 || r>d) r=d;
        }
    }
    dpm[m][c]=1;
    dpv[m][c] = r;
    // printf("dfs 0x%x, %d, %.6f\n" ,m, c, r);
    return r;
}
int main() {
    int t, ti, n, c, i, j, k, m, l;
    double cx, cy, d, v1, v2, v3, dd;
    scanf("%d", &t);
    for (ti=0; ti<t; ti++) {
        scanf("%d %d", &n, &c);
        memset(tm, 0, sizeof(tm));
        for (i=0; i<n; i++) scanf("%lf %lf", &xs[i], &ys[i]);
        for (i=0; i<n; i++) { 
            tm[1<<i]=1; tv[1<<i]=0;
            for (j=i+1; j<n; j++) {
                dd=sqrt((xs[i]-xs[j])*(xs[i]-xs[j])+(ys[i]-ys[j])*(ys[i]-ys[j]))/2;
                cx = (xs[i]+xs[j])/2; cy = (ys[i]+ys[j])/2;
                m=0; for (k=0; k<n; k++) {
                    d = sqrt((xs[k]-cx)*(xs[k]-cx)+(ys[k]-cy)*(ys[k]-cy));
                    if (d-EPS<dd) m |= (1<<k);
                }
                if (tm[m]==0) { tv[m]=dd; tm[m]=1; } else if (tv[m]>dd) tv[m]=dd;
                for (k=j+1; k<n; k++) {
                    v1 = (ys[i]-ys[j])*(xs[j]-xs[k])-(ys[j]-ys[k])*(xs[i]-xs[j]);
                    if (fabs(v1)<EPS) continue;
                    v1 = (ys[j]-ys[i])*(ys[k]-ys[j])*(ys[i]-ys[k]);
                    v2 = (ys[k]-ys[j])*(xs[j]-xs[i])*(xs[i]+xs[j]);
                    v3 = (ys[j]-ys[i])*(xs[k]-xs[j])*(xs[j]+xs[k]);
                    cx = (v1+v2-v3)/((ys[k]-ys[j])*(xs[j]-xs[i])-(ys[j]-ys[i])*(xs[k]-xs[j]))/2;
                    if (fabs(ys[j]-ys[i]) < EPS)  cy = -(xs[k]-xs[j])*(cx-(xs[k]+xs[j])/2)/(ys[k]-ys[j]) + (ys[k]+ys[j])/2;
                    else cy = -(xs[j]-xs[i])*(cx-(xs[j]+xs[i])/2)/(ys[j]-ys[i]) + (ys[j]+ys[i])/2;
                    dd = sqrt((xs[i]-cx)*(xs[i]-cx)+(ys[i]-cy)*(ys[i]-cy));
                    m = 0; for (l=0; l<n; l++) {
                        d = sqrt((xs[l]-cx)*(xs[l]-cx)+(ys[l]-cy)*(ys[l]-cy));
                        if (d-EPS<dd) m |= (1<<l);
                    }
                    if (tm[m]==0) { tv[m]=dd; tm[m]=1; } else if (tv[m]>dd) tv[m]=dd;
                }
            }
        }
        for (i=0; i<n; i++) neic[i]=0;
        j = 1<<n;
        for (m=0; m<j; m++) {
            if (tm[m]==0) continue;
            // printf("0x%x %.6f\n", m, tv[m]);
            for (i=0; i<n; i++) {
                if (m&(1<<i)) { neim[i][neic[i]++] = m; }
            }
        }
        memset(dpm, 0, sizeof(dpm));
        gn = n; gm = (1<<n)-1;
        d = dfs(0, c);
        printf("%.6f\n", d);
    }
    return 0;
}
