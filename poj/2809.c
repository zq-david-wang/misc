#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char exps[1024];
int poly[16];
int poly2[16];
void build() {
    int i; for (i=0; i<=10; i++) poly[i]=0;
    int j=0, k=0, v; 
    char sign;
    while(exps[j]) {
        k=j;
        while(exps[k]!='x'&&exps[k]!=0) k++;
        sign=0; if (exps[j]=='-') { sign=1; j++; } else if (exps[j]=='+') j++;
        if (j==k) v=1;
        else v=exps[j]-'0';
        if (sign) v=-v;
        if (exps[k]==0) { poly[0]=v; break; }
        else {
            if (exps[k+1]=='^') { poly[exps[k+2]-'0']=v; k+=3; }
            else { poly[1]=v; k++; }
        }
        j=k;
    }
}
int main() {
    int tc, ti, i, p, s, x, v, pp, j, ss;
    scanf("%d", &tc); for (ti=1; ti<=tc; ti++) {
        scanf("%d %s", &x, exps);
        build();
        printf("POLYNOMIAL %d\n", ti);
        printf("%s\n", exps);
        for (i=0; i<=10; i++) poly2[i]=0;
        s=0;
        for (i=10; i>0; i--) {
            if (poly[i]==0) continue;
            p = i*poly[i];
            if (p==0) continue;
            if (s&&p>0) printf("+%d", p);
            else printf("%d", p);
            s=1;
            if (i>2) printf("x^%d", i-1);
            else if (i>1) printf("x");
            poly2[i-1] = p;
        }
        if (s==0) printf("0");
        printf("\n");
        s=0; for (i=10; i>=0; i--) {
            if (poly2[i]==0) continue;
            if (s&&poly2[i]>0) printf("+%d", poly2[i]);
            else printf("%d", poly2[i]);
            if (i>1) printf("(%d)^%d", x, i);
            else if (i>0) printf("(%d)", x);
            s=1;
        }
        if (s==0) printf("0");
        printf("\n");
        s=0; ss=0; for (i=10; i>=0; i--) {
            if (poly2[i]==0) continue;
            pp=1; for (j=0; j<i; j++) pp*=x;
            v = poly2[i]*pp;
            if (s&&v>=0) printf("+%d", v);
            else printf("%d", v);
            s=1;
            ss += v;
        }
        if (s==0) printf("0");
        printf("\n%d\n", ss);
    }
    return 0;
}


