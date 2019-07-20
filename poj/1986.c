#include<stdio.h>

typedef struct { unsigned short l, i; }Nei;
typedef struct { Nei nei[6]; int neic; }NNode;
NNode map[40001];
int flag[40001];
int parent[40001];
int base[40001];

int dis[40001];

int ans[10000];
typedef struct _T{
    struct _T* n;
    unsigned short i, b;
}QNode;
QNode *query[40001];
QNode gpool[30000];
int gpc = 0;
QNode *alloc() {
    QNode* r = &gpool[gpc++];
    r->n = NULL;
    return r;
}
int stack[40001];
char *dir = "NESW";
void compact(int a) {
    int p = parent[a];
    int pp;
    while(1) {
        if (p==0 || flag[p] != 2) break;
        base[a] += base[p];
        p = parent[p];
    }
    parent[a] = p;
}
int main() {
    int n, m, i, k;
    int a, b, l;
    char c, d;
    int ni, pa;
    QNode *p;
    scanf("%d %d", &n, &m);
    for (i=1; i<=n; i++) {
        map[i].neic = 0;
        flag[i] = 0;
        parent[i] = 0;
        query[i] = NULL;
        base[i] = 0;
    }
    for (i=0; i<m; i++) {
        scanf("%d %d %d %c", &a, &b, &l, &c);
        map[a].nei[map[a].neic].l = l;
        map[a].nei[map[a].neic++].i = b;
        map[b].nei[map[b].neic].l = l;
        map[b].nei[map[b].neic++].i = a;
    }
    scanf("%d", &k);
    for (i=0; i<k; i++) {
        scanf("%d %d", &a, &b);
        if (a==b) {ans[i]=0; continue;}
        p = alloc(); p->b = b; p->i = i;
        p->n = query[a]; query[a] = p;
        p = alloc(); p->b = a; p->i = i;
        p->n = query[b]; query[b] = p;
    }

    int stop=0;
    stack[stop++] = 1;
    dis[1] = 0;
    flag[1] = 1; //1-->under 2-->done 0
    while(stop) {
        a = stack[stop-1];
        for (d=0; d<map[a].neic; d++) {
            ni = map[a].nei[d].i;
            if (flag[ni]!=0) continue; 
            flag[ni] = 1;
            dis[ni] = dis[a]+map[a].nei[d].l;
            base[ni] = map[a].nei[d].l;
            parent[ni] = a;
            p = query[ni];
            while(p!=NULL) {
                if (flag[p->b] == 1) {
                    ans[p->i] = dis[ni]-dis[p->b];
                } else if (flag[p->b] == 2) {
                    compact(p->b);
                    ans[p->i] = base[p->b] + dis[ni]- dis[parent[p->b]];
                }
                p = p->n;
            }
            stack[stop++] = ni;
            break;
        }
        if (d==map[a].neic) {
            flag[a] = 2;
            stop--;
        }
    }
    for (i=0; i<k; i++) printf("%d\n", ans[i]);
    return 0;
}
