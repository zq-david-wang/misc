#include<stdio.h>

int main() {
    int n, m, c, c1, c2, cc;
    while(1) {
        scanf("%d %d %d", &n, &m, &c); if (n==0) break;
        if (c==1) {
            c1 = (m-7+1)/2; c2 = (m-7)/2;
        } else {
            c2 = (m-7+1)/2; c1 = (m-7)/2;
        }
        cc = (n-7+1)/2*c1+(n-7)/2*c2;
        printf("%d\n", cc);
    }
    return 0;
}
