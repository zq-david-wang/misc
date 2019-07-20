#include<stdio.h>

typedef struct _T{
    struct _T *cs[52+4];
}TNode;
TNode gpool[100000];
int gpc;
TNode *alloc() {
    TNode *r = &gpool[gpc++];
    int i; for (i=0; i<52+4; i++) r->cs[i] = NULL;
    return r;
}
TNode *root;
char codes[128];
void init() {
    gpc = 0;
    root = alloc();
    int i;
    for (i=0; i<128; i++) codes[i] = -1;
    for (i=0; i<26; i++) {
        codes[i+'a'] = i;
        codes[i+'A'] = i+26;
    }
    codes['.'] = 52;
    codes[','] = 53;
    codes['?'] = 54;
    codes[' '] = 55;
}
char buf[256];
void readline(char *b) {
    char c; int i=0;
    while(1) {
        c = getchar();
        if (c==EOF || c=='\n') break;
        b[i++] = c;
    }
    b[i] = 0;
}

void addphrase(const char *w) {
    TNode *p = root;
    char c;
    int i=0; while(1) {
        c = w[i++];
        if (c==0) break;
        c = codes[c];
        if (p->cs[c]==NULL) p->cs[c] = alloc();
        p = p->cs[c];
    }
    // printf("add %s: %d\n", w, i);
}
char findphrase(const char *w) {
    TNode *p = root;
    char c;
    int i=0; while(1) {
        c = w[i++];
        if (c==0) break;
        c = codes[c];
        if (p->cs[c]==NULL) return 0;
        p = p->cs[c];
    }
    return 1;
}
int main() {
    int m, n, i;
    init();
    readline(buf);
    sscanf(buf, "%d %d", &m, &n);
    for (i=0; i<m; i++) {
        readline(buf);
        addphrase(buf);
    } 
    int c=0;
    for (i=0; i<n; i++) {
        readline(buf);
        c+=findphrase(buf);
    }
    printf("%d\n", c);
    return 0;
}
