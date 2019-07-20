#include<stdio.h>

int covers[10001];
int fc[10001], fis[10001][2];
int main() {
    int n, i, h, r, j, k;
    int a, b;
    scanf("%d %d %d %d", &n, &i, &h, &r);
    for(j=1; j<=n; j++) {
        covers[j] = 0;
        fc[j] = 0;
    }
    for (j=0; j<r; j++) {
        scanf("%d %d", &a, &b);
        for (k=0; k<fc[a]; k++) if (fis[a][k]==b) break;
        if (k<fc[a]) continue;
        for (k=0; k<fc[b]; k++) if (fis[b][k]==a) break;
        if (k<fc[b]) continue;
        fis[a][fc[a]++] = b;
        if (a<b) for (k=a+1; k<b; k++) covers[k]++;
        else for (k=b+1; k<a; k++) covers[k]++;
    } 
    for (j=1; j<=n; j++) printf("%d\n", h-covers[j]);
    return 0;
}
