#include<stdio.h>
#include<stdlib.h>
#include<string.h>


double fs[100000][5];
double eval(int m, int i) {
    double r=0;
    int j; for (j=0; j<5; j++) {
        if (m&(1<<j)) r+=fs[i][j];
        else r-=fs[i][j];
    }
    return r;
}
int main() {
    int n, i, j, k;
    double min, max, mm=0, d;
    char mark[5];
    scanf("%d", &n);
    for (i=0; i<n; i++) for (j=0; j<5; j++) scanf("%lf", &fs[i][j]);
    for (i=0; i<32; i++) {
        for (k=0; k<5; k++) {
            if (i&(1<<k))mark[k]=1;
            else mark[k]=0;
        }
        d=0; for (k=0; k<5; k++) if (mark[k]) d+=fs[0][k]; else d-=fs[0][k];
        min=d;
        max=min;
        for (j=1; j<n; j++) {
            d=0; for (k=0; k<5; k++) if (mark[k]) d+=fs[j][k]; else d-=fs[j][k];
            if (d>max) max=d;
            if (d<min) min=d;
        }
        d = max-min;
        if (mm<d)mm=d;
    }
    printf("%.2f\n", mm);
    return 0;
}


