#include<stdio.h>
#include<string.h>
typedef struct _T {
    struct _T *cs[26];
    int c;
}WNode;
WNode gpool[5000];
int gpc;
WNode *alloc() {
    WNode *r = &gpool[gpc++];
    int i; for (i=0; i<26; i++) r->cs[i] = NULL;
    r->c = 0;
    return r;
}
WNode *root;
void adddict(const char *w) {
    WNode *p = root;
    char c;
    while(1) {
        c = *w++;
        if (c==0) break;
        if (c<'A'||c>'Z') return;
        c -= 'A';
        if (p->cs[c]==NULL) p->cs[c] = alloc();
        p = p->cs[c];
    }
    p->c = 1;
}

typedef struct _TT {
    struct _TT* cs[16];
    long long c;
}CNode;
CNode gcpool[200000];
int gcpc;
CNode *alloc_cache() {
    CNode *r = &gcpool[gcpc++];
    int i; for (i=0;i<16; i++) r->cs[i] = NULL;
    r->c=0;
    if (gcpc>=sizeof(gcpool)/sizeof(gcpool[0])) printf("error\n");
    return r;
}
CNode *cache[32][32];
void init() {
    gpc = 0;
    gcpc = 0;
    root = alloc();
    memset(cache, 0, sizeof(cache));
}

long long getcache(int i, int j, WNode *p) {
    if (cache[i][j]==NULL) return -1;
    CNode *cp = cache[i][j];
    long long v = ((long long)((void*)p));
    int s, m; for (s=0; s<4; s++) {
        m = v&0xf;
        if (cp->cs[m]==NULL) return -1;
        cp = cp->cs[m];
        v >>= 4;
    }
    return cp->c;
}

void addcache(int i, int j, WNode *p, long long c) {
    if (cache[i][j]==NULL)cache[i][j] = alloc_cache();
    CNode *cp = cache[i][j];
    long long v = ((long long)((void*)p));
    int s, m; for (s=0; s<4; s++) {
        m = v&0xf;
        if (cp->cs[m]==NULL) cp->cs[m] = alloc_cache();
        cp = cp->cs[m];
        v >>= 4;
    }
    cp->c = c;
}

char map[32][32];
int readline(char *b) {
    int i=0;
    char c;
    while(1) {
        c = getchar();
        if (c==EOF || c=='\n') break;
        b[i++] = c;
    }
    b[i] = 0;
    return i;
}
char buf[128];
int gw, gh;
long long dfs(int r, int c, WNode *p) {
    if (r>=gh || c>=gw) return 0;
    if (p==NULL) return 0;
    long long cache = getcache(r, c, p);
    if (cache != -1) {
        return cache;
    }
    WNode *np;
    cache = 0;
    int i = map[r][c] - 'A', j;
    if (p->cs[i]!=NULL) {
        np = p->cs[i];
        cache = np->c;
        for (i=r+1; i<gh; i++) for (j=c; j<gw; j++)cache += dfs(i, j, np);
        for (i=c+1; i<gw; i++) cache += dfs(r, i, np);
    } else return 0;
    addcache(r, c, p, cache);
    return cache;
}
int main() {
    init();
    int h, w, i, j;
    readline(buf);
    sscanf(buf, "%d %d", &h, &w);
    for (i=h-1; i>=0; i--) readline(map[i]);
    readline(buf);
    while(readline(buf)) {
        adddict(buf);
    }
    /*
    FILE *fp = fopen("dict.in", "r");
    while(fscanf(fp, "%s", buf)==1) {
        adddict(buf);
    }
    */
    gh = h; gw = w;
    long long rc = 0;
    for (i=0; i<h; i++) for (j=0; j<w; j++) {
        rc += dfs(i, j, root);
    }
    printf("%lld\n", rc);
    return 0;
}
