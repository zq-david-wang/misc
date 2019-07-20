#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char span[64][64];
span la, lb;
struct {short m1, m2;} specs[26];
short mins[26], maxs[26], cs[26], css[26];
char steps[][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
    {1, 1},
    {1, -1},
    {-1, 1},
    {-1, -1},
};
int main() {
    int tc, ti, i, x, y, s, n, ss, j, k, ni, nj, c;
    char spec[32];
    span *p1, *p2, *tp;
    scanf("%d", &tc); for (ti=1; ti<=tc; ti++) {
        printf("Simulation #%d\n", ti);
        scanf("%d %d %d", &x, &y, &s);
        for (i=0; i<y; i++) scanf("%s", la[i]);
        for (i=0; i<s; i++) {
            specs[i].m1=0; specs[i].m2=0;
            scanf("%s", spec);
            j=0; while(spec[j]!='/'&&spec[j]!=0) {
                c = spec[j]-'0';
                specs[i].m1 |= (1<<c);
                j++;
            }
            if (spec[j]=='/')j++;
            while(spec[j]) {
                c = spec[j]-'0';
                specs[i].m2 |= (1<<c);
                j++;
            }
        }
        scanf("%d", &n);
        for (i=0; i<s; i++) cs[i]=0;
        for (i=0; i<y; i++) for (j=0; j<x; j++) {
            if (la[i][j]=='.') {
                la[i][j]=100;
                continue;
            }
            la[i][j] -= 'A';
            cs[la[i][j]]++;
        }
        for (i=0; i<s; i++) mins[i]=maxs[i]=cs[i];
        p1=&la; p2=&lb;
        for (k=0; k<n; k++) {
            // for (i=0; i<y; i++) { for (j=0; j<x; j++) printf("%4d ", (*p1)[i][j]); printf("\n"); } printf("-------------\n");
            for (i=0; i<y; i++) for (j=0; j<x; j++) (*p2)[i][j]=100;
            for (i=0; i<y; i++) for (j=0; j<x; j++) {
                for (ss=0; ss<s; ss++) css[ss]=0;
                for (ss=0; ss<8; ss++) {
                    ni=i+steps[ss][0];
                    nj=j+steps[ss][1];
                    if (ni<0||ni>=y||nj<0||nj>=x) continue;
                    if ((*p1)[ni][nj]==100) continue;
                    css[(*p1)[ni][nj]]++;
                }
                for (ss=0; ss<s; ss++) {
                    if ((*p1)[i][j]==ss) {
                        if ((specs[ss].m1&(1<<css[ss]))) { (*p2)[i][j]=ss; break; }
                    // } else if ((*p1)[i][j]==100) {
                    } else {
                        if ((specs[ss].m2&(1<<css[ss]))) { (*p2)[i][j]=ss; break; }
                    }
                }
            }
            tp = p1; p1=p2; p2=tp;
            for (i=0; i<s; i++) cs[i]=0;
            for (i=0; i<y; i++) for (j=0; j<x; j++) {
                if ((*p1)[i][j]==100) { continue; }
                cs[(*p1)[i][j]]++;
            }
            for (i=0; i<s; i++) {
                if (mins[i]>cs[i]) mins[i]=cs[i];
                if (maxs[i]<cs[i]) maxs[i]=cs[i];
            }
        }
        for (i=0; i<s; i++) {
            printf("Species %c: At most %d live, at least %d live.\n", i+'A', maxs[i], mins[i]);
        }
    }
    return 0;
}


