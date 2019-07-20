#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _T {
    struct _T *p, *n, *u, *d, *head;
    char i, j, k;
    int c;
}DLink;

DLink pool[100000];
int gpc;
#define EMARK '-'
DLink *head, *tail;
char check[16][16][16];
DLink *link[16][16][16];
int rmarks[16], cmarks[16], bmarks[4][4];
char map[16][24];
DLink *stack[10000];
DLink *stackh[10000];
int stop, hstop;
int gcc;
int dfs(){
    if (head->n==tail) return 1;
    gcc++; if(gcc>10000000) return 1;
    DLink *p = head->n, *dp, *np, *hp, *nhp;
    int i, j, k, cstop, chstop;
    i = p->c;
    hp = p->n; while(hp!=tail) {
        if (hp->c<i) { i=hp->c; p=hp; }
        hp = hp->n;
    }
    if (i==0) return 0;
    // printf("choosing node with count %d\n", i);
    // find min colume p....
    dp=p->d;
    if (stop>10000||hstop>10000) printf("stack not enough: %d,%d\n", stop, hstop);
    while(dp!=NULL) {
        // try use row dp, and change row only
        i=dp->i; j=dp->j; k=dp->k;
        cstop = stop; chstop = hstop;
        map[i][j] = k+'A';
        // printf("try %d,%d %c\n", i, j, map[i][j]);
        // collect headers
        np=dp->p; while(np!=NULL) {
            hp = np->head;
            if (hp->p->n==hp) {
                hp->p->n = hp->n;
                hp->n->p = hp->p;
                stackh[hstop++]=hp;
            }
            np=np->p;
        }
        np=dp; while(np!=NULL) {
            hp = np->head;
            if (hp->p->n==hp) {
                hp->p->n = hp->n;
                hp->n->p = hp->p;
                stackh[hstop++]=hp;
            }
            np=np->n;
        }
        for (i=chstop; i<hstop; i++) {
            hp = stackh[i];
            // collect rows that satisfy the colume
            hp=hp->d; while(hp!=NULL) {
                nhp = hp->d;
                np=hp->p; while(np!=NULL) { 
                    if (np->u->d == np) {
                        stack[stop++]=np;
                        np->head->c--;
                        np->u->d = np->d;
                        if (np->d) np->d->u=np->u;
                    }
                    np=np->p;
                }
                np=hp; while(np!=NULL) {
                    if (np->u->d == np) {
                        stack[stop++]=np;
                        np->head->c--;
                        np->u->d = np->d;
                        if (np->d) np->d->u=np->u;
                    }
                    np=np->n;
                }
                hp=nhp;
            }
        }
        if (dfs()) return 1;
        // restore
        for (i=stop-1; i>=cstop; i--) {
            np = stack[i];
            np->u->d=np; 
            np->head->c++;
            if (np->d) np->d->u=np;
        } stop=cstop;
        for (i=hstop-1; i>=chstop; i--) {
            np = stackh[i];
            np->p->n=np; np->n->p=np;
        } hstop = chstop;
        dp = dp->d;
    }
    return 0;
}

