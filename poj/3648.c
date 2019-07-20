/*
 * =====================================================================================
 *
 *       Filename:  3648.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  2019年01月15日 22时01分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include<stdio.h>
#include<string.h>

char flag[64];
int ibuse[32*2][2];
int gm, gn;

int dfs(int s) {
    if (s==gm) return 1;
    int a, b, ap, bp;
    a = ibuse[s][0];
    b = ibuse[s][1];
    if (a>=gn) ap = a-gn;
    else ap = a+gn;
    if (b>=gn) bp = b-gn;
    else bp = b+gn;
    char of[4];
    of[0] = flag[a]; of[1] = flag[b];
    of[2] = flag[ap]; of[3] = flag[bp];
    // try 1, 1
    if (flag[a] == 0 && flag[b] == 0) {
        flag[a] = 1; flag[b] = 1; flag[ap] = 2; flag[bp] = 2;
        if (dfs(s+1) > 0) return 1;
    } else if (flag[a] == 0 && flag[b] == 1) {
        flag[a] = 1; flag[ap] = 2;
        if (dfs(s+1) > 0) return 1;
    } else if (flag[a] == 1 && flag[b] == 0) {
        flag[b] = 1; flag[bp] = 2;
        if (dfs(s+1)>0) return 1;
    } else if (flag[a] == 1 && flag[b] == 1) {
        if (dfs(s+1)>0) return 1;
    }
    flag[a] = of[0]; flag[b] = of[1];
    flag[ap] = of[2]; flag[bp] = of[3];
    // try 1, 2
    if (flag[a] == 0 && flag[b] == 0) {
        flag[a] = 1; flag[b] = 2; flag[ap] = 2; flag[bp] = 1;
        if (dfs(s+1) > 0) return 1;
    } else if (flag[a] == 0 && flag[b] == 2) {
        flag[a] = 1; flag[ap] = 2;
        if (dfs(s+1) > 0) return 1;
    } else if (flag[a] == 1 && flag[b] == 0) {
        flag[b] = 2; flag[bp] = 1;
        if (dfs(s+1)>0) return 1;
    } else if (flag[a] == 1 && flag[b] == 2) {
        if (dfs(s+1)>0) return 1;
    }
    flag[a] = of[0]; flag[b] = of[1];
    flag[ap] = of[2]; flag[bp] = of[3];
    // try 2, 1
    if (flag[a] == 0 && flag[b] == 0) {
        flag[a] = 2; flag[b] = 1;
        flag[ap] = 1; flag[bp] = 2;
        if (dfs(s+1) > 0) return 1;
    } else if (flag[a] == 0 && flag[b] == 1) {
        flag[a] = 2; flag[ap] = 1;
        if (dfs(s+1) > 0) return 1;
    } else if (flag[a] == 2 && flag[b] == 0) {
        flag[b] = 1; flag[bp] = 2;
        if (dfs(s+1)>0) return 1;
    } else if (flag[a] == 2 && flag[b] == 1) {
        if (dfs(s+1)>0) return 1;
    }
    flag[a] = of[0]; flag[b] = of[1];
    flag[ap] = of[2]; flag[bp] = of[3];
    return 0;
}
int main() {
    int n, m, i, j;
    int a, b;
    char b1[8], b2[8];
    while(1) {
        scanf("%d %d", &n, &m);
        if (n==0 && m==0) break;
        for (i=0; i<m; i++) {
            scanf("%s %s", b1, b2);
            a=0; j=0; while(b1[j]>='0'&&b1[j]<='9') {
                a = a*10+b1[j]-'0';
                j++;
            } if (b1[j] == 'h') a+=n;
            b=0; j=0; while(b2[j]>='0'&&b2[j]<='9') {
                b = b*10+b2[j]-'0';
                j++;
            } if (b2[j] == 'h') b+=n;
            ibuse[i][0] = a;
            ibuse[i][1] = b;
        }
        for (i=0; i<n+n; i++) flag[i] = 0;
        flag[0] = 1; flag[n] = 2;
        gm = m; gn = n;
        i = dfs(0);
        if (i==0) printf("bad luck\n");
        else {
            for (i=1; i<n; i++) {
                if (i>1) printf(" ");
                if (flag[i]==1) {
                    printf("%dw", i);
                } else {
                    printf("%dh", i);
                }
            }
            printf("\n");
        }
    }
    return 0;
}
