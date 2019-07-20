#include<stdio.h>

char buf[2048];
int main() {
    int i, c, lc, ci=0;
    while(1) {
        scanf("%s", buf);
        if (buf[0]=='-') break;
        ci++;
        lc=0; c=0; i=0; while(1) {
            if (buf[i]==0) break;
            if (buf[i]=='{') lc++;
            else {
                if (lc==0) { c++; lc++; }
                else lc--;
            }
            i++;
        }
        c += (lc/2);
        printf("%d. %d\n", ci, c);
    }
    return 0;
}
