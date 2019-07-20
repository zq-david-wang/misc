#include<stdio.h>
#include<string.h>


typedef struct _T {
    struct _T *cs[26];
    int i;
}WNode;
WNode pool[10000*64];
int pc;
WNode *root;
WNode *alloc() {
    WNode *r = &pool[pc++];
    int i; for (i=0; i<26; i++) r->cs[i]=NULL;
    r->i = -1;
    return r;
}
void init() {
    pc = 0;
    root = alloc();
}

int addword(char *w, int wi) {
    WNode *p = root;
    char c;
    int i=0; while(1) {
        c = w[i];
        if (c==0) break;
        i++; c-='a';
        if (p->cs[c]==NULL)p->cs[c]=alloc();
        p = p->cs[c];
    }
    p->i = wi;
    return i;
}

int findword(WNode *p, char *w) {
    if (p==NULL) return -1;
    char c;
    int i=0; while(1) {
        c = w[i];
        if (c==0) break;
        i++; c-='a';
        if (p->cs[c]==NULL)return -1;
        p = p->cs[c];
    }
    return p->i;
}

int findmissing(WNode *p, char *w) {
    if (p==NULL) return -1;
    int r=-1, t;
    int i; for (i=0; i<26; i++) {
        if (p->cs[i]==NULL) continue;
        t=findword(p->cs[i], w);
        if (t<0) continue;
        if (r<0||r>t)r=t;
    }
    if (*w==0) return r;
    char c = *w-'a';
    if (p->cs[c]) {
        t = findmissing(p->cs[c], w+1);
        if (t>=0) { if (r<0||r>t) r=t; }
    }
    return r;
}

int findwrong(WNode *p, char *w) {
    if (*w==0) return -1;
    if (p==NULL) return -1;
    char c = *w-'a';
    int ri = -1, t;
    int i; for (i=0; i<26; i++) {
        if (c==i) continue;
        if (p->cs[i]==NULL) continue;
        t = findword(p->cs[i], w+1);
        if (t<0) continue;
        if (ri<0||ri>t) ri = t;
    }
    if (p->cs[c]) {
        t = findwrong(p->cs[c], w+1);
        if (t>=0) {
            if (ri<0||ri>t) ri=t;
        }
    }
    return ri;
}

int findtoomuch(WNode *p, char *w) {
    if (*w==0) return -1;
    if (p==NULL) return -1;
    char c = *w - 'a';
    int r, t;
    r = findword(p, w+1);
    if (p->cs[c]) {
        t = findtoomuch(p->cs[c], w+1);
        if (t>=0) { if (r<0||r>t) r=t; }
    }
    return r;
    /*
    // WNode *tp = p->cs[c];
    WNode *tp = p;
    int r = -1, t, i=0, j;
    while(w[i]==w[0])i++;
    for (j=0; j<i; j++) {
        t = findword(p, w+j+1);
        if (tp!=NULL) tp=tp->cs[c];
        if (t<0) continue;
        if (r<0||r>t)r=t;
    }
    if (tp) {
        t = findtoomuch(tp, w+i);
        if (t>=0) { if (r<0||r>t) r=t; }
    }
    return r;
    */
}

char buf[10000*26];
char *words[10001];
char word[32];
int main() {
    int n, q, i, r, t, l, j;
    char *p = buf, c;
    scanf("%d", &n);
    init();
    for (i=0; i<n; i++) {
        words[i] = p;
        scanf("%s", p);
        l = addword(p, i);
        p += (l+1);
    }
    scanf("%d", &q);
    for (i=0; i<q; i++) {
        scanf("%s", word);
        r = findword(root, word);
        if (r>=0) { printf("%s is correct\n", word); continue; }
        l = strlen(word);
        r = -1;
        for (j=0; j<l-1; j++) {
            c=word[j]; word[j]=word[j+1]; word[j+1]=c;
            t = findword(root, word);
            c=word[j]; word[j]=word[j+1]; word[j+1]=c;
            if (t<0) continue;
            if (r<0||r>t) r=t;
        } 
        t = findmissing(root, word);
        if (t>=0) { if (r<0||r>t) r=t; }
        t = findwrong(root, word);
        if (t>=0) { if (r<0||r>t) r=t; }
        t = findtoomuch(root, word);
        if (t>=0) { if (r<0||r>t) r=t; }
        if (r<0) printf("%s is unknown\n", word);
        else printf("%s is a misspelling of %s\n", word, words[r]);
    }
    return 0;
}
