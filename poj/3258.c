#include<stdio.h>
#include<stdlib.h>

int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}
int loc[50000];
int main() {
    int l, n, m, i, c, last;
    scanf("%d %d %d", &l, &n, &m);
    for (i=0; i<n; i++) scanf("%d", &loc[i]);
    qsort(loc, n, sizeof(loc[0]), mycmp);
    int low=0, high=l, mid, lastfit=0;
    while(low<=high) {
        mid = (low+high)/2;
        c = 0; last = 0;
        for (i=0; i<n; i++) {
            if (loc[i]-last<mid) {
                c++; if (c>m) break;
            } else last = loc[i];
        }
        if (c<=m && l-last<mid) c++;
        if (c>m) {
            high = mid-1;
            lastfit = 0;
        } else {
            low = mid+1;
            lastfit = 1;
        }
    }
    if (lastfit==0) mid--;
    printf("%d\n", mid);
    return 0;
}
