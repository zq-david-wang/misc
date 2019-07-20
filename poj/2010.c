#include<stdio.h>
#include<stdlib.h>

void heapify(int *h, int i, int n) {
    int mi=i, ni;
    ni = i*2+1;
    if (ni>=n) return;
    if (h[ni]>h[mi]) mi = ni;
    ni = i*2+2;
    if (ni<n && h[ni]>h[mi])mi = ni;
    if (mi != i) {
        ni = h[mi]; h[mi] = h[i]; h[i] =ni;
        heapify(h, mi, n);
    }
}
int h1[100000], h2[100000];
typedef struct { int s, f; }SNode;
SNode std[100000];
long long ls[100000], rs[100000];
int mycmp(const void *a, const void *b) {
    return ((const SNode*)a)->s - ((const SNode*)b)->s;
}
int main() {
    int n, c, f, m;
    int i, j;
    long long s;
    scanf("%d %d %d", &n, &c, &f);
    for (i=0; i<c; i++) scanf("%d %d", &std[i].s, &std[i].f);
    qsort(std, c, sizeof(std[0]), mycmp);
    m = n/2;
    s = 0;
    for (i=0; i<m; i++) {
        h1[i] = std[i].f;
        s += h1[i];
    }
    ls[i] = s;
    for (i=m/2+1; i>=0; i--)heapify(h1, i, m);
    for (i=m; i+m<c; i++) {
        if (h1[0]<std[i].f) {
            ls[i+1] = ls[i];
        } else {
            ls[i+1] = ls[i]+std[i].f-h1[0];
            h1[0] = std[i].f;
            heapify(h1, 0, m);
        }
    }
    s = 0;
    for (i=0; i<m; i++) {
        h2[i] = std[c-i-1].f;
        s += h2[i];
    }
    rs[c-i-1] = s;
    for (i=m/2+1; i>=0; i--) heapify(h2, i, m);
    for (i=c-m-1; i>=m; i--) {
        if (h2[0]<std[i].f) {
            rs[i-1] = rs[i];
        } else {
            rs[i-1] = rs[i]+std[i].f-h2[0];
            h2[0] = std[i].f;
            heapify(h2, 0, m);
        }
    }
    for (i=c-m-1; i>=m; i--) {
        if (ls[i] + rs[i] + std[i].f <= f) break;
    }
    if (i>=m)printf("%d\n", std[i].s);
    else printf("-1\n");
    return 0;
}
