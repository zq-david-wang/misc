#include<stdio.h>

int map[1000][1000];
int main() {
    int n, i, j, valid, s1, s2;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        for (i=0; i<n; i++) for (j=0; j<n; j++) scanf("%d", &map[i][j]);
        valid=1;
        for (i=0; i<n-1; i++) {
            for (j=0; j<n-1; j++) {
                s1 = map[i][j]+map[i+1][j+1];
                s2 = map[i+1][j]+map[i][j+1];
                if (s1!=s2) { valid=0; break; }
            }
            if (valid==0) break;
        }
        if (valid) printf("homogeneous\n");
        else printf("not homogeneous\n");
    }
    return 0;
}
