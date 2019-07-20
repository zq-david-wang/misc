#include<stdio.h>

typedef struct _T{
    struct _T* cs[26];
    short li, c;
}WNode;

WNode gpool[1000000];
int gpc;
WNode* alloc() {
    WNode *r = &gpool[gpc++];
    int i; for (i=0; i<26; i++) r->cs[i] = NULL;
    r->li = -1;
    r->c = 0;
    if (gpc>=sizeof(gpool)/sizeof(gpool[0]))printf("!!!!\n");
    return r;
}
WNode *root;
void init() {
    gpc = 0;
    root = alloc();
}

void addword(const char *a, int wi) {
    printf("add word %s\n", a);
    int i, j;
    char c;
    WNode *p;
    for (i=0; ; i++) {
        if (a[i]==0) break;
        j = i; p = root;
        while(1) {
            c = a[j++];
            if (c>'z' || c<'a') break;
            c -= 'a';
            if (p->cs[c]==NULL)p->cs[c] = alloc();
            p = p->cs[c];
            if (p->li != wi) {
                p->li = wi; p->c++;
            }
        }
    }
}

int ghn, gm;
void findmax(WNode* r, int l) {
    if (r==NULL) return;
    if (r->c > ghn && gm < l) gm = l;
    int i; for (i=0; i<26; i++) findmax(r->cs[i], l+1);
}

char b[1024];
int main() {
    int i, c;
    while(1) {
        scanf("%d", &c);
        if (c==0) break;
        init();
        for (i=0; i<c; i++) {
            scanf("%s", b);
            addword(b, i);
        }
        ghn = c/2;
        gm = 0;
        findmax(root, 0);
        printf("%d\n", gm);
    }
    return 0;
}
