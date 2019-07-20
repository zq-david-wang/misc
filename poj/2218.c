#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char names[32][32];
struct {short w, i;} players[32];
int main() {
    int i, w, d, j, ci=0;
    char b[16];
    while(scanf("%s", b)==1) {
        ci++;
        i=0; while(1) {
            scanf("%s", names[i]); if (strcmp("END", names[i])==0) break;
            scanf("%d %d", &d, &w); w-=d;
            for (j=i-1; j>=0; j--) {
                if (players[j].w>=w) break;
                players[j+1]=players[j];
            }
            players[j+1].w=w; players[j+1].i=i;
            i++;
        }
        if (ci>1) printf("\n");
        for (j=0; j<i; j++) printf("%s\n", names[players[j].i]);

    }
    return 0;
}


