#include<stdio.h>

int cs[100];
double pr[10][10];
double b1[10], b2[10];
int main() {
    int n, i, j, m=0, k;
    double s;
    double *p1=b1, *p2=b2, *tp;
    while(scanf("%d", &cs[m])==1)m++;
    n=1; while(m!=n*n) n++;
    for (i=0; i<n; i++) {
        s=0; for (j=0; j<n; j++) s+=cs[i*n+j];
        for (j=0; j<n; j++) pr[i][j]=cs[i*n+j]/s;
    }
    for (i=0; i<n; i++) p1[i]=0; p1[0]=1;
    for (i=0; i<10; i++) {
        for (j=0; j<n; j++) { 
            if (j>0) printf(" ");
            printf("%.5f", p1[j]);
        } printf("\n");
        if (i==9) break;
        for (j=0; j<n; j++) {
            s=0; for (k=0; k<n; k++) {
                s += p1[k]*pr[k][j];
            }
            p2[j]=s;
        }
        tp=p1; p1=p2; p2=tp;
    }
    return 0;
}
