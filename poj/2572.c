#include<stdio.h>

int main() {
    int a, b, c, i, cc, s, j;
    char b1[12], b2[12], b3[12];
    char bb[32];
    while(scanf("%s", bb)==1) {
        i=0; j=0; while(bb[i]!='+') { b1[j++]=bb[i]; i++; } for (;j<7; j++)b1[j]='0';
        i++; j=0; while(bb[i]!='=') { b2[j++]=bb[i]; i++; } for (;j<7; j++)b2[j]='0';
        i++; j=0; while(bb[i]!=0) { b3[j++]=bb[i]; i++; }
        c = 0; for (j--; j>=0; j--) c=c*10+b3[j]-'0';
        cc = 0;
        for (i=0; i<7; i++) {
            s = b1[i]-'0'+b2[i]-'0'+cc;
            cc = s/10; b3[i]=s%10;
        }
        cc = 0; for (i=6; i>=0; i--) {
            cc = cc*10+b3[i];
        }
        if (cc==c) printf("True\n");
        else printf("False\n");
    }
    return 0;
}