void process() {
    int i, j, k, si, sj, bi, bj, m;
    DLink *p, *np, *nnp, *nnnp;
    gpc = 0;
    stop = 0; hstop=0; gcc=0;
    head=&pool[gpc++];
    tail=&pool[gpc++];
    head->p=NULL; head->n=tail; head->u=NULL; head->d=NULL; head->head=NULL;
    tail->p=head; tail->n=NULL; tail->u=NULL; tail->d=NULL; head->head=NULL;
    p = head;
    // build marks;
    for (i=0; i<4; i++) for (j=0; j<4; j++) bmarks[i][j]=0;
    for (i=0; i<16; i++) rmarks[i]=cmarks[i]=0;
    for (i=0; i<16; i++){ 
        for (j=0; j<16; j++) {
            if (map[i][j]==EMARK) continue;
            k = map[i][j]-'A'; m=(1<<k);
            if (k<0||k>=26) printf("%c wrong\n", map[i][j]);
            rmarks[i] |= m;
            cmarks[j] |= m;
            bmarks[i/4][j/4] |= m;
        }
    }
    // build check
    for (i=0; i<16; i++) for (j=0; j<16; j++) {
        for (k=0; k<16; k++) {
            link[i][j][k]=NULL;
            check[i][j][k]=0;
            if (map[i][j]!=EMARK) continue;
            m=(1<<k);
            if (rmarks[i]&m) continue;
            if (cmarks[j]&m) continue;
            if (bmarks[i/4][j/4]&m) continue;
            check[i][j][k]=1;
            // if (map[i][j]!=EMARK) printf("error\n");
        }
    }
    // i,j should have element
    for (i=0; i<16; i++) for (j=0; j<16; j++) {
        if (map[i][j]!=EMARK) continue;
        np = &pool[gpc++]; np->u=NULL; np->d=NULL; np->p=p; np->n=p->n; p->n->p=np; p->n=np; p=np;
        nnp=np; np->c = 0;
        for (k=0; k<16; k++) {
            if (check[i][j][k]==0) continue;
            nnnp = &pool[gpc++]; nnnp->head=np; nnnp->u=nnp; nnp->d=nnnp; nnnp->d=NULL; nnp=nnnp; nnnp->n=NULL;
            nnnp->i=i; nnnp->j=j; nnnp->k=k;
            nnnp->p = link[i][j][k]; if (link[i][j][k]!=NULL) link[i][j][k]->n=nnnp;
            link[i][j][k]=nnnp;
            np->c++;
        }
    }
    // row should have k
    for (i=0; i<16; i++) for (k=0; k<16; k++) {
        if (rmarks[i]&(1<<k)) continue;
        np = &pool[gpc++]; np->u=NULL; np->d=NULL; np->p=p; np->n=p->n; p->n->p=np; p->n=np; p=np;
        nnp=np; np->c=0;
        for (j=0; j<16; j++) {
            if (check[i][j][k]==0) continue;
            nnnp = &pool[gpc++]; nnnp->head=np; nnnp->u=nnp; nnp->d=nnnp; nnnp->d=NULL; nnp=nnnp; nnnp->n=NULL;
            nnnp->i=i; nnnp->j=j; nnnp->k=k;
            nnnp->p = link[i][j][k]; if (link[i][j][k]!=NULL) link[i][j][k]->n=nnnp;
            link[i][j][k]=nnnp;
            np->c++;
        }
    }
    // col shoudl have k
    for (j=0; j<16; j++) for (k=0; k<16; k++) {
        if (cmarks[j]&(1<<k)) continue;
        np = &pool[gpc++]; np->u=NULL; np->d=NULL; np->p=p; np->n=p->n; p->n->p=np; p->n=np; p=np;
        nnp=np; np->c=0;
        for (i=0; i<16; i++) {
            if (check[i][j][k]==0) continue;
            nnnp = &pool[gpc++]; nnnp->head=np; nnnp->u=nnp; nnp->d=nnnp; nnnp->d=NULL; nnp=nnnp; nnnp->n=NULL;
            nnnp->i=i; nnnp->j=j; nnnp->k=k;
            nnnp->p = link[i][j][k]; if (link[i][j][k]!=NULL) link[i][j][k]->n=nnnp;
            link[i][j][k]=nnnp;
            np->c++;
        }
    }
    // block should have k
    for (bi=0; bi<4; bi++) for (bj=0; bj<4; bj++) {
        for (k=0; k<16; k++) {
            if (bmarks[bi][bj]&(1<<k)) continue;
            np = &pool[gpc++]; np->u=NULL; np->d=NULL; np->p=p; np->n=p->n; p->n->p=np; p->n=np; p=np;
            nnp=np; np->c=0;
            for (si=0; si<4; si++) for (sj=0; sj<4; sj++) {
                i=bi*4+si; j=bj*4+sj;
                if (check[i][j][k]==0) continue;
                nnnp = &pool[gpc++]; nnnp->head=np; nnnp->u=nnp; nnp->d=nnnp; nnnp->d=NULL; nnp=nnnp; nnnp->n=NULL;
                nnnp->i=i; nnnp->j=j; nnnp->k=k;
                nnnp->p = link[i][j][k]; if (link[i][j][k]!=NULL) link[i][j][k]->n=nnnp;
                link[i][j][k]=nnnp;
                np->c++;
            }
        }
    }
    dfs();
}
int main() {
    int i, j=0;
    while(scanf("%s", map[0])==1) {
        for (i=1; i<16; i++) scanf("%s", map[i]);
        j++;
        process();
        if (j>1) printf("\n");
        for (i=0; i<16; i++) printf("%s\n", map[i]);
    } 
    return 0;
}


