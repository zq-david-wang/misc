#include<stdio.h>

typedef struct _T {
    struct _T* cs[26];
    int c;
}CNode;
CNode pool[20000*26];
int pc;
CNode *root;
CNode *alloc() {
    CNode *r = &pool[pc++];
    int i; for (i=0; i<26; i++) r->cs[i]=NULL;
    r->c = 0;
    return r;
}
void init() {
    pc=0;
    root = alloc();
}
void addword(char *w) {
    char c;
    CNode *p = root;
    int i=0; while(1) {
        c = w[i]; if (c==0) break; i++;
        c -='a';
        if (p->cs[c]==NULL) p->cs[c] = alloc();
        p->c++;
        p = p->cs[c];
    }
    p->c++;
}
char words[1000][32];
int main() {
    int n=0; while(scanf("%s", words[n])==1)n++;
    init();
    int i, j; for (i=0; i<n; i++) addword(words[i]);
    CNode *p;
    char c; 
    for (i=0; i<n; i++) {
        p = root;
        j=0; while(1) {
            if (p->c==1) break;
            c = words[i][j]; if (c==0) break; j++;
            c -= 'a';
            p = p->cs[c];
        }
        printf("%s ", words[i]);
        c = words[i][j]; words[i][j]=0;
        printf("%s\n", words[i]); words[i][j]=c;
    }
    return 0;
}
