#include<stdio.h>

int vs[100000];
int main() {
    int n, m, i, c;
    long long s = 0;
    long long l=0, mv, h;
    scanf("%d %d", &n, &m);
    for (i=0; i<n; i++) {
        scanf("%d", &vs[i]);
        s += vs[i];
        if (l<vs[i]) l = vs[i];
    }
    h = s;
    while(l<=h) {
        mv = (l+h)/2;
        c = 0; s=0;
        for (i=0; i<n; i++) {
            if ((s+vs[i]) > mv) {
                c++; s = 0;
            }
            s += vs[i];
        }
        c++;
        if (c<=m) { if (h==mv) break; h = mv; }
        else l = mv+1;
    }
    printf("%lld\n", h);
    return 0;
}
