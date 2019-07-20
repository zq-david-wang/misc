#include<stdio.h>

int hp[20000];

void heapify(int s, int n) {
    int ns, ms = s;
    ns = s*2+1;
    if (ns>=n) return;
    if (hp[ms] > hp[ns]) ms = ns;
    ns = s*2+2;
    if (ns<n && hp[ns] < hp[ms])ms = ns;
    if (ms==s) return;
    int t = hp[ms];
    hp[ms] = hp[s]; hp[s] = t; heapify(ms, n);
}
int main() {
    int n, i, v;
    long long s=0;
    scanf("%d", &n);
    for (i=0; i<n; i++) scanf("%d", &hp[i]);
    for (i=n/2; i>=0; i--)heapify(i, n);
    while(n>1) {
        v = hp[0];
        n--;
        hp[0] = hp[n]; heapify(0, n);
        s += (v+hp[0]);
        hp[0] += v;
        heapify(0, n);
    }
    printf("%lld\n", s);
    return 0;
}
