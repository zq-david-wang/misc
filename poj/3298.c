/*
 * =====================================================================================
 *
 *       Filename:  3298.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019年01月20日 22时32分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include<stdio.h>
int ns[30002];
int main() {
    int n, c, i, j, m, mm, k;
    char f;
    scanf("%d", &c);
    for (i=0; i<c; i++) {
        scanf("%d", &n);
        for (j=1; j<=n; j++) scanf("%d", &ns[j]);
        ns[0] = 0; ns[n+1] = 0;
        m = 0;
        for (j=1; j<=n; j++) {
            if (ns[j]>ns[j-1]&& ns[j]>ns[j+1]) m++;
        }
        m = m*2;
        if (n>1 && ns[n]>ns[n-1])m--;
        printf("%d\n", m);
    }

    return 0;
}

