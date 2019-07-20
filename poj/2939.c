#include<stdio.h>

typedef struct {int cs[2], si;}NNode;
NNode pool[1000000*4];
int pc;
int root;
int alloc() {
    pool[pc].cs[0]=0; pool[pc].cs[1]=0;
    pool[pc].si = -1;
    return pc++;
}
void init() {
    pc=0;
    root = alloc();
}

int addv(int v, int si) {
    int i, r=root;
    char c;
    for (i=0;i<30;i++) {
        c = v&1; v>>=1;
        if (pool[r].cs[c]==0) {
            pool[r].cs[c]=alloc();
        }
        r=pool[r].cs[c];
    }
    if (pool[r].si==-1) pool[r].si=si;
    return si-pool[r].si;
}

int main() {
    int n, a, b, m, i;
    long long v;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        scanf("%d %d\n", &a, &b);
        init();
        v=0; i=0; while(1) {
            v=v*v; v%=n;
            v=v*a+b; v%=n;
            m=addv(v, i); if (m) break;
            i++;
        } 
        n -= m; printf("%d\n", n);

    }
    return 0;
}
