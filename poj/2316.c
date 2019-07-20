#include<stdio.h>

int main() {
    int i, l;
    char bs[16], ns[16];
    scanf("%s", bs);
    i=0; while(1) {
        if ((bs[i])==0) break;
        bs[i] -= '0'; i++;
    } l=i;
    while(scanf("%s", ns)==1) {
        for (i=0; i<l; i++) {
            bs[i] += (ns[i]-'0');
            bs[i] %= 10;
        }
    }
    for (i=0; i<l; i++) bs[i]+='0';
    printf("%s\n", bs);
    return 0;
}
