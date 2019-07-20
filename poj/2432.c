#include<stdio.h>
#include<string.h>

#define MARGIN 20
int loc[5001];
char flag[5001][MARGIN+MARGIN+1];
struct { unsigned short s, d; short r; }queue[5001*MARGIN*2];
int nei[5001][5000];
int neic[5001];
int main() {
    int n, m, i, a, b;
    scanf("%d %d", &n, &m);
    for (i=1; i<=n; i++) {
        scanf("%d", &loc[i]);
        neic[i] = 0;
    }
    for (i=0; i<m; i++) {
        scanf("%d %d", &a, &b);
        nei[a][neic[a]++] = b;
        nei[b][neic[b]++] = a;
    }
    int start = loc[1];
    int qhead, qtail;
    qhead = qtail = 0;
    queue[qhead].s = 1;
    queue[qhead].d = 0;
    queue[qhead].r = 0;
    qhead++;
    memset(flag, 0, sizeof(flag));
    flag[1][0+MARGIN] = 1;
    char find = 0;
    int l, s, d, round, nr, cw, ccw, ncw, nccw;
    int dcw, dccw, lb;
    while(qtail<qhead) {
        s = queue[qtail].s;
        l = loc[s];
        d = queue[qtail].d+1;
        round = queue[qtail].r; 
        qtail++;
        cw = 0; ccw = 0;
        if (l>=start) cw = l-start;
        else cw = 360+l-start;
        // cw - ccw = round*360
        ccw = (cw/360)*360 - round*360;

        // printf("process s: %d, l: %d, next d: %d, round :%d, cw: %d, ccw: %d\n", s, l, d, round, cw, ccw);
        for (i=0; i<neic[s]; i++) {
            b = nei[s][i];
            lb = loc[b];
            // from l->lb
            dccw = 0;
            if (l<lb) dcw = lb-l;
            else dcw = lb-l+360;
            if (dcw >=180) {
                dccw = 360-dcw;
                dcw = 0;
            }
            ncw = (cw+dcw);
            nccw = (ccw+dccw);
            if (nccw!=ncw && b==1) {
                find = 1;
                break;
            }
            nr = (ncw-nccw)/360;
            if (ncw<nccw) nr--;
            if (nr<-MARGIN || nr>MARGIN) continue;
            // printf("try %d(%d), dcw:%d, dccw:%d ncw:%d,nccw:%d\n", b, lb, dcw, dccw, ncw, nccw);
            if (flag[b][nr+MARGIN]==0) {
                flag[b][nr+MARGIN] = 1;
                queue[qhead].s = b;
                queue[qhead].d = d;
                queue[qhead].r = nr;
                qhead++;
            }
        }
        if (find) break;
    }

    if (find) {
        printf("%d\n", d);
    } else printf("-1\n");
    return 0;
}
