#include<stdio.h>
#include<string.h>

long long xs[1000], ys[1000];
short dis[1000][2];
int queue[1000*2];
#define EPS 0.000001
char buf1[128], buf2[128];
int main() {
    int n, i, j, k, ii, ic;
    int s, e, nj, v;
    int x, y;
    int head, tail;
    long long sd, tv, d;
    scanf("%d", &ic); for (ii=0; ii<ic; ii++) {
        scanf("%d %d %d %s %s", &n, &s, &e, buf1, buf2);
        s--; e--;
        //
        tv=0; i=0; j=0; k=0; while(1) {
            if (buf1[i]==0) break;
            if (buf1[i]!='.') {
                tv = tv*10+buf1[i]-'0';
                if (k) j++;
            } else {
                k=1; j=0;
            } i++;
        } for (;j<3; j++) tv*=10; sd=tv;
        // printf("tv1 is %lld\n", tv);
        tv=0; i=0; j=0; k=0; while(1) {
            if (buf2[i]==0) break;
            if (buf2[i]!='.') {
                tv = tv*10+buf2[i]-'0';
                if (k) j++;
            } else {
                k=1; j=0;
            } i++;
        } for (;j<3; j++) tv*=10; sd+=tv;
        // printf("tv2 is %lld, sd is %lld\n", tv, sd);
        sd = sd*sd;
        for (i=0; i<n; i++)  { 
            scanf("%d %d", &x, &y);
            xs[i]=x*1000; ys[i]=y*1000;
        }
        memset(dis, 0xff, sizeof(dis));
        head=tail=0; queue[head++] = s; dis[s][0]=0;
        while(tail<head) {
            i=queue[tail++];
            j=i>>16; i=i&0xffff; nj=(j+1)&1;
            // printf("--- using plug %d via %d\n", i, j);
            if (i==e) break;
            for (k=0; k<n; k++) {
                if (dis[k][nj]!=-1) continue;
                d = (xs[i]-xs[k])*(xs[i]-xs[k])+(ys[i]-ys[k])*(ys[i]-ys[k]);
                if (d>sd) continue;
                dis[k][nj] = dis[i][j]+1;
                queue[head++] = (nj<<16) | k;
            }
        }
        v = dis[e][0]; if (dis[e][1]>=0) if (v<0||v>dis[e][1]) v=dis[e][1];
        memset(dis, 0xff, sizeof(dis));
        head=tail=0; queue[head++] = (1<<16) | s; dis[s][1]=0;
        while(tail<head) {
            i=queue[tail++];
            j=i>>16; i=i&0xffff; nj=(j+1)&1;
            // printf("=== using plug %d via %d\n", i, j);
            if (i==e) break;
            for (k=0; k<n; k++) {
                if (dis[k][nj]!=-1) continue;
                d = (xs[i]-xs[k])*(xs[i]-xs[k])+(ys[i]-ys[k])*(ys[i]-ys[k]);
                if (d>sd+EPS) continue;
                dis[k][nj] = dis[i][j]+1;
                queue[head++] = (nj<<16) | k;
            }
        }
        if (dis[e][0]>=0) if (v<0||v>dis[e][0]) v=dis[e][0];
        if (dis[e][1]>=0) if (v<0||v>dis[e][1]) v=dis[e][1];
        if (v<0) printf("Impossible\n");
        else printf("%d\n", v);
    }
    return 0;
}
