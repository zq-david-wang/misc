#include<stdio.h>

int main() {
    int m, t, u, f, d, i;
    char s[8];
    int ss=0;
    scanf("%d %d %d %d %d", &m, &t, &u, &f, &d);
    for (i=0; i<t; i++) {
        scanf("%s", s);
        if (s[0] == 'u' || s[0] == 'd') ss += (u+d);
        else ss += (f+f);
        if (ss > m) break;
    }
    printf("%d\n", i);
    return 0;
}
