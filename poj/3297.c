#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char name[128];
    int c;
}Project;
Project pros[101];

int mycmp(const void*a, const void*b) {
    const Project* pa = (const Project*)a;
    const Project* pb = (const Project*)b;
    if (pa->c != pb->c) return pb->c - pa->c;
    return strcmp(pa->name, pb->name);
}

typedef struct _T {
    struct _T* cs[36];
    int id;
}NNode;

NNode gpool[30000];
int gpc;
NNode *alloc() {
    NNode *r = &gpool[gpc++];
    int i; for (i=0; i<36; i++) r->cs[i] = NULL;
    r->id = -1;
    return r;
}
NNode *root;
void init() {
    gpc = 0;
    root = alloc();
}
void addsub(const char* n, int id) {
    NNode *p = root;
    char c;
    while(1) {
        c = *n++;
        if (c==0) break;
        if (c>='0' && c<='9') c -= '0';
        else c = c-'a'+10;
        if (p->cs[c] == NULL) p->cs[c] = alloc();
        p = p->cs[c];
    }
    if (p->id == id) return;
    if (p->id == -1) p->id = id;
    else p->id = -2;
}

void collect(NNode *r) {
    if (r==NULL) return;
    if (r->id>=0) pros[r->id].c++;
    int i; for (i=0; i<36; i++) if (r->cs[i]) collect(r->cs[i]);
}

void readline(char *p) {
    char c;
    int i=0;
    while(1) {
        c = getchar();
        if (c==EOF || c== '\n') break;
        p[i++] = c;
    }
    p[i] = 0;
}


int main() {
    int pc, i;
    char *p;
    while(1) {
        pc = 0;
        p = pros[pc].name;
        readline(p);
        if (p[0] == '0') break;
        pros[pc].c = 0;
        pc++;
        init();
        while(1) {
            // read students until not
            while(1) {
                p = pros[pc].name;
                readline(p);
                if (p[0]<'a' || p[0]>'z')break;
                // new student p -> pc-1
                addsub(p, pc-1);
            }
            if (p[0] == '1') break;
            pros[pc].c = 0;
            pc++;
        }
        // collect all names
        collect(root);
        // sort
        qsort(pros, pc, sizeof(Project), mycmp);
        for (i=0; i<pc; i++) printf("%s %d\n", pros[i].name, pros[i].c);
    }
    return 0;
}
