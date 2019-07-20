#include<stdio.h>

typedef struct {
    int d[8];
    int c;
}BNumber;
BNumber dp[1001];
#define MOD 1000000000
void copy(BNumber*a, BNumber *b) {
    a->c = b->c;
    int i; for (i=0; i<b->c; i++) a->d[i] = b->d[i];
}
void add(BNumber *a, BNumber *b) {
    int c=0, v;
    int i; for (i=a->c; i<b->c; i++) a->d[i] = 0;
    int l = a->c; if (l<b->c) l= b->c;
    for (i=0; i<l; i++) {
        v = a->d[i]+b->d[i]+c;
        a->d[i] = v % MOD;
        c = v/MOD;
    }
    if (c) a->d[i++] = c;
    a->c = i;
}
void print(BNumber *a) {
    int i = a->c-1;
    printf("%d", a->d[i]);
    for (i--; i>=0; i--) printf("%09d", a->d[i]);
    printf("\n");
}

int main() {
    int n, k, i, j, v;
    scanf("%d %d", &n, &k);
    dp[0].c = 1;
    dp[0].d[0] = 1;
    for (i=1; i<=n; i++) dp[i].c = 0;
    for (j=k; j>=1; j--) {
        for (i=n; i>=1; i--) {
            for (v=j; v<=i; v+=j) {
                if (dp[i-v].c == 0) continue;
                if (dp[i].c == 0) copy(&dp[i], &dp[i-v]);
                else add(&dp[i], &dp[i-v]);
            }
        }
    }
    print(&dp[n]);
    return 0;
}
