#include<stdio.h>

char buf[128];
int main() {
    int n, i, s=1;
    scanf("%d", &n);
    i = 0; buf[127]=0;
    if (n<0) { n=-n; s=0; }
    while(n!=0) {
       if (n&1) {
           buf[127-i-1] = '1';
           if ((i&1)==s) n++;
       }  else {
           buf[127-i-1] = '0';
       }
       i++;
       n>>=1;
    }
    if (i==0) {buf[126] = '0'; i++; }
    printf("%s", &buf[127-i]);
    return 0;
}
