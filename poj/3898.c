#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char pn[1024];
char ts[10004];
char score[10004];
int dp1[1004], dp2[1004];
int main() {
    int m, n, i, t, r=-1, t2, j;
    int *p1, *p2, *tp;
    char *p;
    int mc, sc;
    while(scanf("%s %s", pn, ts)==2) {
        m = strlen(pn); n = strlen(ts);
        for (i=0; i<n; i++) score[i]=ts[i]-'a'+1;
        // compress pn
        i=0; j=0; p=pn;
        mc=0; sc=0;
        while(1) {
            if (j==m) {
                if (mc) {
                    while(mc) { p[i++]='?'; mc--; }
                }
                break;
            }
            if (p[j]=='?') mc++;
            else if (p[j]=='*') sc++;
            else {
                if (mc) {
                    while(mc) { p[i++]='?'; mc--; }
                    if (sc) p[i++]='*';
                } else if (sc) {
                    p[i++]='*';
                }
                mc=0; sc=0;
                p[i++] = p[j];
            }
            j++;
        } m=i; p[m]=0;
        r=-1;
        p1=dp1; p2=dp2;
        p1[m]=0;
        for (i=m-1;i>=0; i--) p1[i]=-1;
        for (j=n-1; j>=0; j--) {
            p2[m] = 0;
            for (i=m-1; i>=0; i--) {
                p2[i]=-1;
                if (p[i]=='?'||p[i]==ts[j]) {
                    if (p1[i+1]>=0) p2[i]=p1[i+1]+score[j];
                } else if (p[i]=='*') {
                    t = p2[i+1];
                    t2 = p1[i]; if (t2>=0) {
                        t2+=score[j];
                        if (t<0||t>t2) t=t2;
                    }
                    p2[i]=t;
                }
            }
            tp=p1; p1=p2; p2=tp;
            if (p1[0]<0) continue;
            if (r<0||r>p1[0]) r=p1[0];
        }
        printf("%d\n", r);
    }
    return 0;
}


