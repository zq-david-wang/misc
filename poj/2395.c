#include<stdio.h>
#include<stdlib.h>

typedef struct {short a, b; int d;} ENode;

ENode edges[10000];
int mycmp(const void*a, const void *b) {
    const ENode*pa=  (const ENode*)a;
    const ENode*pb=  (const ENode*)b;
    return pa->d - pb->d;
}
int ps[2001];
int temp[2001];
int gc[2001];

int findp(int s) {
    int p=ps[s], c=0;
    while(p != -1) {
        temp[c++] = s;
        s = p;
        p = ps[p];
    }
    for (c--; c>=0; c--) ps[temp[c]] = s;
    return s;
}

int main() {
    int n, m, i;
    int a, b, d, r=0;
    int ga, gb;
    scanf("%d %d", &n, &m);
    for (i=0; i<m; i++) {
        scanf("%d %d %d", &a, &b, &d);
        edges[i].a = a;
        edges[i].b = b;
        edges[i].d = d;
    }
    qsort(edges, m, sizeof(edges[0]), mycmp);
    for (i=1; i<=n; i++) {
        ps[i] = -1;
        gc[i] = 1;
    }
    for (i=0; i<m; i++) {
        a = edges[i].a;
        b = edges[i].b;
        ga = findp(a);
        gb = findp(b);
        if (ga==gb) continue;
        if (gc[ga]>gc[gb]) {
            gc[ga] += gc[gb];
            ps[gb] = ga;
        } else {
            gc[gb]+= gc[ga];
            ps[ga] = gb;
        }
        r = edges[i].d;
    }
    printf("%d\n", r);
    return 0;
}
