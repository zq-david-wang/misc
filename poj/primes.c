#include<stdio.h>
#include<string.h>

char map[1100];

int main() {
    memset(map, 0, sizeof(map));
    int i,j; for (i=2; i<sizeof(map); i++) {
        if (map[i]==1) continue;
        printf("%d\n", i);
        for (j=i+i; j<sizeof(map); j+=i) map[j]=1;
    }
    return 0;
}
