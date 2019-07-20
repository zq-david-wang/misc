#include<stdio.h>
#include<string.h>

char map[50][50];
int dis[50][50][50];
int queue[50*50*50];
typedef struct _T{
    struct _T* n;
    int b;
}ENode;
ENode pool[50*50*2];
int pc;
ENode *nei[50][26];
int main() {
    int n, p1, p2, p3, i, j;
    char b[8], c;
    int head, tail;
    ENode *p;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        memset(nei, 0, sizeof(nei)); pc=0;
        scanf("%d %d %d", &p1, &p2, &p3);
        p1--; p2--; p3--;
        for (i=0; i<n; i++) for (j=0; j<n; j++) {
            scanf("%s", b); c = b[0]-'a';
            map[i][j] = c;
            p = &pool[pc++]; p->b=j; p->n=nei[i][c]; nei[i][c] = p;
            p = &pool[pc++]; p->b=i; p->n=nei[j][c]; nei[j][c] = p;
        }
        memset(dis, 0xff, sizeof(dis));
        head=tail=0;
        queue[head++] = (p1<<16)|(p2<<8)|p3;
        dis[p1][p2][p3] = 0; j=-1;
        while(tail<head) {
            i = queue[tail++];
            p1 = i>>16; p2 = (i>>8)&0xff; p3 = i&0xff;
            if (p1==p2 && p2==p3) { j=dis[p1][p2][p3]; break; }
            c = map[p2][p3]; p=nei[p1][c];
            while(p!=NULL) {
                i = p->b;
                if (dis[i][p2][p3]<0) {
                    dis[i][p2][p3] = 1+dis[p1][p2][p3];
                    queue[head++] = (i<<16)|(p2<<8)|p3;
                }
                p = p->n;
            }
            c = map[p1][p3]; p=nei[p2][c];
            while(p!= NULL) {
                i = p->b;
                if (dis[p1][i][p3]<0) {
                    dis[p1][i][p3] = 1+dis[p1][p2][p3];
                    queue[head++] = (p1<<16)|(i<<8)|p3;
                }
                p = p->n;
            }
            c = map[p1][p2]; p=nei[p3][c];
            while(p!= NULL) {
                i = p->b;
                if (dis[p1][p2][i]<0) {
                    dis[p1][p2][i] = 1+dis[p1][p2][p3];
                    queue[head++] = (p1<<16)|(p2<<8)|i;
                }
                p = p->n;
            }
        }
        if (j<0) printf("impossible\n");
        else printf("%d\n", j);
    }
    return 0;
}
