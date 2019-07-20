#include<stdio.h>

int days[2004];

int main() {
    int c, i, f1, f2, d;
    int s, e, v;
    scanf("%d %d %d %d", &c, &f1, &f2, &d);
    for (i=0; i<=d; i++) days[i] = 0;
    for (i=0; i<c; i++) {
        scanf("%d %d", &s, &e);
        if (s>d) continue;
        if (e>d) e = d;
        days[e]++;
        days[s-1]--;
    }
    v = 0;
    for (i=d; i>=0; i--) {
        v += days[i];
        f2 += v;
        if (f2>=f1) break;
    }
    printf("%d\n", i);
    return 0;
}
