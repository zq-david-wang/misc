#include<stdio.h>
#include<string.h>

typedef struct _T{
    struct _T *n;
    int s;
}ENode;
ENode pool[15536];
int pc=0;
ENode *nei[2048];

unsigned char map[2048][2048/8];

void dfs(int i, int s, int ns) {
    while((i<11) && (s&(1<<i))) i++;
    if (i==11) { 
        map[s][ns/8] |= (1<<(ns%8));
        return;
    }
    dfs(i+1, s, ns|(1<<i));
    if (i<10 && (s&(1<<(i+1)))==0) dfs(i+2, s, ns);
}
void build(int s) {
    dfs(0, s, 0);
    ENode *p;
    nei[s] = NULL;
    int i; for (i=0; i<2048; i++) {
        if (map[s][i/8] & (1<<(i%8))) {
            p = &pool[pc++];
            p->s = i; p->n = nei[s]; nei[s] = p;
        }
    }
}
int mask[12];
void init() {
    int i=1;
    mask[0] = 0;
    int j; for (j=1; j<12; j++) { mask[j] = mask[j-1]+i; i*=2; }
    memset(map, 0, sizeof(map));
    for (i=0; i<2048; i++) {
        build(i);
    }
}
long long dp[2048][12];
int cache[12][12];

long long dfs2(int s, int c, int m) {
    if (c==0) {
        if (s==0) return 1;
        return 0;
    }
    s |= m;
    if (dp[s][c] != -1) return dp[s][c];
    long long r=0;
    ENode *p = nei[s];
    while(p != NULL) {
        r += dfs2(p->s, c-1, m);
        p = p->n;
    }
    dp[s][c] = r;
    return r;
}
long long calc(int a, int b) {
    if (cache[a][b] != -1) return cache[a][b];
    int m = mask[11-a];
    memset(dp, 0xff, sizeof(dp));
    return dfs2(0, b, m);
}
int main() {
    init();
    memset(cache, 0xff, sizeof(cache));
    int a, b, t;
    long long r;
    while(1) {
        scanf("%d %d", &a, &b);
        if (a==0) break;
        if (a>b) { t=a; a=b; b=t; }
        r = calc(b, a);
        printf("%lld\n", r);
    }
    return 0;
}
