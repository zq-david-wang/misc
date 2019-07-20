#include<stdio.h>
#include<string.h>

char map[100][128];
short seg[128*128*2];
int count(int s, int d, int r, int c) {
    if (d==1) return seg[s];
    d /= 2;
    if (r<d&&c<d) return seg[s]+count(s*4+1, d, r, c);
    if (r<d&&c>=d) return seg[s]+count(s*4+2, d, r, c-d);
    if (r>=d&&c>=d) return seg[s]+count(s*4+3, d, r-d, c-d);
    return seg[s]+count(s*4+4, d, r-d, c);
}
void addseg(int s, int d, int sr, int sc, int dr, int dc) {
    if (sr<0) sr=0;
    if (sc<0) sc=0;
    if (dr>=d) dr=d-1;
    if (dc>=d) dc=d-1;
    if (sr>dr||sc>dc) return;
    if (sr==0&&sc==0&&dr==d-1&&dc==d-1) {
        seg[s]++;
        return;
    }
    d/=2;
    addseg(s*4+1, d, sr, sc, dr, dc);
    addseg(s*4+2, d, sr, sc-d, dr, dc-d);
    addseg(s*4+3, d, sr-d, sc-d, dr-d, dc-d);
    addseg(s*4+4, d, sr-d, sc, dr-d, dc);
}

int main() {
    int n, m, r, c, i, j, cc, t;
    while(1) {
        scanf("%d %d %d %d", &n, &m, &r, &c);
        if (n==0) break;
        for (i=0; i<n; i++) scanf("%s", map[i]);
        memset(seg, 0, sizeof(seg));
        cc = 0;
        for (i=0; i+r<=n; i++) {
            for (j=0; j+c<=m; j++) {
                t = count(0, 128, i, j)&1;
                if (((t+map[i][j])&1)==1) {
                    addseg(0, 128, i, j, i+r-1, j+c-1);
                    cc++;
                }
            }
            for (; j<m; j++) {
                t = (count(0, 128, i, j)&1) + map[i][j];
                if (t&1) { cc=-1; break; }
            }
            if (cc==-1) break;
        }
        for (; i<n; i++) {
            for (j=0; j<m; j++) {
                t = (count(0, 128, i, j)&1) + map[i][j];
                if (t&1) { cc=-1; break; }
            }
            if (cc==-1) break;
        }
        printf("%d\n", cc);
    }
    return 0;
}
