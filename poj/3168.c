#include<stdio.h>
#include<stdlib.h>

struct { int x1, y1, x2, y2; }farms[25000];
char flag[25000];
typedef struct{
    int x, y1, y2, i;
}CNode;
CNode nodes[50000];
int mycmp(const void *a, const void *b) {
    const CNode*pa = (const CNode*)a;
    const CNode*pb = (const CNode*)b;
    if (pa->x != pb->x) return pa->x-pb->x;
    return pa->y1-pb->y1;
}
int main() {
    int n, i, j, m;
    int li, ey;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        flag[i] = 0;
        scanf("%d %d %d %d", &farms[i].x1, &farms[i].y1, &farms[i].x2, &farms[i].y2);
    }
    for (i=0; i<n; i++) {
        j = i*2;
        nodes[j].x = farms[i].x1;
        nodes[j].y1 = farms[i].y1;
        nodes[j].y2 = farms[i].y2;
        nodes[j].i = i;
        j = i*2+1;
        nodes[j].x = farms[i].x2;
        nodes[j].y1 = farms[i].y1;
        nodes[j].y2 = farms[i].y2;
        nodes[j].i = i;
    }
    m = n*2;
    qsort(nodes, m, sizeof(nodes[0]), mycmp);
    li = nodes[0].i; ey = nodes[0].y2;
    for (i=1; i<m; i++) {
        if (nodes[i].x != nodes[i-1].x) {
            li = nodes[i].i;
            ey = nodes[i].y2;
        } else {
            if (nodes[i].y1<=ey) {
                flag[li] = 1;
                flag[nodes[i].i] = 1;
                if (ey<nodes[i].y2) ey = nodes[i].y2;
            } else {
                li = nodes[i].i;
                ey = nodes[i].y2;
            }
        }
    }
    for (i=0; i<n; i++) {
        j = i*2;
        nodes[j].x = farms[i].y1;
        nodes[j].y1 = farms[i].x1;
        nodes[j].y2 = farms[i].x2;
        nodes[j].i = i;
        j = i*2+1;
        nodes[j].x = farms[i].y2;
        nodes[j].y1 = farms[i].x1;
        nodes[j].y2 = farms[i].x2;
        nodes[j].i = i;
    }
    qsort(nodes, m, sizeof(nodes[0]), mycmp);
    li = nodes[0].i; ey = nodes[0].y2;
    for (i=1; i<m; i++) {
        if (nodes[i].x != nodes[i-1].x) {
            li = nodes[i].i;
            ey = nodes[i].y2;
        } else {
            if (nodes[i].y1<=ey) {
                flag[li] = 1;
                flag[nodes[i].i] = 1;
                if (ey<nodes[i].y2) ey = nodes[i].y2;
            } else {
                li = nodes[i].i;
                ey = nodes[i].y2;
            }
        }
    }
    j=0; for (i=0; i<n; i++) if (flag[i]==0) j++;
    printf("%d\n", j);
    return 0;
}
