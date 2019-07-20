#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define P1 1299709

typedef struct _T {
    struct _T *n;
    long long s, c;
}LNode;
LNode *nodes;
int gnc;
#define BATCH (65536*4)
LNode *alloc() {
    if (nodes==NULL || gnc==BATCH) {
        nodes = (LNode*)malloc(BATCH*sizeof(LNode));
        gnc = 0;
    }
    return &nodes[gnc++];
}
LNode *bucket[P1];
void init() {
    memset(bucket, 0, sizeof(bucket));
    nodes = NULL;
}

int add(long long c, long long s, int d) {
    int i1 = c%P1;
    int r = 0;
    LNode *p = bucket[i1];
    while(p!= NULL) {
        if (p->c == c) return 0;
        p = p->n;
    }
    p = alloc();
    p->c = c;
    p->s = (s<<3)|d;
    p->n = bucket[i1];
    bucket[i1] = p;
    return 1;
}

long long get(unsigned long long c) {
    int i1 = c%P1;
    int r = 0;
    LNode *p = bucket[i1];
    while(p!= NULL) {
        if (p->c == c) return p->s;
        p = p->n;
    }
    return -1;
}

#define QS 1000000
unsigned long long queue[QS];
char b[8][16];
char stack[100];
char *dirs[] = {
    "north",
    "east",
    "south",
    "west",
};

int main() {
    int n, i, nn, in;
    char r, c, di, tb;
    long long s, ns, mob[4], imob[4], m, nns;
    init();
    scanf("%d", &n);
    in = n-2;
    for (i=0; i<n; i++) scanf("%s", b[i]);
    // collect
    nn = 0;
    mob[0]=mob[1]=mob[2]=mob[3]=0xffffffffffffffffL;
    imob[0]=imob[1]=imob[2]=imob[3]=0;
    s = 0; nn = in*in; i = nn-1;
    for (r=1; r<n-1; r++) {
        for (c=1; c<n-1; c++) {
            m = 1; m <<= i;
            if (b[r][c]=='.') s |= m;
            if (b[r-1][c]!='.') { mob[0] &= (~m); imob[0] |= m; }
            else if (r-1==0) { mob[0] &= (~m); }
            if (b[r+1][c]!='.') { mob[2] &= (~m); imob[2] |= m; }
            else if (r+1==n-1) { mob[2] &= (~m); }
            if (b[r][c+1]!='.') { mob[1] &= (~m); imob[1] |= m; }
            else if (c+1==n-1) { mob[1] &= (~m); }
            if (b[r][c-1]!='.') { mob[3] &= (~m); imob[3] |= m; }
            else if (c-1==0) { mob[3] &= (~m); }
            i--;
        }
    }
    m=1; m = (m<<nn)-1;
    int head, tail;
    // printf("s is %llx, m is %llx\n", s, m);
    add(s, s, 4);
    head = tail = 0;
    queue[head++] = s;
    while(tail != head) {
        s = queue[tail++];
        if (tail==QS) tail = 0;
        if (s==0) break;
        ns = (((s&mob[0])<<in) | (s&imob[0]));
        if (add(ns, s, 0)) { queue[head++] = ns; if (head==QS)head=0; }
        ns = (((s&mob[1])>>1) | (s&imob[1]));
        if (add(ns, s, 1)) { queue[head++] = ns; if (head==QS)head=0; }
        ns = (((s&mob[2])>>in) | (s&imob[2]));
        if (add(ns, s, 2)) { queue[head++] = ns; if (head==QS)head=0; }
        ns = (((s&mob[3])<<1) | (s&imob[3]));
        if (add(ns, s, 3)) { queue[head++] = ns; if (head==QS)head=0; }
    }
    s=0; i=0;
    if (nn) while(1) {
        ns = get(s);
        di = ns & 7;
        if (di>3) break;
        stack[i++] = di;
        s = ns>>3;
        if (i>64) break;
        // printf("%d: %d %lld\n", i, di, s);
    }
    for (i--; i>=0; i--) {
        printf("%s\n", dirs[stack[i]]);
    }
    return 0;
}
