#include<stdio.h>
#include<string.h>
#include<math.h>

int max1[2*1000*100+2];
int min1[2*1000*100+2];
int max2[2*1000*100+2];
int min2[2*1000*100+2];
char flag[2*1000*100+2];
short xs[100], ys[100];
short xs1[100], ys1[100];
short xs2[100], ys2[100];
int xx1[2*1000*100+2];
int xx2[2*1000*100+2];
int xxc;
int main() {
    int n, x, y, i, s, nx, xi, v1, v2, k;
    int sx, sy, n1, n2;
    long long md, tv, lx, ly;
    double mdd;
    int *pmax1=max1, *pmax2=max2, *pmin1=min1, *pmin2=min2, *tp;
    int *pxx1=xx1, *pxx2=xx2;
    while(1) {
        scanf("%d", &n); if (n==0) break;
        s=0; md=0;
        for (i=0; i<n; i++) {
            scanf("%d %d", &x, &y);
            xs[i]=x; ys[i]=y;
            if (x<0) x=-x; s+=x;
        }
        sx=0; sy=0; n1=0;
        for (i=0; i<n; i++) {
            if (xs[i]>0&&ys[i]>0) { sx+=xs[i]; sy+=ys[i]; }
            else if (xs[i]<0&&ys[i]<0) { sx-=xs[i]; sy-=ys[i]; }
            else { xs1[n1]=xs[i]; ys1[n1]=ys[i]; n1++; }
        }
        memset(flag, 0, sizeof(flag[0])*(s*2+1));
        pmax1[s+sx]=sy; // pmin1[s+sx]=sy;
        xxc=0; pxx1[xxc++]=sx;
        for (i=0; i<n1; i++) {
            k=xxc; xxc=0;
            for (xi=0; xi<k; xi++) {
                x = pxx1[xi];
                nx = x+xs1[i];
                v1 = pmax1[x+s]+ys1[i]; // v2 = pmin1[x+s]+ys1[i];
                if (flag[nx+s]==0) {
                    flag[nx+s]=1;
                    pmax2[nx+s] = v1; // pmin2[nx+s] = v2;
                    pxx2[xxc++] = nx;
                } else {
                    if (pmax2[nx+s]<v1) pmax2[nx+s]=v1;
                    // if (pmin2[nx+s]>v2) pmin2[nx+s]=v2;
                }
                nx = x-xs1[i];
                v1 = pmax1[x+s]-ys1[i]; // v2 = pmin1[x+s]-ys1[i];
                if (flag[nx+s]==0) {
                    flag[nx+s]=1;
                    pmax2[nx+s] = v1; // pmin2[nx+s] = v2;
                    pxx2[xxc++] = nx;
                } else {
                    if (pmax2[nx+s]<v1) pmax2[nx+s]=v1;
                    // if (pmin2[nx+s]>v2) pmin2[nx+s]=v2;
                }
            }
            tp=pmax1; pmax1=pmax2; pmax2=tp;
            // tp=pmin1; pmin1=pmin2; pmin2=tp;
            tp=pxx1; pxx1=pxx2; pxx2=tp;
            for (xi=0; xi<xxc; xi++) flag[pxx1[xi]+s]=0;
        }
        md = 0;
        for (xi=0; xi<xxc; xi++) {
            lx = pxx1[xi]; ly = pmax1[lx+s];
            tv = lx*lx+ly*ly; if (tv>md) md=tv;
            // ly = pmin1[lx+s]; tv = lx*lx+ly*ly; if (tv>md) md=tv;
        }
        ////////////
        sx=0; sy=0; n1=0;
        for (i=0; i<n; i++) {
            if (xs[i]>0&&ys[i]<0) { sx-=xs[i]; sy-=ys[i]; }
            else if (xs[i]<0&&ys[i]>0) { sx+=xs[i]; sy+=ys[i]; }
            else { xs1[n1]=xs[i]; ys1[n1]=ys[i]; n1++; }
        }
        pmax1[s+sx]=sy; //  pmin1[s+sx]=sy;
        xxc=0; pxx1[xxc++]=sx;
        for (i=0; i<n1; i++) {
            for (xi=0; xi<xxc; xi++) flag[pxx1[xi]+s]=0;
            k = xxc; xxc=0;
            for (xi=0; xi<k; xi++) {
                x = pxx1[xi]; nx = x+xs1[i];
                v1 = pmax1[x+s]+ys1[i]; // v2 = pmin1[x+s]+ys1[i];
                if (flag[nx+s]==0) {
                    flag[nx+s]=1;
                    pmax2[nx+s] = v1; // pmin2[nx+s] = v2;
                    pxx2[xxc++] = nx;
                } else {
                    if (pmax2[nx+s]<v1) pmax2[nx+s]=v1;
                    // if (pmin2[nx+s]>v2) pmin2[nx+s]=v2;
                }
                nx = x-xs1[i];
                v1 = pmax1[x+s]-ys1[i]; // v2 = pmin1[x+s]-ys1[i];
                if (flag[nx+s]==0) {
                    flag[nx+s]=1;
                    pmax2[nx+s] = v1; // pmin2[nx+s] = v2;
                    pxx2[xxc++] = nx;
                } else {
                    if (pmax2[nx+s]<v1) pmax2[nx+s]=v1;
                    // if (pmin2[nx+s]>v2) pmin2[nx+s]=v2;
                }
            }
            tp=pmax1; pmax1=pmax2; pmax2=tp;
            // tp=pmin1; pmin1=pmin2; pmin2=tp;
            tp=pxx1; pxx1=pxx2; pxx2=tp;
        }
        for (xi=0; xi<xxc; xi++) {
            lx = pxx1[xi]; ly = pmax1[lx+s];
            tv = lx*lx+ly*ly; if (tv>md) md=tv;
            // ly = pmin1[lx+s]; tv = lx*lx+ly*ly; if (tv>md) md=tv;
        }
        ////////////
        mdd = sqrt(md);
        printf("Maximum distance = %.3f meters.\n", mdd);
    }
    return 0;
}
