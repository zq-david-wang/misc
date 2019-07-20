#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char n[32], ic;
    short ps[100], is[100], lv[100], mv[100], mx[100];
} PNode;
PNode ps[16];
char inames[100][32];
int gic;
int addname(char *n) {
    int i; for (i=0; i<gic; i++) if (strcmp(n, inames[i])==0) return i;
    strcpy(inames[gic], n); gic++;
    return i;
}
char line[128];
int readline() {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        line[i++] = c;
    }
    line[i]=0;
    return i;
}
char buf1[128], buf2[128];
short qname[128], qtype[128];
int main() {
    int p, i, n, j, c, k, ni, q, pp;
    int lj, max, tv;
    int ss, cc, ii;
    while(1) {
        readline();
        sscanf(line, "%d", &p); if (p==0) break;
        gic=0;
        for (i=0; i<p; i++) {
            readline(); sscanf(line, "%s", ps[i].n);
            readline(); sscanf(line, "%d", &n);
            ps[i].ic = n;
            for (j=0; j<n; j++) {
                readline();
                c = sscanf(line, "%s %s", buf1, buf2);
                pp=-1; if (c==2) { k=strlen(buf2); buf2[k-1]=0; sscanf(buf2, "%d", &pp); }
                ps[i].ps[j]=pp;
                ni = addname(buf1);
                ps[i].is[j] = ni;
            }
        }
        for (i=0; i<p; i++) {
            for (j=0; j<100; j++) ps[i].mv[j]=ps[i].lv[j]=0;
            c=0;
            for (j=0; j<ps[i].ic; j++) if (ps[i].ps[j]!=-1) break;
            k=1; if (j<ps[i].ic&&ps[i].ps[j]==0) k=0;
            ss=0; cc=0;
            for (j=ps[i].ic-1; j>=0; j--) {
                cc++;
                if (ps[i].ps[j]!=-1) {
                    k=ps[i].ps[j];
                    ps[i].mx[j] = cc*ps[i].ps[j]+ss;
                    ss = ps[i].mx[j];
                    cc=0;
                }
                ps[i].lv[ps[i].is[j]]=k;
                c+=k;
                if (k==0) {
                    for (ii=j-1; ii>=0; ii--) if (ps[i].ps[ii]!=-1) break;
                    if (ii<0||ps[i].ps[ii]>0) k=1;
                }
            }
            j=ps[i].ic-1;
            while (c>100) {
                ni = ps[i].is[j--];
                ps[i].lv[ni]=0;
                c--;
            }
            c = 100-c; lj=0; max=100; 
            for (j=0; j<ps[i].ic; j++) {
                // from lj to j, share c
                tv = c/(j-lj+1)+ps[i].lv[ps[i].is[j]];
                if (tv>max) tv=max;
                ps[i].mv[ps[i].is[j]]=tv;
                if (ps[i].ps[j]!=-1) {
                    ps[i].mv[ps[i].is[j]]=ps[i].ps[j];
                    lj = j+1; max=ps[i].ps[j];
                }
            }
            // rebuild lv
            max=100; c=100;
            for (j=0; j<ps[i].ic; j++) {
                if (c<=0) break;
                ni = ps[i].is[j];
                if (ps[i].ps[j]!=-1) {
                    c -= ps[i].ps[j];
                    max = ps[i].ps[j];
                } else {
                    for (k=j+1; k<ps[i].ic; k++) if (ps[i].ps[k]!=-1) break;
                    ss = 0; if (k<ps[i].ic) ss = ps[i].mx[k];
                    if (ps[i].lv[ni]*(k-j)+ss<c) {
                        cc = (c-ss+k-j-1)/(k-j);
                        if (cc>ps[i].lv[ni]) ps[i].lv[ni]=cc;
                    }
                    c-=max;
                }
            }
        }
        readline(); sscanf(line, "%d", &q);
        for (k=0; k<q; k++) {
            readline(); sscanf(line, "%s %s", buf1, buf2);
            qname[k] = addname(buf2);
            qtype[k] = buf1[0];
        }
        /*
        for (k=0; k<gic; k++) {
            for (i=0; i<p; i++) printf("%s %d: %d,%d\n", inames[k], i, ps[i].lv[k], ps[i].mv[k]);
            printf("---\n");
            if (k>4) break;
        } 
        */
        for (k=0; k<q; k++) {
            ni = qname[k];
            lj=0;
            if (qtype[k]=='l') {
                for (i=0; i<p; i++) {
                    for (j=0; j<p; j++) {
                        if (i==j) continue;
                        if (ps[i].lv[ni]>ps[j].mv[ni]) break;
                    }
                    if (j==p) {
                        if (lj>0) printf(" %s", ps[i].n);
                        else printf("%s", ps[i].n);
                        lj++;
                    }
                }
            } else {
                for (i=0; i<p; i++) {
                    for (j=0; j<p; j++) {
                        if (i==j) continue;
                        if (ps[i].mv[ni]<ps[j].lv[ni]) break;
                    }
                    if (j==p) {
                        if (lj>0) printf(" %s", ps[i].n);
                        else printf("%s", ps[i].n);
                        lj++;
                    }
                }
            }
            printf("\n");
        }
    }
    return 0;
}


