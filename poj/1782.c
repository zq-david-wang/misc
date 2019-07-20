#include<stdio.h>

char buf[2048];
int readline() {
    int i=0;
    char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        buf[i++] = c;
    }
    buf[i]=0;
    if (c==EOF) return -1;
    return i;
}
int main() {
    int i, n, c, si;
    while(1) {
        n = readline();
        if (n<0) break;
        if (n) {
            si = 0; c=1; for (i=1; i<n; i++) {
                if (buf[i]!=buf[i-1]) {
                    if (c>1) {
                        printf("%d%c", c, buf[i-1]);
                        c=1; si=i;
                    }
                } else {
                    if (c==1 && si!=i-1) {
                        printf("1"); for (; si<i-1; si++) {
                            if (buf[si]=='1') printf("11");
                            else printf("%c", buf[si]);
                        }
                        printf("1");
                    }
                    if (c==9) { printf("9%c", buf[i]); c=0; si=i;}
                    c++;
                }
            }
            if (c==1){
                printf("1"); for (; si<n; si++) {
                    if (buf[si]=='1') printf("11");
                    else printf("%c", buf[si]);
                } printf("1");
            } else {
                printf("%d%c", c, buf[i-1]);
            }
        }
        printf("\n");
    }
    return 0;
}
