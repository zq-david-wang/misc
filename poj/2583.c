#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main() {
    int a, b, c;
    int v0, v1, v2;
    while(scanf("%d %d %d", &v0, &v1, &v2)==3) {
        c = v0;
        // a+b=v1-v0;
        // 4a+2b=v2-v0;
        a=((v2-v0)-(v1-v0)*2)/2;
        b = v1-v0-a;
        printf("%d %d %d\n", 9*a+3*b+c, 16*a+4*b+c, 25*a+5*b+c);
    }
    return 0;
}


