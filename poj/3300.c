/*
 * =====================================================================================
 *
 *       Filename:  3300.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019年01月20日 22时16分07秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int a, b;
}Ratio;

int fronts[16], rears[128];
Ratio rs[1280];
int mycmp(const void*a, const void*b) {
    const Ratio *pa = (const Ratio*)a;
    const Ratio *pb = (const Ratio*)b;
    long v1 = pa->a; v1 *= pb->b;
    long v2 = pb->a; v2 *= pa->b;
    if (v1>v2) return 1;
    if (v1<v2) return -1;
    return 0;
}
int main() {
    int n, m, i, j, k;
    double ms, s;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        scanf("%d", &m);
        for (i=0; i<n; i++) scanf("%d", &fronts[i]);
        for (i=0; i<m; i++) scanf("%d", &rears[i]);
        k = 0;
        for (i=0; i<n; i++) for (j=0; j<m; j++) {
            rs[k].a = rears[j];
            rs[k].b = fronts[i];
            k++;
        }
        qsort(rs, k, sizeof(Ratio), mycmp);
        ms = 0;
        for (i=0; i<k-1; i++) {
            s = rs[i+1].a; s *= rs[i].b; s/=rs[i+1].b; s/=rs[i].a;
            if (s>ms)ms = s;
        }
        printf("%.2f\n", ms);
    }
}
