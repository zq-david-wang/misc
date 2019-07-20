#include<stdio.h>
#include<stdlib.h>


double xs[1000], ys[1000];
typedef struct { double qd,qdb; int i;}RNode;
int mycmp(const void *a, const void *b) {
    const RNode *pa =  (const RNode*)a;
    const RNode *pb =  (const RNode*)b;
    if (pa->qd<pb->qd) return -1;
    else if (pa->qd>pb->qd) return 1;
    return 0;
}
RNode qds[1000];
#define PI 3.141
#define EPS 0.0005
int main() {
    int n, ic=0, i, j, rc, cc;
    double x1, y1, x2, y2, t, rt;
    while(1) {
        scanf("%d", &n); if (n==0) break; ic++;
        scanf("%lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &t);
        for (i=0; i<n; i++) {
            scanf("%lf %lf", &xs[i], &ys[i]);
            qds[i].qd = ((xs[i]-x1)*(xs[i]-x1)+(ys[i]-y1)*(ys[i]-y1))*PI;
            qds[i].i = i;
        }
        qsort(qds, n, sizeof(qds[0]), mycmp);
        rc = 0;
        if (t==0) {
            for (i=0; i<n; i++) {
                if ((xs[i]==x1&&ys[i]==y1)||(xs[i]==x2&&ys[i]==y2)) rc++;
            }
        } else {
            for (i=0; i<n; i++) {
                j = qds[i].i;
                qds[i].qdb = ((xs[j]-x2)*(xs[j]-x2)+(ys[j]-y2)*(ys[j]-y2))*PI;
                if (qds[i].qdb-EPS<=t) rc++;
            }
            for (i=0; i<n; i++) {
                if (qds[i].qd-EPS>t) break;
                cc = i+1;
                rt = t-qds[i].qd;
                for (j=i+1; j<n; j++) if (qds[j].qdb-EPS<=rt) cc++;
                if (rc<cc) rc=cc;
            }
        }
        printf("%d. %d\n", ic, n-rc);
    }
    return 0;
}
