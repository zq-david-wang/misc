#include<stdio.h>

int gg[30001], base[30001], gc[30001];
int temp[30001];
int compact(int g) {
    int c = 0, ggi;
    while(g!=0) {
        ggi = gg[g];
        if (ggi==0) break;
        temp[c++] = g;
        g = ggi;
    } 
    temp[c] = g;
    for (c--; c>=0; c--) {
        base[temp[c]] += base[temp[c+1]];
        gg[temp[c]] = g;
    }
    return g;
}
int main() {
    int p, i, a, b;
    int ga, gb;
    char act[8];
    scanf("%d", &p);
    for (i=0; i<=30000; i++) { gg[i] = 0; base[i] = 0; gc[i] = 1; }
    for (i=0; i<p; i++) {
        scanf("%s", act);
        if (act[0] == 'M') {
            scanf("%d %d", &a, &b);
            ga = compact(a);
            gb = compact(b);
            if (ga != gb )  {
                base[ga] = gc[gb];
                gg[ga] = gb;
                gc[gb] += gc[ga];
            }
        } else {
            scanf("%d", &a);
            ga = compact(a);
            printf("%d\n", base[a]);
        }
    }
    return 0;
}
