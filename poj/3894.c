#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct { int n, p, b, a; } npool[10000*256];
int nei[10000*2+4];
int path[10000*2+4];
char flag[10000*2+4];
int queue[10000*2+4];
int dfs(int s, int e) {
    if (s==e) return 1;
    int j = nei[s], b, pj;
    while(j!=-1) {
        if (1) {
            b = npool[j].b;
            if (flag[b]==0) {
                path[b] = j;
                flag[b]=1;
                if (dfs(b, e)) return 1;
            }
        }
        j = npool[j].n;
    }
    return 0;
}
int findpath(int s, int e) {
    memset(flag, 0, (e+1));
    flag[s]=1;
    // return  dfs(s, e);
    int head=0, tail=0, j, b;
    queue[head++] = s;
    while(tail<head) {
        s = queue[tail++];
        j = nei[s];
        while(j!=-1) {
            b = npool[j].b;
            if (flag[b]==0) {
                path[b]=j;
                if (b==e) return 1;
                flag[b]=1;
                queue[head++] = b;
            }
            j = npool[j].n;
        }
    }
    return 0;
}
int maxflow(int s, int e) {
    memset(flag, 0, e+1);
    int r = 0, f, a, b, j;
    while(1) {
        f = findpath(s, e);
        if (f==0) break;
        r += f;
        b = e;
        while(b!=s) {
            j = path[b];
            a = npool[j].a;
            if (npool[j].p==-1) {
                nei[a] = npool[j].n;
                if (nei[a]!=-1) npool[nei[a]].p=-1;
            } else {
                npool[npool[j].p].n = npool[j].n;
                if (npool[j].n!=-1) npool[npool[j].n].p=npool[j].p;
            }
            if (nei[b]!=-1) npool[nei[b]].p=j;
            npool[j].n=nei[b]; npool[j].b=a; npool[j].a=b; nei[b]=j;
            b=a;
        }
    }
    return r;
}
int main() {
    int n, c, i, j;
    int ji, si;
    int pc;
    while(scanf("%d", &n)==1) {
        pc=0; memset(nei, 0xff, sizeof(int)*(n+n+2));
        for (i=1; i<=n; i++) {
            if (nei[0]!=-1) npool[nei[0]].p = pc;
            npool[pc].n=nei[0]; npool[pc].a=0; npool[pc].b=i; npool[pc].p=-1; nei[0]=pc++;
        }
        for (i=n+1; i<=n+n; i++) {
            if (nei[i]!=-1) npool[nei[i]].p = pc;
            npool[pc].n=nei[i]; npool[pc].a=i; npool[pc].b=n+n+1; npool[pc].p=-1; nei[i]=pc++;
        }
        for (i=0; i<n; i++) {
            scanf("%d: (%d)", &ji, &c); ji++;
            for (j=0; j<c; j++) {
                scanf("%d", &si); si++;
                if (nei[ji]!=-1) npool[nei[ji]].p = pc;
                npool[pc].n=nei[ji]; npool[pc].a=ji; npool[pc].b=si; npool[pc].p=-1; nei[ji]=pc++;
            }
        }
        i = maxflow(0, n+n+1);
        printf("%d\n", i);
    }
    return 0;
}


