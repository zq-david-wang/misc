#include<stdio.h>
#include<string.h>

int nn[1000001];

int main() {
    int n, t, i, s, e;
    scanf("%d %d", &n, &t);
    memset(nn, 0xff, (t+1)*sizeof(nn[0]));
    for (i=0; i<n; i++) {
        scanf("%d %d", &s, &e);
        if (nn[s]<e) nn[s] = e;
    }
    for (i=2; i<=t; i++) {
        if (nn[i]<nn[i-1] && nn[i-1]>=i) nn[i] = nn[i-1];
    }
    s = 0;for (i=1; i<=t; ) {
        if (nn[i]<0) break;
        i=nn[i]+1;
        s++;
    }
    if (i<=t) printf("-1\n");
    else printf("%d\n", s);
    return 0;
}
