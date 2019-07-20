#include<stdio.h>

struct {short i, j;}js[10000];

char map[128][128];
int main() {
    int n, i, j;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%s", map[i]);
    int jn=0, i1, i2, j1, j2;
    for (i=0; i<n; i++) for (j=0; j<n; j++) {
        if (map[i][j] == 'J') {
            js[jn].i=i;
            js[jn].j=j;
            jn++;
        }
    }
    int s = 0;
    int di, dj, cs, fit, ni1, nj1, ni2, nj2, c;
    for (i=0; i<jn; i++) {
        i1 = js[i].i;
        j1 = js[i].j;
        // if ((n-i1-1)*(n-i1-1)+n*n < s) break;
        for (j=i+1; j<jn; j++) {
            i2 = js[j].i;
            j2 = js[j].j;
            di = i2-i1;
            dj = j2-j1;
            cs = di*di+dj*dj;
            if (cs<=s) continue;
            fit = 0;
            ni1 = i1+dj; nj1 = j1-di; ni2 = i2+dj; nj2 = j2-di;
            if (ni1>=0&&ni1<n&&nj1>=0&&nj1<n&&ni2>=0&&ni2<n&&nj2>=0&&nj2<n) {
                if (map[ni1][nj1]!='B' && map[ni2][nj2] != 'B') {
                    c = 0;
                    if (map[ni1][nj1] == '*')c++;
                    if (map[ni2][nj2] == '*')c++;
                    if (c<2) {
                        fit = 1;
                        if (s<cs) {
                            s = cs;
                            // printf("update s to %d, via %d,%d(%c) %d,%d(%c) %d,%d(%c), %d,%d(%c)\n", s, 
                            //    i1,j1,map[i1][j1], i2,j2,map[i2][j2], ni1,nj1,map[ni1][nj1], ni2,nj2,map[ni2][nj2]);
                        }
                    }
                }
            }
            if (fit) continue;
            ni1 = i1-dj; nj1 = j1+di; ni2 = i2-dj; nj2 = j2+di;
            if (ni1>=0&&ni1<n&&nj1>=0&&nj1<n&&ni2>=0&&ni2<n&&nj2>=0&&nj2<n) {
                if (map[ni1][nj1]!='B' && map[ni2][nj2] != 'B') {
                    c = 0;
                    if (map[ni1][nj1] == '*')c++;
                    if (map[ni2][nj2] == '*')c++;
                    if (c<2) {
                        if (s<cs) {
                            s = cs;
                            // printf("update s to %d, via %d,%d(%c) %d,%d(%c) %d,%d(%c), %d,%d(%c)\n", s, 
                            //     i1,j1,map[i1][j1], i2,j2,map[i2][j2], ni1,nj1,map[ni1][nj1], ni2,nj2,map[ni2][nj2]);
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", s);
    return 0;
}
