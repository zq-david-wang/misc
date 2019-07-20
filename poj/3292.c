/*
 * =====================================================================================
 *
 *       Filename:  3292.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019年01月22日 08时38分33秒
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

char map[250001];
char map2[250001];
int ps[110000];
int count[250001];

void build() {
    memset(map, 0, sizeof(map));
    memset(map2, 0, sizeof(map2));
    int i, j, c=0, d, a, b;
    long long ld;
    for (i=1; i<sizeof(map); i++) {
        if (map[i]==1)continue;
        ps[c++] = i;
        d = 4*i+1;
        for (j=i+d; j<sizeof(map); j+=d) map[j] = 1;
    }
    for (i=0; i<c; i++) {
        a = ps[i];
        for (j=0; j<c; j++) {
            b = ps[j];
            ld = 4*a;
            ld *= b; ld += a; ld+= b;
            if (ld>=sizeof(map2))break;
            map2[ld]=1;
        }
    }
    count[0]=0;
    for (i=1; i<sizeof(map2); i++) {
       count[i] = count[i-1]+map2[i]; 
    }
}

int main() {
    int n, i;
    build();
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        i = (n-1)/4;
        printf("%d %d\n", n, count[i]);
    }
    return 0;
}
