#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int readline(char *b) {
    int i=0;
    char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        b[i++] = c;
    }
    b[i]=0;
    return i;
}

char buf1[32];
char graph[64*80+4];
int cs[128][128];
typedef struct { char c1, c2; short c; } CNode;
CNode nodes[128*128];
int mycmp(const void *a, const void *b) {
    const CNode *pa = (const CNode*)a;
    const CNode *pb = (const CNode*)b;
    if (pa->c != pb->c) return pb->c-pa->c;
    if (pa->c1 != pb->c1) return pa->c1-pb->c1;
    return pa->c2 - pb->c2;
}
int main() {
    int n, i, l, j, k;
    double r;
    while(1) {
        readline(buf1);
        sscanf(buf1, "%d", &n);
        if (n==0) break;
        l = 0;
        for (i=0; i<n; i++) {
            l += readline(graph+l);
        }
        memset(cs, 0, sizeof(cs));
        for (i=1; i<l; i++) {
            cs[graph[i-1]][graph[i]]++;
        }
        k=0; for (i=0; i<128; i++) for (j=0; j<128; j++) {
            nodes[k].c1 = i; nodes[k].c2 = j;
            nodes[k].c = cs[i][j];
            k++;
        }
        qsort(nodes, 128*128, sizeof(nodes[0]), mycmp);
        for (i=0; i<5; i++) {
            r = nodes[i].c; r/=(l-1);
            printf("%c%c %d %.6f\n", nodes[i].c1, nodes[i].c2, nodes[i].c, r);
        }
        printf("\n");
    }
    return 0;
}
