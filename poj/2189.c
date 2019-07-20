#include<stdio.h>

int cs[1001];
int main() {
    int n, p, c, i, s;
    scanf("%d %d %d", &n, &p, &c);
    for (i=0; i<=p; i++) cs[i] = 0;
    for (i=0; i<n; i++) {
        scanf("%d", &s);
        cs[s]++;
    }
    int m = 0, j=1, cc=0;
    for (i=1; i<p; i++) {
        cc += cs[i];
        while(cc>c) {
            cc -= cs[j];
            j++;
        }
        if (m<(i-j+1)) m = i-j+1;
    }
    printf("%d\n", m);
    return 0;
}
