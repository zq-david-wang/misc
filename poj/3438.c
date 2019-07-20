#include<stdio.h>

char buf[1024];
char obuf[2048];
int main() {
    int n, i, c, j;
    char *p;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%s", buf);
        p = obuf;
        c=1; j=1; while(1) {
            if (buf[j]==0) break;
            if (buf[j]==buf[j-1]) c++;
            else {
                p+=sprintf(p, "%d%d", c, buf[j-1]-'0');
                c=1;
            }
            j++;
        }
        if (c) sprintf(p, "%d%d", c, buf[j-1]-'0');
        printf("%s\n", obuf);
    }
    return 0;
}
