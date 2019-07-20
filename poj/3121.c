#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct { int *cs, cc; }SNode;
SNode gsets[2000];
int gsn;
int gpool[2000*200];
int gstack[2000*200];
int gstop;
int gpc;
void init() {
    gpc=0;
    gsets[0].cs=NULL;
    gsets[0].cc=0;
    gsn=1;
}
int addset(SNode *a) {
    int i, j; for (i=0; i<gsn; i++) {
        if (a->cc != gsets[i].cc) continue;
        for (j=0; j<a->cc; j++) if (a->cs[j]!=gsets[i].cs[j]) break;
        if (j==a->cc) return i;
    }
    // no match, add it
    gsets[gsn++] = *a;
    return -gsn;
}

int unionit(int a, int b) {
    SNode n;
    int *p = &gpool[gpc];
    int ai=0, bi=0, k=0;
    int ca, cb;
    while(1) {
        if (ai==gsets[a].cc) {
            for(; bi<gsets[b].cc; bi++) p[k++] = gsets[b].cs[bi]; break;
        }
        if (bi==gsets[b].cc) {
            for(; ai<gsets[a].cc; ai++) p[k++] = gsets[a].cs[ai]; break;
        }
        ca = gsets[a].cs[ai];
        cb = gsets[b].cs[bi];
        if (ca<cb) {
            p[k++] = ca; ai++;
        } else if (ca>cb) {
            p[k++] = cb; bi++;
        } else {
            p[k++] = ca; ai++; bi++;
        }
    }
    n.cc = k;
    n.cs = p;
    a=addset(&n); if (a<0) { gpc+=(k+1); a=-a-1; }
    return a;
}

int intersect(int a, int b) {
    SNode n;
    int *p = &gpool[gpc];
    int ai=0, bi=0, k=0;
    int ca, cb;
    while(1) {
        if (ai==gsets[a].cc) break;
        if (bi==gsets[b].cc) break;
        ca = gsets[a].cs[ai];
        cb = gsets[b].cs[bi];
        if (ca<cb) ai++;
        else if (ca>cb) bi++;
        else {
            p[k++] = ca; ai++; bi++;
        }
    }
    n.cc = k;
    n.cs = p;
    a=addset(&n); if (a<0) { gpc+=(k+1); a=-a-1; }
    return a;
}

int add(int a, int b) {
    SNode n;
    int *p = &gpool[gpc], ca, k=0;
    int i; for (i=0; i<gsets[a].cc; i++) {
        ca = gsets[a].cs[i];
        if (ca==b) return a;
        if (ca>b) break;
        p[k++] = ca;
    }
    p[k++] = b;
    for (; i<gsets[a].cc; i++) p[k++] = gsets[a].cs[i];
    n.cc = k;
    n.cs = p;
    a=addset(&n); if (a<0) { gpc+=(k+1); a=-a-1; }
    return a;
}

int main() {
    int tc, ti, c, i;
    int a, b;
    char cmd[16];
    scanf("%d", &tc);
    for (ti=0; ti<tc; ti++) {
        init();
        gstop=0;
        scanf("%d", &c); for (i=0; i<c; i++) {
            scanf("%s", cmd);
            if (cmd[0]=='P') { gstack[gstop++]=0; }
            else if (cmd[0]=='D') { a=gstack[gstop-1];  gstack[gstop++]=a; }
            else if (cmd[0]=='U') {
                a=gstack[--gstop]; b=gstack[--gstop];
                a=unionit(a, b); gstack[gstop++] = a;
            } else if (cmd[0]=='I') {
                a=gstack[--gstop]; b=gstack[--gstop];
                a=intersect(a, b); gstack[gstop++] = a;
            } else if (cmd[0]=='A') {
                a=gstack[--gstop]; b=gstack[--gstop];
                a=add(b, a); gstack[gstop++] = a;
            }
            a = gstack[gstop-1];
            printf("%d\n", gsets[a].cc);
        }
        printf("***\n");
    }
    return 0;
}


