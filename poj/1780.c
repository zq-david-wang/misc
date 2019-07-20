#include<stdio.h>
#include<string.h>

char map[1000000];
char rs[1000000+8];
int end, mod;
int vs[1000000+8];
int dfs(int s, int c, int v) {
    if (c==end) {
        rs[s] = 0;
        return 1;
    }
    int i, r, nv; for (i=0; i<10; i++) {
        nv = v*10+i;
        if (map[nv]) continue;
        rs[s] = i+'0';
        map[nv] = 1;
        r = dfs(s+1, c+1, nv%mod);
        if (r) return r;
        map[nv] = 0;
    }
    return 0;

}
int main() {
    int n, i;
    int c, v, nv;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        end=1; for (i=0; i<n; i++) end*=10; mod=end/10;
        memset(map, 0, end*sizeof(map[0]));
        for (i=0; i<n; i++) rs[i]='0';
        vs[n-1]=0; map[0]=1;
        while(1) {
            if (i-n+1==end) break;
            v = vs[i-1];
            for (c=0; c<10; c++) {
                nv = v*10+c;
                if (map[nv]) continue;
                map[nv]=1;
                rs[i] = c+'0';
                vs[i] = nv%mod;
                i++;
                break;
            }
            if (c<10) continue;
            // try pop stack
            while(1) {
                nv = vs[i-2]*10+rs[i-1]-'0';
                map[nv]=0;
                for (c=rs[i-1]+1; c<='9'; c++) {
                    nv = vs[i-2]*10+c-'0';
                    if (map[nv]) continue;
                    map[nv] = 1;
                    rs[i-1] = c;
                    vs[i-1] = nv%mod;
                    break;
                }
                if (c<='9') break;
                i--;
            }
        }
        rs[i] = 0;
        printf("%s\n", rs);
    }
    return 0;
}
