#include<stdio.h>
#include<string.h>

char buf[128];
int main() {
    int l, i, s=0;
    while(1) {
        if (scanf("%s", buf)!=1) break;
        l = strlen(buf);
        if (strcmp(buf, "<br>")==0) { printf("\n"); s=0; }
        else if (strcmp(buf, "<hr>")==0) {
            if (s) printf("\n");
            for (i=0; i<80; i++) printf("-");printf("\n"); s=0;
        } else {
            if (s+1+l>80) { printf("\n%s", buf); s=l; }
            else { if (s) { printf(" "); s++; }  printf("%s", buf); s+=l; }
        }
    }
    if (s) printf("\n");
    return 0;
}
