#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char map[128][128];
char p1[128], p2[128];
int main() {
    int c1, c2;
    int i;
    map['R']['P']=0; map['P']['R']=1;
    map['R']['S']=1; map['S']['R']=0;
    map['P']['S']=0; map['S']['P']=1;
    map['P']['P']=0; map['S']['S']=0; map['R']['R']=0;
    while(1) {
        scanf("%s %s", p1, p2); if (p1[0]=='E') break;
        c1=c2=0;
        i=0; while(1) {
            if (p1[i]==0) break;
            c1 += map[p1[i]][p2[i]];
            c2 += map[p2[i]][p1[i]];
            i++;
        }
        printf("P1: %d\n", c1);
        printf("P2: %d\n", c2);
    }
    return 0;
}


