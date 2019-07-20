#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int hand[4];
char cs[4];
int cc[4];
struct { char b, c; int m;} qs[16];
int gc, gn, gs;
int count1s(int m) {
    int c=0;
    while(m) {
        c++; m=m&(m-1);
    }
    return c;
}
void dfs(int s) {
    while(s<18) if ((1<<s)&hand[gs]) s++; else break; 
    int i, m;
    if (s==18) {
        for (i=0; i<gn; i++) {
            if (qs[i].b==gs) continue;
            m = qs[i].m&cc[qs[i].b];
            if (count1s(m)!=qs[i].c) break;
        }
        if (i==gn) {
            if (cc[3]!=hand[3]) gc=2;
            else gc=1;
        }
        return;
    }
    for (i=0; i<3; i++) {
        if (cs[i]<5) {
            m=cc[i]; cc[i]|=(1<<s); cs[i]++;
            dfs(s+1);
            cs[i]--; cc[i]=m;
        } if (gc>1) return;
    }
    if (cs[3]<3) {
        m=cc[3]; cc[3]|=(1<<s); cs[3]++;
        dfs(s+1);
        cs[3]--; cc[3]=m;
    }
}
int verify(int s, int n) {
    gc=0; gs=s; gn=n;
    int i; for (i=0; i<4; i++) cs[i]=0;
    cs[s]=5;
    dfs(0);
    return gc==1;
}
int main() {
    int t, i, j, b, c, k, m;
    char s[8];
    while(1) {
        scanf("%d", &t); if(t==0) break;
        for (i=0; i<4; i++) {
            scanf("%s", s);
            m=0; j=0; while(s[j]) {
                m |= (1<<(s[j]-'A')); j++;
            } hand[i]=m;
        }
        for (i=0; i<t; i++) {
            scanf("%d %s %d", &b, s, &c); b--;
            m=0; for (j=0; j<3; j++) m |= (1<<(s[j]-'A'));
            qs[i].b=b; qs[i].c=c; qs[i].m=m;
        }
        for (i=0; i<t; i++) {
            b = qs[i].b;
            for (j=0; j<3; j++) { if (j==b) continue;
                if (verify(j, i+1)) break;
            }
            if (j<3) break;
        }
        if (i<t) printf("%d\n", i+1);
        else printf("?\n");
    }
    return 0;
}


