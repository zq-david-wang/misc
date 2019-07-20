#include<stdio.h>
#include<string.h>

char map[1001][1001];
unsigned int queue[1000000];

int main() {
    int x, y, n, i;
    int a, b;
    unsigned int v;
    scanf("%d %d %d", &x, &y, &n);
    x += 500; y += 500;
    memset(map, 0, sizeof(map));
    for (i=0; i<n; i++) {
        scanf("%d %d", &a, &b);
        a += 500; b += 500;
        map[a][b] = 1;
    }
    int qhead=0, qtail = 0, d;
    queue[qhead++] = (500<<10) | 500;
    map[500][500] = 1;
    while(qtail<qhead) {
        v = queue[qtail++];
        a = (v>>10)&0x3ff; b = v&0x3ff;  d = v>>20;
        if (a==x && b==y) break;
        d++;
        if (a>0 && map[a-1][b]==0) {
            map[a-1][b] = 1;
            queue[qhead++] = (d<<20)|((a-1)<<10)|b;
        }
        if (a<1000 && map[a+1][b]==0) {
            map[a+1][b] = 1;
            queue[qhead++] = (d<<20)|((a+1)<<10)|b;
        }
        if (b>0 && map[a][b-1]==0) {
            map[a][b-1] = 1;
            queue[qhead++] = (d<<20)|(a<<10) | (b-1);
        }
        if (b<1000 && map[a][b+1]==0) {
            map[a][b+1] = 1;
            queue[qhead++] = (d<<20)|(a<<10) | (b+1);
        }
    }
    printf("%d\n", d);
    return 0;
}
