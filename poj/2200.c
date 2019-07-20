#include<stdio.h>

char name[5][4];
char mark[128], sv[128];
typedef struct {
    char n, s, r, i;
}CNode;
CNode card[5];
int main() {
    int c, i, j, k;
    int fi, si, li, nli, find, t, ci, ri, mr;
    CNode tc;
    mark['A']=0; for (i='2'; i<='9';i++) mark[i]=i-'1';
    mark['1']=9; mark['J']=10; mark['Q']=11; mark['K']=12;
    sv['C']=0; sv['D']=1; sv['H']=2; sv['S']=3;
    scanf("%d", &c);
    for (i=1; i<=c; i++) {
        for (j=0; j<5; j++) { 
            scanf("%s", name[j]);
            if (name[j][2]==0) card[j].s=name[j][1];
            else card[j].s=name[j][2];
            card[j].n = mark[name[j][0]];
            card[j].r = card[j].n*4+sv[card[j].s];
            card[j].i = j;
        }
        // sort card
        for (j=1; j<5; j++) {
            tc = card[j];
            for (k=j-1; k>=0; k--) {
                if (card[k].r <= tc.r) break;
                card[k+1]=card[k];
            }
            card[k+1] = tc;
        }
        // try
        find=0;
        for (j=0; j<5; j++) {
            for (fi=0; fi<5; fi++) {
                if (fi==j) continue;
                if (card[fi].s != card[j].s) continue;
                for (si=0; si<5; si++) {
                    if (si==j||si==fi) continue;
                    for (li=0; li<5; li++) {
                        if (li==j||li==fi||li==si) continue;
                        for (nli=0; nli<5; nli++) {
                            if (nli==j||nli==fi||nli==si||nli==li) continue;
                            ri = 1; mr=card[si].r; if (mr>card[li].r) {mr=card[li].r; ri=2; }
                            if (mr>card[nli].r) { mr=card[nli].r; ri=3; }
                            if (ri==1 && card[li].r>card[nli].r) ri+=3;
                            else if (ri==2 && card[si].r>card[nli].r) ri+=3;
                            else if (ri==3 && card[si].r>card[li].r) ri+=3;
                            if (((card[fi].n+ri)%13)==card[j].n) { find=1; break; }
                        }
                        if (find) break;
                    }
                    if (find) break;
                }
                if (find) break;
            }
            if (find) break;
        }
        printf("Problem %d: %s %s %s %s %s\n", i, name[card[j].i],
                name[card[fi].i], name[card[si].i], name[card[li].i], name[card[nli].i]);
    }
    return 0;
}
