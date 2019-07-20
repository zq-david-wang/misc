#include<stdio.h>

char qs[512*512*2+8];
char map[512][512];

char buf[5120];
int readline() {
    int i=0;
    char c;
    while(1) {
        c=getchar();
        if (c==EOF||c=='\n') break;
        buf[i++]=c;
    }
    buf[i]=0;
    return i;
}
int vs[128];
int cs0[512*512*2], cs1[512*512*2];
int build(int s, int d, int ci) {
    if (cs0[s]==0) { qs[ci]='B'; return ci+1; }
    if (cs1[s]==0) { qs[ci]='W'; return ci+1; }
    qs[ci++] = 'Q';
    d /= 2;
    ci = build(s*4+1, d, ci);
    ci = build(s*4+2, d, ci);
    ci = build(s*4+3, d, ci);
    ci = build(s*4+4, d, ci);
    return ci;
}
void count(int s, int r, int c, int d) {
    if (d==1) {
        if (map[r][c]) { cs0[s]=0; cs1[s]=1; }
        else { cs0[s]=1; cs1[s]=0; }
        return;
    }
    d /= 2;
    count(s*4+1, r, c, d);
    count(s*4+2, r, c+d, d);
    count(s*4+3, r+d, c, d);
    count(s*4+4, r+d, c+d, d);
    cs0[s] = cs0[s*4+1]+cs0[s*4+2]+cs0[s*4+3]+cs0[s*4+4];
    cs1[s] = cs1[s*4+1]+cs1[s*4+2]+cs1[s*4+3]+cs1[s*4+4];
    // printf("count %d: 0s %d, 1s %d\n", s, cs0[s], cs1[s]);
}
int main() {
    int n, i, j, k, c, v;
    int c1 ,c2;
    for (i='0'; i<='9'; i++) vs[i]=i-'0';
    for (i='a'; i<='f'; i++) vs[i]=i-'a'+10;
    readline(); sscanf(buf+22, "%d", &n);
    readline(); readline();
    for (i=0; i<n; i++) {
        readline();
        for (j=0; j<n/8; j++) {
            c1 = vs[buf[5*j+2]]; c2 = vs[buf[5*j+3]];
            v = c1*16+c2;
            for (k=0; k<8; k++) map[i][j*8+k]=(v>>k)&1;
        }
    }
    // for (i=0; i<n; i++) { for (j=0;j<n; j++) printf("%d ", map[i][j]); printf("\n"); }
    count(0, 0, 0, n);
    i = build(0, n, 0);
    qs[i] = 0;
    printf("%d\n%s\n", n, qs);
    return 0;
}
