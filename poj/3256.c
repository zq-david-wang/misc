#include<stdio.h>
#include<string.h>


int loc[100];
char map[1001][1001];
int nei[1001][1001];
int neic[1001];
int reach[1001];
char flag[1001];
int queue[1001];
int main() {
    int k, n, m, i, j;
    int a, b;
    int head, tail;
    scanf("%d %d %d", &k, &n, &m);
    for (i=0; i<k; i++) scanf("%d", &loc[i]);
    memset(map, 0, sizeof(map));
    for (i=1; i<=n; i++) neic[i] = 0;
    for (i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        if (map[a][b]) continue;
        map[a][b] = 1;
        nei[a][neic[a]++]=b;
    }
    for (i=0; i<k; i++) {
        for (j=1; j<=n; j++) flag[j]=0;
        head = tail = 0;
        queue[head++] = loc[i];
        flag[loc[i]] = 1;
        while(tail<head) {
            a = queue[tail++];
            reach[a]++;
            for (j=0; j<neic[a]; j++) {
                b = nei[a][j];
                if (flag[b]) continue;
                queue[head++] = b;
                flag[b] = 1;
            }
        }
    }
    int rc = 0;
    for (i=1; i<=n; i++) if (reach[i]==k) rc++;
    printf("%d\n", rc);
    return 0;
}
