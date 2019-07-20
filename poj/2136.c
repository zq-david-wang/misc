#include<stdio.h>

int cs[26];
char buf[128];
int main() {
    int i, c, j;
    for (i=0; i<26; i++) cs[i] = 0;
    while(scanf("%s", buf)!=EOF) {
        i=0; while(buf[i]!=0) {
            c = buf[i];
            if (c>='A'&&c<='Z') {
                c -= 'A';
                cs[c]++;
            }
            i++;
        }
    }
    c = cs[0]; for (i=1; i<26; i++) if (c<cs[i]) c=cs[i];
    for (i=c; i>0; i--) {
        for (j=0; j<26; j++) {
            if (cs[j]>=i) {
                if (j>0) printf(" *");
                else printf("*");
            } else {
                if (j>0) printf("  ");
                else printf(" ");
            }
        }
        printf("\n");
    }
    printf("A"); for (i=1; i<26; i++) printf(" %c", i+'A'); printf("\n");
    return 0;
}
