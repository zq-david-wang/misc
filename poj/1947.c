#include<stdio.h>
#include<string.h>

typedef struct _T{
    struct _T *n;
    int b, c;
}ENode;

ENode pool[300];
ENode *nei[151], *stack[151];
int cc[151];
int dcs[151];

int pi[151];
int cis[151];
int accs[151];
int gcisc = 0;
int cstart[151];

int dp1[151][151], dp2[151][151];
int dp3_pool[151*200];
int dp3pc = 0;
int *dp3[151];
int count(int s) {
    ENode *p = nei[s];
    int c = 1;
    dcs[s] = 0;
    while(p!=NULL) {
        c += count(p->b);
        p = p->n;
        dcs[s]++;
    }
    cc[s] = c;
    cstart[s] = gcisc;
    // printf("count %d, gc %d, dc %d\n", s, gcisc, dcs[s]);
    dp3[s] = &dp3_pool[dp3pc];
    dp3pc += (dcs[s]*151);
    p = nei[s];
    int stop = 0;
    while(p != NULL) {
        cis[gcisc++] = p->b;
        stack[stop++] = p;
        p = p->n;
    }
    int ss = 0;
    for (stop--; stop>=0; stop--) {
        p = stack[stop];
        ss += cc[p->b];
        accs[cstart[s]+stop] = ss;
    }
    return c;
}
int dfs(int s, int p, int i);
int calc1(int s, int p) {
    if (cc[s] < p) return -2;
    if (cc[s] == p) return 0;
    if (dp1[s][p] != -1) return dp1[s][p];
    // second dimention dp
    int r = dfs(s, p-1, 0);
    dp1[s][p] = r;
    return r;
}

int calc2(int s, int p) {
    if (cc[s]<=p) return -2;
    if (dp2[s][p] != -1) return dp2[s][p];
    ENode *e = nei[s];
    int mv = -2, v1;
    while(e!=NULL) {
        if (cc[e->b]>=p) {
            v1 = calc1(e->b, p);
            if (v1>=0) {
                v1++;
                if (mv<0 || mv>v1) mv = v1;
            }
            v1 = calc2(e->b, p);
            if (v1>=0) {
                if (mv<0 || mv>v1) mv = v1;
            }
        }
        e = e->n;
    }
    dp2[s][p] = mv;
    return mv;
}
int dfs(int s, int p, int i) {
    int *cache = dp3[s];
    int base  = cstart[s];
    if (p==0) return dcs[s]-i;
    if (i>=dcs[s]) return -2;
    if (accs[base+i]<p) return -2;
    if (accs[base+i]==p) return 0;
    int ii = i*151+p;
    if (cache[ii] != -1) return cache[ii];
    int r = dfs(s, p, i+1);
    if (r>=0) r++;
    int v1, v2, j;
    for (j=1; j<=p; j++) {
        v1 = calc1(cis[base+i], j);
        if (v1<0) break;
        v2 = dfs(s, p-j, i+1);
        if (v2>=0) {
            v1 += v2;
            if (r<0 || v1<r) r = v1;
        }
    }
    cache[ii] = r;
    return r;

}
int main() {
    int n, p, i;
    int a, b, pc = 0;
    ENode *e;
    scanf("%d %d", &n, &p);
    for (i=1; i<=n; i++) { 
        nei[i] = NULL;
        pi[i] = 0;
    }
    for (i=1; i<n; i++) {
        scanf("%d %d", &a, &b);
        e = &pool[pc++]; e->b = b; e->n = nei[a]; nei[a] = e;
        pi[b] = a;
    }
    // for (i=1; i<=n; i++) printf("%d: cstart: %d, dp3 0x%p, cc: %d, dc : %d\n", i, cstart[i], dp3[i], cc[i], dcs[i]);
    for (i=1; i<=n; i++) if (pi[i]==0) break;
    count(i);
    // printf("start with %d\n", i);
    memset(dp1, 0xff, sizeof(dp1));
    memset(dp2, 0xff, sizeof(dp2));
    memset(dp3_pool, 0xff, sizeof(dp3_pool));
    int v1 = calc1(i, p);
    int v2 = calc2(i, p);
    // printf("with %d ==> %d\n", i, v1);
    // printf("without %d ==> %d\n", i, v2);
    if (v2>=0) {
        if (v1<0 || v1>v2) v1 = v2;
    }
    printf("%d\n", v1);
    return 0;
}
