/*
 * =====================================================================================
 *
 *       Filename:  3643.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019年01月19日 21时06分43秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include<stdio.h>
#define EPS 0.0001
int ali[256][3];
int emp[256][3];
int main() {
    int m, n, i, c;
    double w0, w1, w2, w3;
    double yt;
    while(1) {
        scanf("%d", &m);
        if (m==-1) break;
        for (i=0; i<m; i++) scanf("%d %d %d", &ali[i][0], &ali[i][1], &ali[i][2]);
        scanf("%d", &n);
        for (i=0; i<n; i++) scanf("%d %d %d", &emp[i][0], &emp[i][1], &emp[i][2]);
        w0 = w1 = w2 = w3 = 0;
        while(1) {
            for (i=0; i<m; i++) {
                yt = w0*ali[i][0]+w1*ali[i][1]+w2*ali[i][2]+w3;
                if (yt<-EPS) continue;
                w0 = w0+EPS*ali[i][0]*(-1-yt);
                w1 = w1+EPS*ali[i][1]*(-1-yt);
                w2 = w2+EPS*ali[i][2]*(-1-yt);
                w3 = w3+EPS*1*(-1-yt);
            }
            for (i=0; i<n; i++) {
                yt = w0*emp[i][0]+w1*emp[i][1]+w2*emp[i][2]+w3;
                if (yt>EPS) continue;
                w0 = w0+EPS*emp[i][0]*(1-yt);
                w1 = w1+EPS*emp[i][1]*(1-yt);
                w2 = w2+EPS*emp[i][2]*(1-yt);
                w3 = w3+EPS*1*(1-yt);
            }
            c = 0;
            for (i=0; i<m; i++) {
                yt = w0*ali[i][0]+w1*ali[i][1]+w2*ali[i][2]+w3;
                if (yt>-EPS) c++;
            }
            for (i=0; i<n; i++) {
                yt = w0*emp[i][0]+w1*emp[i][1]+w2*emp[i][2]+w3;
                if (yt<=EPS) c++;
            }
            if (c==0) break;
            // printf("---%d\n", c);
        }
        w0 *= 10000;
        w1 *= 10000;
        w2 *= 10000;
        w3 *= 10000;
        /*
        for (i=0; i<m; i++) {
            yt = w0*ali[i][0]+w1*ali[i][1]+w2*ali[i][2]+w3;
            printf("ali %d is %.4f\n", i, yt);
        }
        for (i=0; i<n; i++) {
            yt = w0*emp[i][0]+w1*emp[i][1]+w2*emp[i][2]+w3;
            printf("emp %d is %.4f\n", i, yt);
        }
        */
        printf("%.6f %.6f %.6f %.6f\n", w0, w1, w2, w3);
    }
    return 0;
}
