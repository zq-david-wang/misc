#include<stdio.h>
#include<string.h>

double vs[100];
int cs[100];
int matrix[100][100];
void build(int w, int h, int d) {
    memset(matrix, 0, sizeof(matrix));
    memset(cs, 0, sizeof(cs));
    int i, j, i1, j1, k=0, k1, cd; for (i=0; i<h; i++) for(j=0; j<w; j++) {
        k1=0; for (i1=0; i1<h; i1++) for (j1=0; j1<w; j1++) {
            cd = i1-i; if (cd<0) cd=-cd; if (j1>j) cd+=(j1-j); else cd+=(j-j1);
            if (cd<=d) { matrix[k][k1]=1; cs[k]++; }
            k1++;
        } k++;
    }
}
int *pmx[100];
#define INF 0x7fffffff
int gcd(int a, int b) {
    if (a<0) a=-a;
    if (b<0) b=-b;
    int t; while(a>0) {
        t=a; a=b%a; b=t;
    }
    return b;
}
void solve(int n) {
    int i, j, k; for (i=0; i<n; i++) pmx[i]=matrix[i];
    int *tp, mv, mj, fa, fb, g, sign;
    double tv;
    for (i=0; i<n; i++) {
        mv=INF; mj=i; for (j=i; j<n; j++) {
            if (pmx[j][i]==0) continue;
            if (mv>pmx[j][i]) { mv=pmx[j][i]; mj=j; }
            if (mv<0) printf("something wrong %d:%d, %d\n", i, j, pmx[j][i]);
            if (mv==1) break;
        } j=mj; 
        if (j!=i) {
            tp = pmx[i]; pmx[i]=pmx[j]; pmx[j]=tp;
            tv = vs[i]; vs[i]=vs[j]; vs[j]=tv;
        }
        for (j=i+1; j<n; j++) {
            if (pmx[j][i]==0) continue;
            g = gcd(pmx[j][i], pmx[i][i]);
            fa = pmx[i][i]/g; fb = pmx[j][i]/g;
            for (k=i; k<n; k++) { pmx[j][k] = pmx[j][k]*fa - pmx[i][k]*fb; }
            vs[j]= vs[j]*fa - vs[i]*fb;
            sign=0; for (k=i+1; k<n; k++) if (pmx[j][k]) break;
            if (k<n && pmx[j][k]<0) sign=1;
            g=0; for (k=i+1; k<n; k++) {
                if (pmx[j][k]==0) continue;
                if (g==0) { g=pmx[j][k]; if (g<0) g=-g;}
                else g=gcd(g, pmx[j][k]);
                if (g==1) break;
            }
            if (sign) g=-g;
            if ((g!=1) && (g!=0)) {
                for(k=i+1; k<n; k++) pmx[j][k]/=g;
                vs[j] /= g;
            }
        }
    }
    //reverse it
    for (i=n-1; i>=0; i--) {
        vs[i] /= pmx[i][i];
        pmx[i][i]=1;
        for (j=i-1; j>=0; j--) {
            if (pmx[j][i]==0) continue;
            vs[j]-=pmx[j][i]*vs[i];
            pmx[j][i]=0;
        }
    }
}
int main() {
    int w, h, d, i, j, ci=0, k;
    while(1) {
        scanf("%d %d %d", &w, &h, &d); if (w==0) break; ci++;
        build(w, h, d); k=0;
        for (i=0; i<h; i++) for (j=0; j<w; j++) {
            scanf("%lf", &vs[k]); vs[k]*=cs[k]; k++;
        }
        // for (i=0; i<w*h; i++) { for (j=0; j<w*h; j++) printf("%d ", matrix[i][j]); printf("%.2f\n", vs[i]); }
        solve(w*h);
        // printf("----\n"); for (i=0; i<w*h; i++) { for (j=0; j<w*h; j++) printf("%d ", pmx[i][j]); printf("%.2f\n", vs[i]); }
        if (ci>1) printf("\n");
        k=0; for (i=0; i<h; i++) {
            for (j=0; j<w; j++) {
                if (vs[k]<=0) vs[k]=0.000001;
                printf("%8.2f", vs[k]); k++;
            }
            printf("\n");
        }
    }
    return 0;
}
