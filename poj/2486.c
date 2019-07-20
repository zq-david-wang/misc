#include<stdio.h>
#include<string.h>

typedef struct {
    char nei[100], nc, cc;
    int *dp1, *dp2, v;
}TNode;

TNode nodes[100];
char flag[100];
char queue[128];
int cache[128*201*2];
int gk;

int dfs2(int s, int k, int i) {
    int v = 0;
    if (i==0) v = nodes[s].v;
    if (k<2 || i>=nodes[s].cc) return v;
    int ii = i*gk+k;
    if (nodes[s].dp2[ii] != -1) return nodes[s].dp2[ii];
    // int a = dfs2(nodes[s].nei[i], k-2, 0);
    int a = dfs2(s, k, i+1);
    int ta;
    // keep try
    int ss; for (ss=2; ss<=k; ss+=2) {
        ta = dfs2(nodes[s].nei[i], ss-2, 0) + dfs2(s, k-ss, i+1);
        if (a<ta) a=ta;
    }
    a += v;
    nodes[s].dp2[ii] = a;
    // printf("dfs2 %d, %d, %d ==> %d\n", s, k, i, a);
    return a;
}

int dfs1(int s, int k, int i) {
    int v = 0;
    if (i==0) v = nodes[s].v;
    if (k==0 || i>=nodes[s].cc) return v;
    int ii = i*gk+k;
    if (nodes[s].dp1[ii] != -1) return nodes[s].dp1[ii];
    int a = dfs1(nodes[s].nei[i], k-1, 0);
    int ta = dfs1(s, k, i+1);
    if (a<ta) a=ta;
    // keep try
    int ss; for (ss=2; ss<=k; ss+=2) {
        ta = dfs2(nodes[s].nei[i], ss-2, 0) + dfs1(s, k-ss, i+1);
        if (a<ta) a=ta;
        if (ss<k) {
            ta = dfs1(nodes[s].nei[i], k-ss-1, 0) + dfs2(s, ss, i+1);
            if (a<ta) a=ta;
        }
    }
    a += v;
    nodes[s].dp1[ii] = a;
    // printf("dfs1 %d, %d, %d ==> %d\n", s, k, i, a);
    return a;
}

int main() {
    int n, k, i, a, b, *p;
    int head, tail;
    while(scanf("%d %d", &n, &k)==2) {
        for (i=0; i<n; i++) {
            scanf("%d", &nodes[i].v);
            nodes[i].nc = 0;
            nodes[i].cc = 0;
            flag[i] = 0;
        }
        for (i=0; i<n-1; i++) {
            scanf("%d %d", &a, &b);
            a--; b--;
            nodes[a].nei[nodes[a].nc++] = b;
            nodes[b].nei[nodes[b].nc++] = a;
        }
        head = tail = 0;
        queue[head++] = 0;
        flag[0] = 1;
        while(tail<head) {
            a = queue[tail++];
            for (i=0; i<nodes[a].nc; i++) {
                b = nodes[a].nei[i];
                if (flag[b] == 0) {
                    flag[b] = 1;
                    queue[head++]=b;
                    nodes[a].nei[nodes[a].cc++] = b;
                }
            }
        }
        // for (i=0; i<n; i++) {
        //     printf("%d: %d[", i, nodes[i].cc);
        //     int j; for (j=0; j<n; j++) printf("%d ", nodes[i].nei[j]);
        //     printf("]\n");
        // }
        p = cache;
        memset(cache, 0xff, (k+1)*n*2*sizeof(cache[0]));
        for (i=0; i<n; i++) {
            nodes[i].dp1 = p; p += nodes[i].cc*(k+1);
            nodes[i].dp2 = p; p += nodes[i].cc*(k+1);
        }
        gk = k;
        a = dfs1(0, k, 0);
        printf("%d\n", a);
    }
    return 0;
}
