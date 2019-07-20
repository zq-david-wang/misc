#include<stdio.h>

int ss[100];
int vs[10];
typedef struct _T {
    struct _T *p, *n;
    int v;
}LNode;

LNode root, tail;
LNode nodes[100];

int dfs(int s) {
    // printf("dfs %d\n", s);
    if (root.n == &tail) return 1;
    LNode *p = &root;
    LNode *b[10];
    int bc= 0, sum;
    p = p->n;
    vs[s] = p->v-vs[0];
    b[bc++] = p;
    p->p->n = p->n;
    p->n->p = p->p;
    p = root.n;
    int i; for (i=1; i<s; i++) {
        sum = vs[i]+vs[s];
        while(p != &tail) {
            if (p->v>=sum) break;
            p = p->n;
        }
        if (p==&tail || p->v > sum) break;
        b[bc++] = p;
        p->p->n = p->n;
        p->n->p = p->p;
        p = p->n;
    }
    if (i>=s) {
       i = dfs(s+1); 
    } else i=0;
    if (i) return 1;
    for (i=bc-1; i>=0; i--) {
        p = b[i];
        p->n->p = p;
        p->p->n = p;
    }
    return 0;
}
int main() {
    LNode *p;
    int n, i, j, t, c, d, s; while(scanf("%d", &n)==1) {
        root.p = NULL; root.n = &tail;
        tail.p = &root; tail.n = NULL;
        c = n*(n-1)/2;
        for (i=0; i<c; i++) scanf("%d", &ss[i]);
        for (i=1; i<c; i++) {
            t = ss[i];
            for (j=i-1; j>=0; j--) {
                if (ss[j]<=t) break;
                ss[j+1] = ss[j];
            }
            ss[j+1] = t;
        }
        if (n==3) {
            d = ss[0]+ss[1]-ss[2];
            if (d&1) printf("Impossible\n");
            else {
                vs[0] = d/2;
                vs[1] = ss[0]-vs[0];
                vs[2] = ss[1]-vs[0];
                printf("%d %d %d\n", vs[0],vs[1],vs[2]);
            } 
            continue;
        }
        // try ss[i] = 1+2
        p = &root;
        for (i=2; i<c; i++) {
            nodes[i].v = ss[i];  
            nodes[i].n = p->n;
            nodes[i].p = p;
            p->n->p = &nodes[i];
            p->n = &nodes[i];
            p = p->n;
        }
        for (i=2; i<=n; i++) {
            d = ss[0]+ss[1]-ss[i];
            if (d&1) continue;
            vs[0] = d/2;
            vs[1] = ss[0]-vs[0];
            vs[2] = ss[1]-vs[0];
            // printf("try %d,%d,%d\n", vs[0], vs[1], vs[2]);
            s = vs[1]+vs[2];
            p = &nodes[i];
            p->p->n = p->n;
            p->n->p = p->p;
            if (dfs(3)) break;
            p->p->n = p;
            p->n->p = p;
        }
        if (i<=n) {
            for (i=0; i<n; i++) {
                if (i>0) printf(" %d", vs[i]);
                else printf("%d", vs[i]);
            } printf("\n");
        } else printf("Impossible\n");
    }
    return 0;
}
