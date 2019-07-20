#include<stdio.h>
#include<string.h>

typedef struct {
    int b, n;
}ENode;
#define MAXN 5004
char map[MAXN][MAXN];
#define MAX 40960
ENode pool[MAX];
int pc;
int nei[MAXN];

int indexes[MAXN];
int low[MAXN];
int stop, gind;
int stack[MAXN];
char istack[MAXN];
char ss[MAXN];
void sc(int s) {
    indexes[s]=gind; low[s]=gind++;
    stack[stop++]=s; istack[s]=1;
    int j = nei[s], b, i, ei;
    while(j!=-1) { 
        b = pool[j].b;
        if (indexes[b]==-1) {
            sc(b);
            if (low[s]>low[b]) low[s]=low[b];
        } else if (istack[b]) {
            if (low[s]>low[b]) low[s]=low[b];
        }
        if (ss[b]!=0) ss[s]=ss[b];
        if (ss[s]==1) ss[s]=2;
        j = pool[j].n;
    }
    if (low[s]==indexes[s]) {
        ei = stop-1;
        while(1) {
            j = stack[--stop];
            istack[j] = 0;
            if (j==s) break;
        }
        for (i=stop; i<=ei; i++) {
            if (ss[stack[i]]!=0) break;
        }
        if (i>ei) {
            for (i=stop; i<=ei; i++) {
                ss[stack[i]] = 1;
            }
        } else {
            for (i=stop; i<=ei; i++) {
                ss[stack[i]] = 2;
            }
        }
    }
}

int main() {
    int n, e, i, a, b, j;
    int head, tail;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        pc=0; for (i=0; i<n; i++) { 
            nei[i]=-1; indexes[i]=-1; ss[i] = 0; istack[i]=0;
        }
        stop=0; gind=0;
        scanf("%d", &e);
        for (i=0; i<e; i++) {
            scanf("%d %d", &a, &b); a--; b--;
            pool[pc].b=b; pool[pc].n=nei[a]; nei[a]=pc++;
        }
        for (i=0; i<n; i++) {
            if (indexes[i]!=-1) continue;
            sc(i);
        }
        i=0;
        for (a=0; a<n; a++) {
            if (ss[a]==1) {
                if (i==0) printf("%d", a+1);
                else printf(" %d", a+1);
                i++;
            }
        }
        printf("\n");
    }
    return 0;
}
