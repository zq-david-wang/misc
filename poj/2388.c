#include<stdio.h>
#include<stdlib.h>

int rank(int *a, int n, int r) {
    if (n==1) return a[0];
    int p = rand()%n;
    int t, i, j, k;
    p = a[p];
    j = -1; k = n;
    for (i=0; i<k;) {
        if (a[i]<p) {
            j++;
            if (i!=j) {
                t = a[i]; a[i] = a[j]; a[j] = t;
            }
        }
        if (a[i]>p) {
            k--;
            if (i != k) {
                t = a[i]; a[i] = a[k]; a[k] = t;
            }
        } else i++;
    }
    // 0-j j-0+1 smaller, k-n-1, n-k bigger
    if (r<=j+1) return rank(a, j+1, r);
    if (r>k) return rank(a+k, n-k, r-k);
    return p;
}
int cows[10000];
int main() {
    int n, i;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d", &cows[i]);
    srand(cows[0]);
    i = rank(cows, n, n/2+1);
    printf("%d\n", i);
    return 0;
}
