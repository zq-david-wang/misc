#include<stdio.h>


char buf[204800];
int readline() {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        buf[i++] = c;
    }
    buf[i]=0;
    return i;
}
int main() {
    int n, i, l, r, mc, c;
    char act;
    while(1) {
        readline();
        sscanf(buf, "%d", &n);
        if (n==0) break;
        l = readline();
        r=0; i=0; mc=0;
        while(1) {
            while(buf[i]==' ')i++;
            if (buf[i]==0) break;
            act = buf[i++]; c=0; while(buf[i]>='0'&&buf[i]<='9') { c=c*10+buf[i]-'0'; i++; }
            if (act=='m') {c%=2; mc+=c;if (c) r=n-r;}
            else { r+=c; r%=n;}
        }
        // if (r<0) r += ((-r)/n+1)*n;
        r %= n; mc %=2;
        if (r) {
            if (mc) {
                if (r<n-r) printf("m1 r%d\n", r);
                else printf("r%d m1\n", n-r);
            } else {
                if (r>(n-r)+2) printf("m1 r%d m1\n", n-r);
                else printf("r%d\n", r);
            }
        } else printf("\n");
    }
    return 0;
}
