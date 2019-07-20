#include<stdio.h>


#define MOD 299993
#define BASE 20029 
int cs[100001][32];
int fs[100001];
typedef struct _T{
    struct _T *n;
    int i;
}LNode;
LNode gpool[200000];
int gpc;

LNode *alloc(int i) {
    LNode *r = &gpool[gpc++];
    r->n = NULL;
    r->i = i;
    return r;
}
LNode *hash[MOD];
void init() {
    gpc = 0;
    int i; for(i=0; i<MOD; i++) hash[i] = NULL;
}
int add(int s, int k) {
   int i, v, j;
   long long m=0;
   for (i=1; i<k; i++) {
       v = cs[s][i]-cs[s][0];
       if (v<0) v = -v;
       m = m*BASE + v;
       m %= MOD;
   }
   if (hash[m] == NULL) { hash[m] = alloc(s); return 0; }
   LNode *p = hash[m];
   while(p!=NULL) {
       j = p->i;
       for (i=1; i<k; i++) {
           if ((cs[s][i]-cs[s][0]) != (cs[j][i]-cs[j][0])) break;
       }
       if (i==k) return s-j;
       p = p->n;
   }
   p = alloc(s);
   p->n = hash[m];
   hash[m] = p;
   return 0;
}
int main() {
    int n, k, i, j, m=0, d;
    init();
    scanf("%d %d", &n, &k);
    for (i=1; i<=n; i++) scanf("%d", &fs[i]);
    for (i=0; i<k; i++) cs[0][i] = 0;
    add(0, k);
    for (i=1; i<=n; i++) {
        for (j=0; j<k; j++) cs[i][j] = cs[i-1][j];
        for (j=0; j<k; j++) if (fs[i]&(1<<j)) cs[i][j]++;
        d = add(i, k);
        if (m<d) m = d;
    }
    printf("%d\n", m);
    return 0;
}
