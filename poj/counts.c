#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int cs[100000];
int main() {
    int i;
    char act[8];
    memset(cs, 0, sizeof(cs));
    while(1) {
        scanf("%s", act); if (act[0]=='E') break;
        scanf("%d", &i);
        if (act[0]=='I') {
            cs[i]++;
        } else if (act[0]=='Q') {
            printf("%d:%d\n", i, cs[i]);
        } else if (act[0]=='D') {
            if (cs[i]) cs[i]--;
        }
    }
    return 0;
}


