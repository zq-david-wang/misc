/*
 * =====================================================================================
 *
 *       Filename:  3639.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019年01月18日 22时25分12秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include<stdio.h>

double rates[365];
int main() {
    int n, i, m, iv;
    double v, g0, g1, tg0;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        for (i=0; i<n; i++) scanf("%lf", &rates[i]);
        g0 = 1000;
        v = 1000/rates[0]*0.97;
        iv = v*100; v = iv; v/=100;
        g1 = v;
        for (i=1; i<n; i++) {
            v = g1*rates[i]*0.97;
            iv = v*100; v=iv; v/=100;
            if (v<g0)v = g0;
            tg0 = v;
            v = g0/rates[i]*0.97;
            iv = v*100; v=iv; v/=100;
            if (v<g1)v = g1;
            g1 = v;
            g0 = tg0;
        }
        printf("%.2f\n", g0);
    }
    return 0;
}
