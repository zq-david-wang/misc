#include<stdio.h>

int sg[1001];

int main() {
    int n, t, i, j, mr, mi, r, c, ec;
    scanf("%d %d", &n, &t);
    for (i=0; i<n; i++) {
        scanf("%d", &sg[i]);
    }
    for (i=0; i<t; i++) {
        mr = 0;
        for (j=0; j<n; j++) if (sg[j]>mr) {
            mr = sg[j];
            mi = j;
        }
        printf("%d\n", mi+1);
        r = sg[mi]; sg[mi] = 0;
        c = r/(n-1); ec = r%(n-1);
        for (j=0; j<n; j++) {
            if (j==mi) continue;
            if (ec) { sg[j] += (c+1); ec--; }
            else sg[j] += c;
        }
    }
    return 0;
}
