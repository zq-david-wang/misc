#include<stdio.h>
#include<stdlib.h>

int ss[5000];
int dp[5000];
int vs[5000];
char flag[5000];
int stack[5000];
typedef struct _T {
    struct _T* n;
    int b;
}ENode;
ENode pool[50000];
int pc=0;
ENode *cs[5000];
void assert(int *p) {
    *p = 0;
}
int mycmp(const void *a, const void *b) {
    return *((const int *)a) - *((const int*)b);
}
int findi(int v, int n) {
    int l=0, h=n-1, m;
    while(l<=h) {
        m = (l+h)/2;
        if (vs[m]==v) return m;
        if (vs[m]>v) h=m-1;
        else l=m+1;
    }
    return -1;
}
int count(int s) {
    ENode *p = cs[s];
    int c = 0;
    while(p!=NULL) {
        c += count(p->b);
        p = p->n;
    }
    if (c==0) c=1;
    return c;
}
int main() {
    int n, i, j, k, m = 1;
    ENode *p;
    int stop;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &ss[i]);
        vs[i]=ss[i];
    }
    qsort(vs, n, sizeof(vs[0]), mycmp);
    for (i=0; i<n; i++) ss[i] = findi(ss[i], n);
    dp[n-1] = 1;
    for (i=n-2; i>=0; i--) {
        k = 0;
        for (j=i+1; j<n; j++) {
            if (ss[j]>=ss[i]) continue;
            if (k<dp[j]) k = dp[j];
        }
        dp[i] = k+1;
        if (m<dp[i]) m=dp[i];
    }
    for (i=0; i<n; i++) { 
        flag[i] = 0;
        cs[i] = NULL;
    }
    for (i=0; i<n; i++) {
        stop=0;
        for (j=i+1; j<n; j++) {
            if (ss[j]>=ss[i]) continue;
            if (dp[j] != dp[i]-1) continue;
            if (flag[ss[j]]) continue;
            flag[ss[j]] = 1;
            stack[stop++] = ss[j];
            p = &pool[pc++]; p->b = j; p->n = cs[i]; cs[i]=p;
            if (pc>=sizeof(pool)/sizeof(pool[0])) assert(NULL);
        }
        for (stop--; stop>=0; stop--) {
            flag[stack[stop]]=0;
        }
    }
    int r=0;
    for (i=0; i<n; i++) {
        if (dp[i]!=m) continue;
        if (flag[ss[i]]) continue;
        flag[ss[i]]=1;
        r += count(i);
    }
    printf("%d %d\n", m, r);
    return 0;
}
