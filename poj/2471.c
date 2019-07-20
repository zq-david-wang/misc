#include<stdio.h>

typedef struct _T {
    struct _T *cs[26];
    int c;
}WNode;

WNode gpool[25*10000];
int gpc;
WNode *root;
WNode *alloc() {
    WNode *r = &gpool[gpc++];
    int i; for (i=0; i<26; i++) r->cs[i] = NULL;
    r->c = 0;
    return r;
}
void init() {
    gpc = 0;
    root = alloc();
}

int addword(char *b, int s, int e) {
    WNode *p = root;
    char c;
    while(s<e) {
        c = b[s++];
        if (c>='A'&&c<='Z') c -= 'A';
        else c-='a';
        if (p->cs[c]==NULL) p->cs[c] = alloc();
        p = p->cs[c];
    }
    p->c++;
    return p->c;
}

int readword(char *b) {
    char c;
    int i=0;
    while(1) {
        c = getchar();
        if (c==EOF) return -1;
        if ((c>='a'&&c<='z') || (c>='A'&&c<='Z'))break;
    }
    b[i++] = c;
    while(1) {
        c = getchar();
        if ((c>='a'&&c<='z') || (c>='A'&&c<='Z')) {
            b[i++] = c;
        } else {
            break;
        }
    }
    b[i] = 0;
    return i;
}

int gcd(int a, int b) {
    int t;
    while(a!=0) {
        t = a;
        a = b%a;
        b = t;
    }
    return b;
}

char buf[128];
char *endword = "BULLSHIT";
int main() {
    int gc=0, gw=0, i, j;
    int eof = 0;
    int c, w;
    while(1) { 
        init();
        w = 0;
        while(1) {
            i = readword(buf);
            if (i==-1) {
                eof = 1;
                break;
            }
            // printf("new word %s\n", buf);
            for (j=0; j<8; j++) if (endword[j]!=buf[j]) break;
            if (j==8) {
                gc++;
                gw += w;
                break;
            }
            w += (addword(buf, 0, i)==1);
        }
        if (eof) break;
    }
    int g = gcd(gw, gc);
    gw /= g;
    gc /= g;
    printf("%d / %d\n", gw, gc);
}
