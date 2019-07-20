/*
 * =====================================================================================
 *
 *       Filename:  3647.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  2019年01月17日 22时55分13秒
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
    char name[32];
    int v;
}Knight;

Knight ks[2500];
int gn;
int dp[2500][1300];
char m[2500][1300];

int mycmp(const void *a, const void *b) {
    return ((const Knight*)a)->v - ((const Knight*)b)->v;
}

int main() {
    int c, i, b, j, p, v;
    int tc = 0;
    while(1) {
        scanf("%d", &c);
        if (c==0) break;
        if (tc>0) printf("\n");
        tc++;
        for (i=0; i<c; i++) scanf("%s %d", ks[i].name, &ks[i].v);
        b = 1;
        while(1) {
            if (b*2 >= c) break;
            b = b*2;
        }
        gn = c;
        qsort(ks, c, sizeof(Knight), mycmp);
        // for (i=0; i<c; i++) printf("%s %d\n", ks[i].name, ks[i].v);
        dp[0][0] = 0;
        b = c-b;
        for (i=0; i<=c; i++) {
            dp[i][0] = 0;
            m[i][0] = 1;
        }
        m[0][0] = 0;
        
        for (i=2; i<=c; i++) {
            p = i/2;
            if (p>b) p=b;
            for (j=1; j<=p; j++) {
                v = (ks[i-1].v-ks[i-2].v)*(ks[i-1].v-ks[i-2].v)+dp[i-2][j-1];
                m[i][j] = 0;
                if (j*2 <= (i-1)) {
                    if (v>dp[i-1][j]) {
                        v = dp[i-1][j];
                        m[i][j] = 1;
                    }
                }
                dp[i][j] = v;
            }
        }
        j = b;
        for (i=c; i>=0;) {
            if (m[i][j]) {
                printf("%s\n", ks[i-1].name);
                i -= 1;
            } else {
                i -= 2; j--;
            }
        }
    }
    return 0;
}

