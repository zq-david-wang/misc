#include<stdio.h>
int gn, gb, gh;
int hs[32];
void dfs(int s, int h) {
    if (h>=gb) {
        if (gh<0 || gh>h) gh = h;
        return;
    }
    int i; for (i=s; i<gn; i++) {
        dfs(i+1, h+hs[i]);
    }
}
int main() {
    int n, b, i;
    scanf("%d %d", &n, &b);
    for (i=0; i<n; i++) scanf("%d", &hs[i]);
    gn = n; gb = b;
    gh = -1;
    dfs(0, 0);
    printf("%d\n", gh-gb);
    return 0;
}
