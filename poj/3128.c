#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char bc[32];
char map[32], cs[32];
int main() {
    int tc, ti, i, c, a;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%s", bc);
        for (i=0; i<26; i++) bc[i]-='A';
        for (i=0; i<=26; i++) { map[i]=-1; cs[i]=0; }
        for (i=0; i<26; i++) {
            if (map[i]!=-1) continue;
            a = i; c=0;
            while(map[a]==-1) {
                map[a]=bc[a];
                a=bc[a];
                c++;
            } cs[c]++;
        }
        for (i=2; i<=26; i+=2) if (cs[i]&1) break;
        if (i>26) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}


