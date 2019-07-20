/*
 * =====================================================================================
 *
 *       Filename:  3644.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  2019年01月17日 12时24分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include<stdio.h>

long long s[32], t[32];
void build() {
    int i, j;
    s[1] = 0; t[1] = 1;
    for (i=2; i<32; i++) {
        s[i] = t[i-1];
        t[i] = 0; for (j=1; j<=i; j++) {
            t[i] += (s[j]*t[i-j+1]);
        }
    }
}
void process(int n, int r) {
    int c, i;
    if (n<=1) return;
    for (i=n; i>=2; i--) {
        c = s[i]*t[n-i+1];
        if (c>r) break;
        r -= c;
    }
    printf("E");
    process(i-1, r/t[n-i+1]);
    printf("S");
    process(n-i+1, r%t[n-i+1]);
}

int main() {
    int n, c;
    build();
    while(1) {
        scanf("%d %d", &n, &c);
        if (n==0) break;
        if (c>t[n]) printf("ERROR");
        else process(n, c-1);
        printf("\n");
    }
    return 0;
}
