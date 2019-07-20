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
#define EMARK '0'
DLink *head, *tail;
char check[16][16][16];
DLink *link[16][16][16];
int rmarks[16], cmarks[16], bmarks[4][4];
char map[16][24];
char omap[16][24];
DLink *stack[10000];
DLink *stackh[10000];
int stop, hstop;
int dfs(){
    if (head->n==tail) return 1;
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
    while(dp!=NULL) {
        // try use row dp, and change row only
        i=dp->i; j=dp->j; k=dp->k;
        cstop = stop; chstop = hstop;
        map[i][j] = k+'1';
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
    stop = 0; hstop=0;
    head=&pool[gpc++];
    tail=&pool[gpc++];
    head->p=NULL; head->n=tail; head->u=NULL; head->d=NULL; head->head=NULL;
    tail->p=head; tail->n=NULL; tail->u=NULL; tail->d=NULL; head->head=NULL;
    p = head;
    // build marks;
    for (i=0; i<3; i++) for (j=0; j<3; j++) bmarks[i][j]=0;
    for (i=0; i<9; i++) rmarks[i]=cmarks[i]=0;
    for (i=0; i<9; i++){ 
        for (j=0; j<9; j++) {
            if (map[i][j]==EMARK) continue;
            k = map[i][j]-'1'; m=(1<<k);
            rmarks[i] |= m;
            cmarks[j] |= m;
            bmarks[i/3][j/3] |= m;
        }
    }
    // build check
    for (i=0; i<9; i++) for (j=0; j<9; j++) {
        for (k=0; k<9; k++) {
            link[i][j][k]=NULL;
            check[i][j][k]=0;
            if (map[i][j]!=EMARK) continue;
            m=(1<<k);
            if (rmarks[i]&m) continue;
            if (cmarks[j]&m) continue;
            if (bmarks[i/3][j/3]&m) continue;
            check[i][j][k]=1;
        }
    }
    // i,j should have element
    for (i=0; i<9; i++) for (j=0; j<9; j++) {
        if (map[i][j]!=EMARK) continue;
        np = &pool[gpc++]; np->u=NULL; np->d=NULL; np->p=p; np->n=p->n; p->n->p=np; p->n=np; p=np;
        nnp=np; np->c = 0;
        for (k=0; k<9; k++) {
            if (check[i][j][k]==0) continue;
            nnnp = &pool[gpc++]; nnnp->head=np; nnnp->u=nnp; nnp->d=nnnp; nnnp->d=NULL; nnp=nnnp; nnnp->n=NULL;
            nnnp->i=i; nnnp->j=j; nnnp->k=k;
            nnnp->p = link[i][j][k]; if (link[i][j][k]!=NULL) link[i][j][k]->n=nnnp;
            link[i][j][k]=nnnp;
            np->c++;
        }
    }
    // row should have k
    for (i=0; i<9; i++) for (k=0; k<9; k++) {
        if (rmarks[i]&(1<<k)) continue;
        np = &pool[gpc++]; np->u=NULL; np->d=NULL; np->p=p; np->n=p->n; p->n->p=np; p->n=np; p=np;
        nnp=np; np->c=0;
        for (j=0; j<9; j++) {
            if (check[i][j][k]==0) continue;
            nnnp = &pool[gpc++]; nnnp->head=np; nnnp->u=nnp; nnp->d=nnnp; nnnp->d=NULL; nnp=nnnp; nnnp->n=NULL;
            nnnp->i=i; nnnp->j=j; nnnp->k=k;
            nnnp->p = link[i][j][k]; if (link[i][j][k]!=NULL) link[i][j][k]->n=nnnp;
            link[i][j][k]=nnnp;
            np->c++;
        }
    }
    // col shoudl have k
    for (j=0; j<9; j++) for (k=0; k<9; k++) {
        if (cmarks[j]&(1<<k)) continue;
        np = &pool[gpc++]; np->u=NULL; np->d=NULL; np->p=p; np->n=p->n; p->n->p=np; p->n=np; p=np;
        nnp=np; np->c=0;
        for (i=0; i<9; i++) {
            if (check[i][j][k]==0) continue;
            nnnp = &pool[gpc++]; nnnp->head=np; nnnp->u=nnp; nnp->d=nnnp; nnnp->d=NULL; nnp=nnnp; nnnp->n=NULL;
            nnnp->i=i; nnnp->j=j; nnnp->k=k;
            nnnp->p = link[i][j][k]; if (link[i][j][k]!=NULL) link[i][j][k]->n=nnnp;
            link[i][j][k]=nnnp;
            np->c++;
        }
    }
    // block should have k
    for (bi=0; bi<3; bi++) for (bj=0; bj<3; bj++) {
        for (k=0; k<9; k++) {
            if (bmarks[bi][bj]&(1<<k)) continue;
            np = &pool[gpc++]; np->u=NULL; np->d=NULL; np->p=p; np->n=p->n; p->n->p=np; p->n=np; p=np;
            nnp=np; np->c=0;
            for (si=0; si<3; si++) for (sj=0; sj<3; sj++) {
                i=bi*3+si; j=bj*3+sj;
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
char perms[1296][9];
int gppc;
int checkit() {
    int i, j, r, c, pi, pj, k, m;
    int perm[16];
    char row1[16], row2[16], p;
    for (r=0; r<gppc; r++) {
        // trial test first....
        for (i=0; i<9; i++) row1[i]=map[0][perms[r][i]];
        for (m=1; m<9; m++) {
            for (i=0; i<9; i++) row2[i]=map[m][perms[r][i]]; p = 0;
            for (i=0; i<9; i++) {
                for (k=0; k<9; k++) {
                    if (i==k&&(i/3)!=(k/3)) continue;
                    for (j=0; j<9; j++) perm[row1[j]]=omap[i][j];
                    for (j=0; j<9; j++) if (perm[row2[j]]!=omap[k][j]) break;
                    if (j==9) { p=1; break; }
                } if (p==1) break;
            }
            if (p==0) {
                for (i=0; i<9; i++) {
                    for (k=0; k<9; k++) {
                        if (i==k&&(i/3)!=(k/3)) continue;
                        for (j=0; j<9; j++) perm[row1[j]]=omap[j][i];
                        for (j=0; j<9; j++) if (perm[row2[j]]!=omap[j][k]) break;
                        if (j==9) { p=1; break; }
                    } if (p==1) break;
                }
            }
            if (p==0) {
                for (i=0; i<9; i++) {
                    for (k=0; k<9; k++) {
                        if (i==k&&(i/3)!=(k/3)) continue;
                        for (j=0; j<9; j++) perm[row1[8-j]]=omap[j][i];
                        for (j=0; j<9; j++) if (perm[row2[8-j]]!=omap[j][k]) break;
                        if (j==9) { p=1; break; }
                    } if (p==1) break;
                }
            }
            if (p==0) break;
        }
        if (m==9) break;
    }
    if (r==gppc) return 0;
    return 1;
    for (r=0; r<gppc; r++) {
        for (c=0; c<gppc; c++) {
            for (i=0; i<9; i++) {
                pi = perms[r][i];
                for (j=0; j<9; j++) {
                    pj = perms[c][j];
                    if (map[pi][pj] != omap[j][8-i]) break;
                } if (j<9) break;
            } if (i==9) return 1;
            for (i=0; i<9; i++) {
                pi = perms[r][i];
                for (j=0; j<9; j++) {
                    pj = perms[c][j];
                    if (map[pi][pj] != omap[8-j][i]) break;
                } if (j<9) break;
            } if (i==9) return 1;
            pi = perms[r][0]; 
            for (j=0; j<9; j++) {
                pj = perms[c][j];
                perm[map[pi][pj]]=omap[0][j];
            }
            for (i=1; i<9; i++) {
                pi = perms[r][i]; 
                for (j=0; j<9; j++) {
                    pj = perms[c][j];
                    if (perm[map[pi][pj]] != omap[i][j]) break;
                } if (j<9) break;
            }
            if (i==9) return 1;
        }
    }
    return 0;
}
char choices[][3] = {
    {0, 1, 2},
    {0, 2, 1},
    {1, 0, 2},
    {1, 2, 0},
    {2, 0, 1},
    {2, 1, 0},
};
int buildperm() {
    int i, j, k, m, n;
    char cc[9];
    gppc=0;
    for (i=0; i<6; i++) {
        cc[0] = choices[i][0];
        cc[1] = choices[i][1];
        cc[2] = choices[i][2];
        for (j=0; j<6; j++) {
            cc[3] = 3+choices[j][0];
            cc[4] = 3+choices[j][1];
            cc[5] = 3+choices[j][2];
            for (k=0; k<6; k++) {
                cc[6] = 6+choices[k][0];
                cc[7] = 6+choices[k][1];
                cc[8] = 6+choices[k][2];
                for (m=0; m<6; m++) {
                    perms[gppc][0]=cc[choices[m][0]*3];
                    perms[gppc][1]=cc[choices[m][0]*3+1];
                    perms[gppc][2]=cc[choices[m][0]*3+2];
                    perms[gppc][3]=cc[choices[m][1]*3];
                    perms[gppc][4]=cc[choices[m][1]*3+1];
                    perms[gppc][5]=cc[choices[m][1]*3+2];
                    perms[gppc][6]=cc[choices[m][2]*3];
                    perms[gppc][7]=cc[choices[m][2]*3+1];
                    perms[gppc][8]=cc[choices[m][2]*3+2];
                    gppc++;
                }
            }
        }
    }
    for (i=0; i<1000; i++) {
        j = rand() % gppc;
        k = rand() % gppc;
        for (m=0; m<9; m++) {
            n = perms[j][m]; perms[j][m]=perms[k][m]; perms[k][m]=n;
        }
    }
}
int main() {
    int i, tc, ti, j;
    buildperm();
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        for (i=0; i<9; i++) scanf("%s", omap[i]);
        for (i=0; i<9; i++) scanf("%s", map[i]);
        process();
        // for (i=0; i<9; i++) printf("%s\n", map[i]);
        for (i=0; i<9; i++) for (j=0; j<9; j++) { map[i][j]-='1'; omap[i][j]-='1'; }
        i = checkit(); if (i) printf("Yes\n"); else printf("No\n");
    } 
    return 0;
}


