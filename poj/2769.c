#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int ns[300];
char map[1000000];
int main() {
    int tc, ti, i, n, m, j;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d", &n);
        for (i=0; i<n; i++) scanf("%d", &ns[i]);
        m=n; while(1) {
            memset(map, 0, m);
            for (i=0; i<n; i++) {
                j = ns[i]%m;
                if (map[j]) break;
                map[j]=1;
            }
            if (i==n) break;
            m++;
        }
        printf("%d\n", m);
    }
    return 0;
}


