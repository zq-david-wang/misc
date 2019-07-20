#include<stdio.h>

typedef struct _T {
    struct _T *n;
    int b;
}ENode;
ENode gpool[100004];
ENode *nei[5001];
ENode *rnei[5001];
int dp[5001];
int rdp[5001];
short enda[50000];
short endb[50000];
int count(int s) {
    if (nei[s]==NULL) return 1;
    if (dp[s] != -1) return dp[s];
    int r = 0;
    ENode *p = nei[s];
    while(p!=NULL) {
        r += count(p->b);
        p = p->n;
    }
    dp[s] = r;
    return r; 
}

int rcount(int s) {
    if (rnei[s]==NULL) return 1;
    if (rdp[s] != -1) return rdp[s];
    int r = 0;
    ENode *p = rnei[s];
    while(p!=NULL) {
        r += rcount(p->b);
        p = p->n;
    }
    rdp[s] = r;
    return r; 
}

int main() {
    int n, m, i, a, b;
    int gec=0;
    ENode *p;
    scanf("%d %d", &n, &m);
    for (i=1; i<=n; i++) {
        nei[i] = NULL; rnei[i] = NULL;
        dp[i] = -1; rdp[i] = -1;
    }
    for (i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        p = &gpool[gec++]; p->b = a; p->n = nei[b]; nei[b] = p;
        p = &gpool[gec++]; p->b = b; p->n = rnei[a]; rnei[a] = p;
        enda[i] = a; endb[i] = b;
    }
    a = 0; for (i=0; i<m; i++) {
        b = count(enda[i])*rcount(endb[i]);
        if (a<b) a = b;
    }
    printf("%d\n", a);
    return 0;
}
