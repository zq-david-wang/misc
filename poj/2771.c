#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct { short h, g, m, s; } stu[500];
char mnames[500][100];
char snames[500][100];
int mnc, snc;
char mn[128], sn[128];
int addmname(const char *n) {
    int i; for (i=0; i<mnc; i++) if (strcmp(n, mnames[i])==0) return i;
    strcpy(mnames[i], n);
    mnc++; return i;
}
int addsname(const char *n) {
    int i; for (i=0; i<snc; i++) if (strcmp(n, snames[i])==0) return i;
    strcpy(snames[i], n);
    snc++; return i;
}
char map[504][504];
char flow[504][504];
char flag[504];
short neic[504];
short path[504];
short neis[504][504];

int dfs(int s, int e) {
    if (s==e) return 1;
    int i, b; for (i=0; i<neic[s]; i++) {
        b = neis[s][i];
        if (flag[b]) continue;
        if (flow[b][s]||(map[s][b]&&flow[s][b]==0)) {
            path[b]=s;
            flag[b]=1;
            if (dfs(b, e))return 1;
        }
    }
    return 0;
}
int findpath(int s, int e) {
    memset(flag, 0, sizeof(flag));
    flag[s]=1;
    return dfs(s, e);
}
int maxflow(int s, int e) {
    memset(flow, 0, sizeof(flow));
    int r=0, f;
    int a, b;
    while(1) {
        f = findpath(s, e);
        if (f==0) break;
        r += f;
        b=e;
        while(b!=s) {
            a= path[b];
            if (flow[b][a]) flow[b][a]=0;
            else flow[a][b]=1;
            b=a;
        }
    }
    return r;
}
int main() {
    int tc, ti, i, n, j, h, m;
    char gb[8];
    int d;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d", &n); mnc=snc=0;
        for (i=0; i<n; i++) {
            scanf("%d %s %s %s", &h, gb, mn, sn);
            stu[i].h=h;
            stu[i].g=0; if (gb[0]=='M') stu[i].g=1;
            stu[i].m = addmname(mn);
            stu[i].s = addsname(sn);
        }
        memset(map, 0, sizeof(map));
        for (i=0; i<=n+1; i++) neic[i]=0;
        for (i=0; i<n; i++) {
            if (stu[i].g) {
                map[0][i+1]=1;
                neis[0][neic[0]++] = i+1;
                neis[i+1][neic[i+1]++] = 0;
            } else {
                map[i+1][n+1]=1;
                neis[i+1][neic[i+1]++] = n+1;
                neis[n+1][neic[n+1]++] = i+1;
            }
        }
        for (i=0; i<n; i++) {
            if (stu[i].g==0) continue;
            for (j=0; j<n; j++) {
                if (stu[j].g) continue;
                m=0;
                d = stu[i].h-stu[j].h; if (d<0) d=-d;
                if (d<=40) m++;
                if (stu[i].m==stu[j].m) m++;
                if (stu[i].s!=stu[j].s) m++;
                if (m<3) continue;
                map[i+1][j+1]=1;
                neis[i+1][neic[i+1]++]=j+1;
                neis[j+1][neic[j+1]++]=i+1;
            }
        }
        m = maxflow(0, n+1); 
        printf("%d\n", n-m);
    }
    return 0;
}


