#include<stdio.h>
#include<string.h>

char dict[1000][88];
char buf[32];
int ls[1000];
short nei[1000][1000];
short neic[1000];
short queue[1024];
char flag[1024];
int main() {
    int d, i, j, k, m, si;
    scanf("%d %s", &d, buf);
    for (i=0; i<d; i++) {
        scanf("%s", dict[i]);
        ls[i] = strlen(dict[i]);
        neic[i] = 0;
        if (ls[i]==3 && strcmp(buf, dict[i])==0) si = i;
    }
    for (i=0; i<d; i++) {
        for (j=0; j<d; j++) {
            if (ls[j]!=ls[i]+1) continue;
            m = 0;
            for (k=0; k<ls[i]; k++) {
                if (dict[j][k] != dict[i][k]) break;
            }
            if (k==ls[i]) m=1;
            else {
                for (;k<ls[i]; k++) if (dict[j][k+1] != dict[i][k]) break;
                if (k==ls[i]) m=1;
            }
            if (m) nei[i][neic[i]++] = j;
        }
    }
    int head=0, tail=0;
    for (i=0; i<d; i++) flag[i] = 0;
    queue[head++] = si;
    flag[si] = 1;
    while(tail<head) {
        i = queue[tail++];
        for (j=0; j<neic[i]; j++) {
            k = nei[i][j];
            if (flag[k]==0) { 
                flag[k] = 1;
                queue[head++] = k;
            }
        }
    }
    i = queue[head-1];
    printf("%s\n", dict[i]);
    return 0;
}
