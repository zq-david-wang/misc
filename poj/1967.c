#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ps[10000], ds[10000];
int dp1[10000*2], dp2[10000*2];
char flag[10000];
int main() {
    int n, i, t, t2, d, j, ii;
    int *p1, *p2, *tp;
    while(scanf("%d", &n)==1) {
        for (i=0; i<n; i++) scanf("%d %d", &ps[i], &ds[i]);
        p1 = dp1; p2 = dp2;
        for (i=0; i<n; i++) p1[i*2]=p1[i*2+1]=0;
        for (d=1; d<n; d++) {
            for (i=0; i<n; i++) {
                ii = i-d; j=i*2;
                t=-1; if (ii>=0) {
                    t = p1[j]; if (t>=0) {
                        t += (ps[ii+1]-ps[ii]);
                        if (t>=ds[ii]) t=-1;
                    }
                    t2 = p1[(ii+1)*2+1]; if (t2>=0) {
                        t2 += (ps[i]-ps[ii]);
                        if (t2>=ds[ii]) t2=-1;
                    }
                    if (t2>=0&&(t<0||t>t2))t=t2;
                } p2[j]=t;
                ii = i+d; j=i*2+1;
                t=-1; if (ii<n) {
                    t = p1[j]; if (t>=0) {
                        t += (ps[ii]-ps[ii-1]);
                        if (t>=ds[ii]) t=-1;
                    }
                    t2 = p1[(ii-1)*2]; if (t2>=0) {
                        t2 += (ps[ii]-ps[i]);
                        if (t2>=ds[ii]) t2=-1;
                    }
                    if (t2>=0&&(t<0||t>t2))t=t2;
                } p2[j]=t;
            }
            tp=p1; p1=p2; p2=tp;
        }
        t=p1[1]; t2=p1[(n-1)*2];
        if (t2>=0&&(t<0||t>t2))t=t2;
        if (t<0) printf("No solution\n");
        else printf("%d\n", t);
    }
    return 0;
}


