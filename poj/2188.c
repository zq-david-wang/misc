#include<stdio.h>

short wire[1001][2];
short hook[1001][2];
int main() {
    int n, i, c=0;
    int a, b, w;
    scanf("%d", &n);
    for (i=1; i<=n; i++) {
        scanf("%d %d", &a, &b);
        wire[a][0]=i; wire[b][1]=i;
        hook[i][0] = a; hook[i][1] = b;
    }
    for (a=1; a<=n; a++) {
        w = hook[a][0];
        b = wire[w][1];
        for (i=1; i<b; i++) {
            w = hook[i][1];
            if (wire[w][0]>a) c++;
        }
    }
    printf("%d\n", c);
    return 0;
}
