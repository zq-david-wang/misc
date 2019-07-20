#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int ref[26];
int dm[26];
char map[10][32];
int pm[10];
int main() {
    int n, p, s, j, i;
    int cc, c, mc, v;
    while(1) {
        scanf("%d", &n); if (n==0) break;
        scanf("%d %d", &p, &s);
        for (i=0; i<p; i++) for (j=0; j<n; j++) map[i][j]=0;
        for (i=0; i<n; i++) { scanf("%d", &dm[i]); ref[i]=0; }
        for (i=0; i<p; i++) { scanf("%d %s", &pm[i], map[i]); }
        cc=0; mc=0;
        for (i=0; i<s; i++) {
            scanf("%d", &v);
            if (v>0) {
                v--;
                cc+=pm[v];
                j=0; while(1) {
                    c = map[v][j]; if (c==0) break; c -= 'A';
                    if (ref[c]==0) cc+=dm[c];
                    ref[c]++;
                    j++;
                }
            } else if (v<0) {
                v=-v; v--;
                cc -= pm[v];
                j=0; while(1) {
                    c = map[v][j]; if (c==0) break; c-='A';
                    ref[c]--;
                    if (ref[c]==0) cc-=dm[c];
                    j++;
                }
            }
            if (mc<cc) mc=cc;
        }
        printf("%d\n", mc);

    }
    return 0;
}


