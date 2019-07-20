#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MOD 1024
int dqu[MOD], dqd[MOD];
int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}
int main() {
    int tc, ti, n, f, b, i, c, h, t;
    int quh, qut, qdh, qdt;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d %d %d", &n, &f, &b);
        quh=qut=qdh=qdt=0;
        for (i=0; i<n; i++) {
            scanf("%d %d", &h, &c);
            if (c==1) dqu[quh++]=f-h;
            else dqd[qdh++]=h;
        }
        qsort(dqu, quh, sizeof(dqu[0]), mycmp);
        // for (i=0; i<quh; i++) printf("%d ", dqu[i]); printf("\n----ups-----\n");
        qsort(dqd, qdh, sizeof(dqd[0]), mycmp);
        // for (i=0; i<qdh; i++) printf("%d ", dqd[i]); printf("\n----downs-----\n");
        while(b) {
            if (quh==qut) {
                t = dqd[qdt++]; qdt%=MOD;
                dqu[quh++]=t+f; quh%=MOD;
                b--;
            } else if(qdh==qdt) {
                t=dqu[qut++]; qut%=MOD;
                dqd[qdh++]=t+f; qdh%=MOD;
            } else {
                if (dqu[qut]<dqd[qdt]) {
                    t=dqu[qut++]; qut%=MOD;
                    dqd[qdh++]=t+f; qdh%=MOD;
                } else {
                    t = dqd[qdt++]; qdt%=MOD;
                    dqu[quh++]=t+f; quh%=MOD;
                    b--;
                }
            }
        }
        quh--; if (quh<0) quh=MOD-1; 
        printf("%d\n", dqu[quh]);
    }
    return 0;
}


