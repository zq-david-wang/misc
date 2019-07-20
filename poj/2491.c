#include<stdio.h>

typedef struct _T {
    struct _T *cs[52];
    int i;
}WNode;

WNode gpool[333*1000];
int gpc;
WNode *root;
WNode *alloc() {
    WNode *r = &gpool[gpc++];
    int i; for (i=0; i<52; i++) r->cs[i] = 0;
    r->i = -1;
    return r;
}

void init() {
    gpc = 0;
    root = alloc();
}

int insert(const char *w, int i) {
    WNode *p = root;
    char c;
    while(1) {
        c = *w++;
        if (c==0) break;
        if (c>='a'&&c<='z') c-='a';
        else if (c>='A'&&c<='Z') c = c-'A'+26;
        else return -1;
        if (p->cs[c]==NULL) p->cs[c] = alloc();
        p = p->cs[c];
    }
    if (p->i == -1) {
        p->i = i;
    }
    return p->i;
}

char *names[333];
char nb[333*1000];
int ins[333], outs[333];

int main() {
    int c, i, n, j, p, ni, i1, i2;
    char *b;
    scanf("%d", &c);
    for (i=1; i<=c; i++) {
        init();
        printf("Scenario #%d:\n", i);
        scanf("%d", &n);
        b = nb;
        ni = 0;
        for (j=0; j<n; j++) ins[j]=outs[j] = -1;
        for (j=0; j<n-1; j++) {
            scanf("%s", b);
            i1 = insert(b, ni);
            if (i1 == ni) {
                names[ni++] = b;
                while(*b!=0) b++;
                b += 4;
            }
            scanf("%s", b);
            i2 = insert(b, ni);
            if (i2 == ni) {
                names[ni++] = b;
                while(*b!=0) b++;
                b += 4;
            }
            ins[i2] = i1;
            outs[i1] = i2;
        }
        for (j=0; j<n; j++) if (ins[j]==-1) break;
        while(j>=0) {
            printf("%s\n", names[j]);
            j = outs[j];
        }
        printf("\n");
    }
    return 0;
}
