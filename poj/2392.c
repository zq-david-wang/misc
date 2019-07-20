#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int c, h, mh;
}BNode;
BNode nodes[400];
int low[404], full[404];
int dp[40004];
int mycmp(const void *a, const void *b) {
    const BNode *pa = (const BNode *)a;
    const BNode *pb = (const BNode *)b;
    return pa->mh - pb->mh;
}
int main() {
    int k, i, mh, r, ei, ceil;
    scanf("%d", &k);
    for (i=0; i<k; i++) {
        scanf("%d %d %d", &nodes[i].h, &nodes[i].mh, &nodes[i].c);
    }
    qsort(nodes, k, sizeof(nodes[0]), mycmp);
    // for (i=0; i<k; i++) printf("%d %d %d\n", nodes[i].h, nodes[i].c, nodes[i].mh);
    r = 0; ei = k-1; mh = 0; ceil = nodes[ei].mh;
    for (i=ei; i>0; i--) {
        r += nodes[i].c*nodes[i].h;
        low[i] =  ceil - r;
        full[i] = r;
        if (r+nodes[i-1].mh<=ceil) {
            mh += r;
            ceil = nodes[i-1].mh;
            r = 0; 
            ei = i-1;
        }
    }
    r += nodes[0].c*nodes[i].h;
    low[0] = ceil - r;
    full[0] = r;
    int mv, th, h, c;
    // printf("ceil is %d, already collect %d, ei is %d\n", ceil, mh, ei);
    if (r<=ceil) mh+=r;
    else {
        // dp it
        for (i=0; i<=ceil; i++) dp[i] = 0;
        for (i=ei; i>=0; i--) {
            // printf("%d: low %d, full %d\n", i, low[i], full[i]);
            for (h=0; h<=low[i]; h++) dp[h] = full[i];
            for (; h<=ceil; h++ ) {
                mv = dp[h];
                th = 0;
                for (c=1; c<=nodes[i].c; c++) {
                    th += nodes[i].h;
                    if (h+th>nodes[i].mh) break;
                    if (mv<(dp[h+th]+th)) mv = th+dp[h+th];
                }
                dp[h] = mv;
            }
        }
        mh += dp[0];
    }
    printf("%d\n", mh);
    return 0;
}
