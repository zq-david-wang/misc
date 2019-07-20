#include<stdio.h>
#include<string.h>

short queue[1004];
short path[1004];
char flag[1004];
char map[1004][1004];

int main() {
    int n, k, i, j;
    int a, b;
    int h, t;
    memset(map, 0, sizeof(map));
    scanf("%d %d", &n, &k);
    for (i=0; i<=k; i++) {
        memset(map[i], 0, (k+1)*sizeof(map[0][0]));
        flag[i] = 0;
        path[i] = -1;
    }
    for (i=0; i<n; i++) {
        scanf("%d %d", &a, &b);
        map[a][b] = 1;
    } 
    h = t = 0;
    flag[1] = 1;
    queue[h++] = 1;
    path[1] = 1;
    while(t<h) {
        i = queue[t++];
        if (i==k) break;
        for (j=1; j<=k; j++) {
            if (map[i][j]==0 || flag[j]==1) continue;
            flag[j] = 1;
            queue[h++] = j;
            path[j] = i;
        }
    }
    if (path[k]<0) printf("-1\n");
    else {
        i = 0; h = k;
        while(h!= 1) {
            queue[i++] = h;
            h = path[h];
        }
        queue[i++] = 1;
        printf("%d\n", i);
        for (i--; i>=0; i--) printf("%d\n", queue[i]);
    }
    return 0;
}
