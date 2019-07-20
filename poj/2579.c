#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char map[16][16];
char omap[16][16];
int main() {
    char m[16];
    int r, c, i, j;
    while(1) {
        scanf("%s", m);
        if (m[0]=='E') break;
        scanf("%d %d", &r, &c);
        for (i=0; i<r; i++) scanf("%s", map[i]);
        scanf("%s", m);
        for (i=0; i<r-1; i++) {
            for (j=0; j<c-1; j++) {
                omap[i][j] = (map[i][j]-'0'+map[i+1][j]-'0'+map[i][j+1]-'0'+map[i+1][j+1]-'0')/4+'0';
            }
            omap[i][j]=0;
            printf("%s\n", omap[i]);
        }
    }
    return 0;
}


