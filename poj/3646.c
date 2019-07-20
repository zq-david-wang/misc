/*
 * =====================================================================================
 *
 *       Filename:  3646.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  2019年01月15日 23时32分17秒
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

int dragons[20000];
int knights[20000];
int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}
int main() {
    int m, n;
    int i, c, j;
    while(1) {
        scanf("%d %d", &m, &n);
        if (m==0 && n==0) break;
        for (i=0; i<m; i++) scanf("%d", &dragons[i]);
        for (i=0; i<n; i++) scanf("%d", &knights[i]);
        if (m>n) {
            printf("Loowater is doomed!\n");
            continue;
        }
        c = 0;
        qsort(dragons, m, sizeof(int), mycmp);
        qsort(knights, n, sizeof(int), mycmp);
        for (i=0,j=0; i<m; i++) {
            while(j<n) {
                if (knights[j] >= dragons[i]) break;
                j++;
            }
            if (j>=n) break;
            c += knights[j];
            j++;
        }
        if (i<m) printf("Loowater is doomed!\n");
        else printf("%d\n", c);
    }
    return 0;
}
