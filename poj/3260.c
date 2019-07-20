#include<stdio.h>

struct {int v, c;} ncs[10000];
int dp1[40000], dp2[40000];
int vs[100];
int cs[100];
#define INF 0xfffffff

int main() {
    int n, t, i, j;
    scanf("%d %d", &n, &t);
    for (i=0; i<n; i++) scanf("%d", &vs[i]);
    for (i=0; i<n; i++) scanf("%d", &cs[i]);
    int mv = vs[0]; for (i=1; i<n; i++) if (mv<vs[i]) mv = vs[i];
    int mc = t + mv*mv*2;
    int cn = 0;
    int v, s;
    for (i=0; i<n; i++) {
        if (cs[i]==0) continue;
        v = 1; s = 0;
        while(s<cs[i]) {
            v = s+1;
            if (s+v>cs[i]) break;
            ncs[cn].v = vs[i]*v;
            ncs[cn].c = v;
            cn++;
            s += v;
        }
        if (s!=cs[i]) {
            ncs[cn].v = vs[i]*(cs[i]-s);
            ncs[cn].c = cs[i]-s;
            cn++;
        }
    }
    // for (i=0; i<cn; i++) printf("%d: %d,%d\n", i, ncs[i].c, ncs[i].v);
    // printf("mc is %d, cn is %d\n", mc, cn);
    for (i=1; i<=mc; i++) dp1[i] = INF;
    dp1[0] = 0;
    s = 0;
    int ts;
    for (i=0; i<cn; i++) {
        ts = s;
        if (ts+ncs[i].v>mc) ts = mc-ncs[i].v;
        for (j=ts; j>=0; j--) {
            if (j+ncs[i].v > mc) continue;
            if (dp1[j]==INF) continue;
            if (dp1[j+ncs[i].v] > dp1[j]+ncs[i].c) dp1[j+ncs[i].v] = dp1[j]+ncs[i].c;
        }
        s += ncs[i].v; 
    }
    // printf("calc dp2\n");
    for (i=1; i<=mc-t; i++) dp2[i] = INF;
    dp2[0] = 0;
    for (i=0; i<n; i++) {
        for (j=vs[i]; j<=mc; j++) {
            if (dp2[j-vs[i]]==INF) continue;
            if (dp2[j-vs[i]]+1 < dp2[j]) dp2[j] = dp2[j-vs[i]]+1;
        }
    }
    s = INF;
    for (i=0; i<=mc-t; i++) {
        if (dp1[t+i]==INF) continue;
        if (dp2[i]==INF) continue;
        if (dp1[t+i]+dp2[i]<s) s = dp1[t+i]+dp2[i];
    }
    if (s==INF) printf("-1\n");
    else printf("%d\n", s);
    return 0;
}
