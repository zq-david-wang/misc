#include<stdio.h>
#include<string.h>

char words[10000][24];
char cs[10000][26];
int nis[10000];
typedef struct _T {
    struct _T *cs[21];
    int i, v;
}WNode;
WNode pool[10000*26];
int pc;
WNode *root;
WNode *alloc() {
    WNode *p = &pool[pc++];
    int i; for (i=0; i<=20; i++) p->cs[i]=NULL;
    return p;
}
void init() {
    pc = 0;
    root = alloc();
}
int dfs(char *cs, int *pi) {
    WNode *p = root;
    int i, c; for (i=0; i<26; i++) {
        c = cs[i];
        if (p->cs[c]==NULL) return 0;
        p = p->cs[c];
    }
    if (p->v !=-1) { 
        *pi = p->i;
        return p->v;
    }
    int r=0, ni=-1, ti;
    for (i=0; i<26; i++) {
        cs[i]++;
        c = dfs(cs, &ti);
        if (r<c) { r=c; ni=ti; }
        cs[i]--;
    }
    r++;
    p->v = r;
    nis[p->i] = ni;
    *pi = p->i;
    return r;
}
int main() {
    init();
    int n=0; while(scanf("%s", words[n])==1) n++;
    memset(cs, 0, n*sizeof(cs[0]));
    WNode *p;
    int i, j, c; for (i=0; i<n; i++) {
        nis[i]=-1;
        j=0; while(words[i][j]!=0) {
            cs[i][words[i][j]-'a']++;
            j++;
        }
        p = root;
        for (j=0; j<26; j++) {
            c = cs[i][j];
            if (p->cs[c]==NULL) p->cs[c]=alloc();
            p = p->cs[c];
        }
        p->v = -1;
        p->i = i;
    }
    int m=0, mi=-1;
    for (i=0; i<n; i++) {
        c = dfs(cs[i], &j);
        if (m<c) { m=c; mi=i; }
    }
    while(mi!=-1) {
        printf("%s\n", words[mi]);
        mi = nis[mi];
    }
    return 0;
}
