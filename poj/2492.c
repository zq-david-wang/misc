#include<stdio.h>

typedef struct _T{
    struct _T *n;
    int id;
}NNode;

NNode gpool[1000000*2+4];
int gpc = 0;
NNode *nei[2000+4];
NNode *alloc(int id) {
    NNode *r = &gpool[gpc++];
    r->n = NULL;
    r->id = id;
    return r;
}

int queue[2000+4];
int gid[2000+4];

int main() {
    int n, i, c, m, j;
    int a, b;
    int invalid, ng;
    int head, tail;
    NNode *p;
    scanf("%d", &c);
    for (i=1; i<=c; i++) {
        scanf("%d %d", &n, &m);
        gpc = 0;
        for (j=1; j<=n; j++) {
            nei[j] = NULL;
            gid[j] = -1;
        }
        for (j=0; j<m; j++) {
            scanf("%d %d", &a, &b);
            p = alloc(b); p->n = nei[a]; nei[a] = p;
            p = alloc(a); p->n = nei[b]; nei[b] = p;
        }
        invalid = 0;
        for (j=1; j<=n; j++) {
            if (gid[j] != -1) continue;
            head = tail = 0;
            queue[head++] = j;
            gid[j] = 0;
            while(tail<head) {
                a = queue[tail++];
                ng = (gid[a]+1)&1;
                p = nei[a];
                while(p!=NULL) {
                    b = p->id;
                    if (gid[b] != -1) {
                        if (gid[b] != ng) {
                            invalid = 1;
                            break;
                        }
                    } else {
                        gid[b] = ng;
                        queue[head++] = b;
                    }
                    p = p->n;
                }
                if (invalid) break;
            }
            if (invalid) break;
        }
        printf("Scenario #%d:\n", i);
        if (invalid) printf("Suspicious bugs found!\n\n");
        else printf("No suspicious bugs found!\n\n");
    }
    return 0;
}
