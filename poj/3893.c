#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char cmd[8192];
int vs[10004];
char flag[10004];
int main() {
    int i1, i2, i, l, j;
    char c;
    memset(flag, 0, sizeof(flag));
    for (i=0; i<=3; i++) { flag[i]=1; vs[i]=i; }
    while(scanf("%d %s %d", &i1, cmd, &i2)==3) {
        l = strlen(cmd);
        if (flag[i2]==0) printf("something wrong\n");
        // printf("i1 is %d, i2 is %d\n", i1, i2);
        j = vs[i2];
        for (i=l-1; i>=0; i--) {
            c = cmd[i];
            if (c=='f') {
                if (j&1) j++;
                else j+=3;
                if (flag[j]==0) { flag[j]=1; vs[j]=-1;  }
            } else if (c=='b') {
                j -= 2;
                if (flag[j]==0) { flag[j]=1; vs[j]=-1;  }
            } else if (c=='k') {
                printf("%d\n", j);
            } else if (c=='<') {
                vs[i1]=j;
            } else {
                if (flag[i1] && vs[i1]==j) printf("=\n");
                else printf("#\n");
            }

        }
    }
    return 0;
}


