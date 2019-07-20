#include<stdio.h>

char buf[1024];
struct { short c, p; }nodes[64];
typedef struct _T {
    struct _T *n;
    int b;
}NNode;
NNode pool[128];
int pc;
NNode *nei[64];
int readline() {
    int i=0;
    char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        buf[i++] = c;
    }
    buf[i]=0;
    return i;
}

int parse(char *b, int p) {
    int i=0, n=0;
    while(b[i]!='('&&b[i]!=0&&b[i]!=')')i++;
    if (b[i]!='(') return i;
    i++;
    while(b[i]>='0'&&b[i]<='9') { n=n*10+b[i]-'0'; i++; }
    if (p>=0) { 
        NNode *pp=&pool[pc++]; pp->b=n; pp->n=nei[p]; nei[p]=pp;
        pp=&pool[pc++]; pp->b=p; pp->n=nei[n]; nei[n]=pp;
    }
    while(1) {
        i += parse(b+i, n);
        if (b[i]==')') { i++; break;}
    }
    return i;
}

int count(int r, int p) {
    nodes[r].p = p;
    NNode *pp = nei[r];
    while(pp!=NULL) {
        if (pp->b != p) {
            nodes[r].c++;
            count(pp->b, r);
        }
        pp=pp->n;
    }
}
int main() {
    int i, c,j;
    while(readline()) {
        pc = 0;
        for (i=1; i<=50; i++) { nei[i]=NULL; nodes[i].c = 0; nodes[i].p = 0;}
        parse(buf, -1);
        for (i=50; i>=1; i--) if (nei[i])break;
        count(i, 0);
        c = 0;
        for (i=1; i<=50; i++) {
            for (j=1; j<=50; j++) {
                if (nodes[j].p==0) continue;
                if (nodes[j].c) continue;
                break;
            }
            if (j>50) break;
            if (nodes[j].p<1) break;
            nodes[nodes[j].p].c--;
            if (c==0) printf("%d", nodes[j].p);
            else printf(" %d", nodes[j].p);
            nodes[j].p = 0;
            c++;
        }
        printf("\n");
    }
    return 0;
}
