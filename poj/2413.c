#include<stdio.h>

typedef struct {
    int ds[15], c;
}Number;
#define MOD 100000000

void add(Number *a, Number *b) {
    int c = 0, i, v;
    while (a->c<b->c) {
        a->ds[a->c++] = 0;
    }
    for (i=0; i<a->c; i++) {
        v = a->ds[i]+b->ds[i]+c;
        c = v/MOD;
        a->ds[i] = v%MOD;
    }
    if (c) a->ds[a->c++] = c;
}

void print(Number *a) {
    int i; printf("%d", a->ds[a->c-1]);
    for (i=a->c-2; i>=0; i--) {
        printf("%08d", a->ds[i]);
    }
    printf("\n");
}

void copy(Number *a, Number *b) {
    a->c = b->c;
    int i; for (i=0; i<a->c; i++) a->ds[i] = b->ds[i];
}
void load(Number *a, char *b) {
    int l=0; while(b[l]!=0) l++;
    a->c = (l+7)/8;
    int r = 0;
    int i, j, k; for (j=0; j<l%8; j++) r = r*10+b[j]-'0';
    i = a->c-1;
    if (r) a->ds[i--] = r;
    for (;i>=0; i--) {
        r = 0;
        for (k=0; k<8; k++) r = r*10+b[j++]-'0';
        a->ds[i] = r;
    }
}
#define FC 500
Number fib[FC];

void init() {
    fib[0].c = 1; fib[0].ds[0] = 1;
    fib[1].c = 1; fib[1].ds[0] = 2;
    int i; for (i=2; i<FC; i++) {
        copy(&fib[i], &fib[i-1]);
        add(&fib[i], &fib[i-2]);
        if (fib[i].c >=14) break;
    }
}


char na[128], nb[128];
int main() {
    init();
    Number a, b;
    int c1, c2, cmp, i, j;
    while(1) {
        scanf("%s %s", na, nb);
        if (na[0]=='0' && nb[0]=='0') break;
        load(&a, na);
        load(&b, nb);
        for (i=0; i<FC; i++) {
            if (fib[i].c > a.c) break;
            if (fib[i].c < a.c) continue;
            cmp = 0;
            for (j=a.c-1; j>=0; j--) {
                if (fib[i].ds[j]>a.ds[j]) {
                    cmp = 1; break;
                } else if (fib[i].ds[j]<a.ds[j]) {
                    cmp = -1; break;
                }
            }
            if (cmp != -1) break;
        }
        c1 = i-1;
        // printf("%d:\n", i); if (i) { print(&fib[i-1]); print(&a); }
        for (; i<FC; i++) {
            if (fib[i].c > b.c) break;
            if (fib[i].c < b.c) continue;
            cmp = 0;
            for (j=b.c-1; j>=0; j--) {
                if (fib[i].ds[j]>b.ds[j]) {
                    cmp = 1; break;
                } else if (fib[i].ds[j]<b.ds[j]) {
                    cmp = -1; break;
                }
            }
            if (cmp == 1) break;
        }
        c2 = i-1;
        // printf("%d:\n", i); if (i) { print(&fib[i-1]); print(&a); }
        printf("%d\n", c2-c1);
    }
    return 0;
}
