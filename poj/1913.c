#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    short i, c;
}IngRequest;
IngRequest ipool[200000];
int idc;
typedef struct {
    char name[32];
    int ci, oc, cost, li;
    IngRequest *is;
} CNode;
CNode cocktails[10001];

char names[10001][32];
int rnamei[10001];
int nc;
struct { int ni, cap, cost; } ingreds[10001];
void assert(int *p) {
    *p=0;
}

int addname() {
    rnamei[nc] = -1;
    if (strlen(names[nc])>=32) assert(0);
    int i; for (i=0; i<nc; i++) if (strcmp(names[i], names[nc])==0) return i;
    return i;
}
int mycmp(const void *a, const void *b) {
    const CNode *pa = (const CNode*)a;
    const CNode *pb = (const CNode*)b;
    if (pa->oc != pb->oc) return pb->oc-pa->oc;
    return pa->li-pb->li;
}
int main() {
    int tc, ti, cn, i, j, ci, cc, ni, in, cost, k, on;
    int lo, nj;
    char oname[32], served;
    scanf("%d", &tc);
    for (ti=1; ti<=tc; ti++) {
        scanf("%d", &cn);
        idc=0; nc=0;
        for (i=0; i<cn; i++) {
            scanf("%s %d", cocktails[i].name, &ci);
            if (strlen(cocktails[i].name)>=32) assert(0);
            cocktails[i].ci = ci;
            cocktails[i].li = i;
            cocktails[i].oc = 0;
            cocktails[i].is = ipool+idc;
            for (j=0; j<ci; j++) {
                scanf("%s %d", names[nc], &cc);
                ni = addname(); if (ni==nc) nc++;
                ipool[idc].i = ni; ipool[idc].c = cc; idc++;
            }
            if (idc>=sizeof(ipool)/sizeof(ipool[0])) assert(0);
        }
        scanf("%d", &in);
        for (i=0; i<in; i++) {
            scanf("%s %d %d", names[nc], &cc, &cost);
            ni = addname(); if (ni==nc) nc++;
            rnamei[ni] = i;
            ingreds[i].ni = ni;
            ingreds[i].cap = cc;
            ingreds[i].cost = cost;
        }
        for (i=0; i<cn; i++) {
            cost = 0;
            for (j=0; j<cocktails[i].ci; j++) {
                ni = cocktails[i].is[j].i;
                ni = rnamei[ni];
                if (ni==-1) { cost=-1; break;}
                cc = cocktails[i].is[j].c;
                cost += (cc*ingreds[ni].cost);
            }
            if (cost<0) cocktails[i].cost = -1;
            else cocktails[i].cost = cost*3+10000;
        }
        scanf("%d", &on);
        lo = -1;
        /*
        for (i=0; i<cn; i++) {
            printf("cocktail %d: %s cost %d\n", i, cocktails[i].name, cocktails[i].cost);
            for (j=0; j<cocktails[i].ci; j++) {
                ni = cocktails[i].is[j].i;
                cc = cocktails[i].is[j].c;
                printf("--ingredent %s(%d): %d\n", names[ni], rnamei[ni], cc);
            }
        }
        */
        for (i=0; i<on; i++) {
            scanf("%s", oname);
            if (strlen(oname)>=32) assert(0);
            for (j=0; j<cn; j++) if (strcmp(cocktails[j].name, oname)==0) break;
            if (j==cn) continue;
            nj = j;
            if (lo==nj) { nj++; nj%=cn; }
            served=0;
            while(1) {
                if (lo==nj) break;
                //try nj
                if (cocktails[nj].cost>=0) {
                    for (k=0; k<cocktails[nj].ci; k++) {
                        ni = cocktails[nj].is[k].i;
                        ni = rnamei[ni];
                        cc = cocktails[nj].is[k].c;
                        if (cc>ingreds[ni].cap) break;
                    }
                    if (k==cocktails[nj].ci) {
                        for (k=0; k<cocktails[nj].ci; k++) {
                            ni = cocktails[nj].is[k].i;
                            ni = rnamei[ni];
                            cc = cocktails[nj].is[k].c;
                            ingreds[ni].cap -= cc;
                        }
                        served=1;
                        cocktails[nj].oc++;
                        // printf("serving %s\n", cocktails[nj].name);
                        break;
                    }
                }
                nj++; nj%=cn;
                if (nj==j) break;
            }
            if (served) lo = nj;
        }
        qsort(cocktails, cn, sizeof(cocktails[0]), mycmp);
        // for (i=0; i<cn; i++) printf("%d: %s order %d\n", i, cocktails[i].name, cocktails[i].oc);
        printf("Scenario %d top cocktails:\n", ti);
        for (i=0; i<10; i++) {
            if (cocktails[i].oc==0) break;
            printf("%d %s %d %d\n", i+1, cocktails[i].name, cocktails[i].oc, cocktails[i].cost);
        }
    }
    return 0;
}
