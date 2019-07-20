#include<stdio.h>

char buf[280];
char cache1[280], cache2[280], cache[280];
typedef struct _T{
    struct _T *cs[2];
}CNode;
CNode pool[1000000];
int gcc;
CNode *alloc() {
    CNode *r = &pool[gcc++];
    r->cs[0]=r->cs[1]=NULL;
    if (gcc>=sizeof(pool)/sizeof(pool[0])) printf("not enough space\n");
    return r;
}
CNode *root;
void init() {
    gcc=0;
    root = alloc();
}
char addstate(const char *s, int n) {
    char c, e=1; int i=0;
    CNode *p = root;
    for (i=0; i<n; i++){
        c = s[i];
        if (p->cs[c]==NULL) { p->cs[c]=alloc(); e=0; }
        p=p->cs[c];
    }
    return e;
}
int main() {
    long long m, s;
    int ic=0, i, l, c, j, r;
    char *p1, *p2, v, *p, ss, *tp;
    while(scanf("%lld", &m)==1) {
        ic++;
        scanf("%s", buf);
        printf("LINE %d", ic);
        p = cache; v=1;
        i=0; while(buf[i]) {
            if (buf[i]=='W') p[i]=0;
            else if (buf[i]=='B') p[i]=1; 
            else {v=0; break;}
            i++;
        }
        if ((i&1)==0) v=0;
        if (p[0]!=0||p[i-1]!=0) v=0;
        if (v==0) { printf(" NONE\n"); continue; }
        c=0; l=i; for (r=0; r<=255; r++) {
            init();
            p1=cache1; p2=cache2;
            for (j=0; j<l; j++) p1[j]=0; p1[j/2]=1;
            addstate(p, l);
            s=1;
            while(1) {
                if (addstate(p1, l)) break;
                s++; if (s>m) break;
                p2[0]=0; p2[l-1]=0;
                for (i=1; i<l-1; i++) {
                    ss = p1[i-1]*4+p1[i]*2+p1[i+1];
                    p2[i]=(r>>ss)&1;
                }
                tp=p1; p1=p2; p2=tp;
            }
            for (j=0; j<l; j++) if (p1[j]!=p[j]) break;
            if (j==l) {
                c++;
                printf(" (%d,%lld)", r, s);
            }
        }
        if (c==0) printf(" NONE\n");
        else printf("\n");
    }
    return 0;
}
