#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main() {
    int i, j, k, map[4][4];
    char b[16], c1, c2, c3;
    while(1) {
        scanf("%s", b); if (b[0]=='E') break;
        for (i=0; i<4; i++) for (j=0; j<4; j++) scanf("%d", &map[i][j]);
        scanf("%s", b);
        while(1) {
            c3=0;
            for (i=0; i<9; i++) {
                j=i/3; k=i%3;
                c1=0; c2=0;
                if (map[j][k]==0) c1++;
                else if (map[j][k]==(i+1)) c2++;
                else continue;
                if (map[j+1][k]==0) c1++;
                else if (map[j+1][k]==(i+1)) c2++;
                else continue;
                if (map[j][k+1]==0) c1++;
                else if (map[j][k+1]==(i+1)) c2++;
                else continue;
                if (map[j+1][k+1]==0) c1++;
                else if (map[j+1][k+1]==(i+1)) c2++;
                else continue;
                if (c2==0) continue;
                map[j][k]=map[j+1][k]=map[j][k+1]=map[j+1][k+1]=0;
                c3++;
            }
            if (c3==0) break;
        }
        c3=0; for (i=0; i<4; i++) for (j=0; j<4; j++) if (map[i][j]) c3++;
        if (c3) printf("THESE WINDOWS ARE BROKEN\n");
        else printf("THESE WINDOWS ARE CLEAN\n");
    }
    return 0;
}


