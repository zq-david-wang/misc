#include<stdio.h>

char *names[] = {
    "Bill",
    "Steve",
    "Linus"
};

int ts[32];
int main() {
    int n, i, t, j, c, k, tt;
    int s[3], p[3], ct;
    scanf("%d", &n);
    for (i=1; i<=n; i++) {
        scanf("%d %d", &t, &c);
        for (j=0; j<c; j++)scanf("%d", &ts[j]);
        ct = 0;
        s[0] = 0; p[0] = 0; for (j=0; j<c; j++) {
            if (ct+ts[j] > t)break;
            s[0] += (ct+ts[j]); p[0]++;
            ct += ts[j];
        } 
        for (j=1; j<c; j++) {
            tt = ts[j];
            for (k=j-1; k>=0; k--) {
                if (ts[k]<=tt) break;
                ts[k+1] = ts[k];
            }
            ts[k+1] = tt;
        }
        ct = 0;
        s[1] = 0; p[1] = 0; for (j=0; j<c; j++) {
            if (ct+ts[j] > t)break;
            s[1] += (ct+ts[j]); p[1]++;
            ct += ts[j];
        } 
        ct = 0;
        s[2] = 0; p[2] = 0; for (j=c-1; j>=0; j--) {
            if (ct+ts[j] > t)break;
            s[2] += (ct+ts[j]); p[2]++;
            ct += ts[j];
        } 
        tt = 1;
        if (p[0]>p[tt] || (p[0]==p[tt]&&s[0]<s[tt])) tt = 0;
        if (p[2]>p[tt] || (p[2]==p[tt]&&s[2]<s[tt])) tt = 2;
        printf("Scenario #%d:\n", i);
        printf("%s wins with %d solved problems and a score of %d.\n", names[tt], p[tt], s[tt]);
        printf("\n");
    }
    return 0;
}
