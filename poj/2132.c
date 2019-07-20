#include<stdio.h>
#include<string.h>

typedef struct _T{
    struct _T *n;
    int b, d;
}ENode;
ENode pool[1000];
int pc=0;
ENode *nei[32];
char flag[32];
typedef struct{
    int cs[32], c;
}BNumber;
#define MOD 100000000
void multiply(BNumber *a, int b) {
    int c=0;
    long long p;
    int i; for (i=0; i<a->c; i++) {
        p = a->cs[i];
        p = p*b+c;
        c = p/MOD;
        a->cs[i] = p%MOD;
    }
    if (c) a->cs[a->c++]=c;
}

void print(BNumber *a) {
    int i; printf("%d", a->cs[a->c-1]);
    for (i=a->c-2; i>=0; i--) printf("%08d", a->cs[i]);
    printf("\n");
}
int dfs(int s, int k) {
    if (s==2) return 1;
    ENode *p = nei[s];
    while(p!=NULL) {
        if (flag[p->b]==0) {
            if ((p->d%k)==0) { 
                flag[p->b] = 1;
                if (dfs(p->b, k)==1) return 1;
            }
        }
        p = p->n;
    }
    return 0;
}
char map[2001];
int primes[400], pcount;
void build() {
    pcount = 0;
    memset(map, 0, sizeof(map));
    int i,j; for (i=2; i<sizeof(map); i++) {
        if (map[i]==1) continue;
        primes[pcount++] = i;
        for (j=i+i; j<sizeof(map); j+=i) map[j]=1;
    }
}
int main() {
    int n, i, j, d;
    build();
    ENode *p;
    scanf("%d", &n);
    for (i=1; i<=n; i++) {
        nei[i] = NULL;
        for (j=1; j<=n; j++) {
            scanf("%d", &d);
            if (d==0) continue;
            p=&pool[pc++];p->b=j;p->d=d;p->n=nei[i];nei[i]=p;
        }
    }
    int pp, k;
    BNumber lcm;
    lcm.c = 1; lcm.cs[0] =1;
    for (i=0; i<pcount; i++) {
        pp = primes[i];
        k = pp; while(k<=2000) k*=pp; k/=pp;
        while(k>1) {
            for (j=1; j<=n;j++) flag[j] = 0;
            flag[1] = 1;    
            if (dfs(1, k)) break;
            k /= pp;
        }
        multiply(&lcm, k);
    }
    print(&lcm);
    return 0;
}
