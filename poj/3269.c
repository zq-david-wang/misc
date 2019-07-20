#include<stdio.h>
#include<stdlib.h>

int mycmp(const void*a, const void *b) {
    return *((const int *)a) - *((const int *)b);
}

int xs[10000], ys[10000];
int vx[10000], vy[10000];
int main() {
    int n, i, c, x1, y1, x2, y2, d, j;
    long long cost;
    int can[4][2], canc;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d %d", &xs[i], &ys[i]);
        vx[i] = xs[i]; vy[i] = ys[i];
    }
    qsort(vx, n, sizeof(vx[0]), mycmp);
    qsort(vy, n, sizeof(vy[0]), mycmp);
    cost = 0; c = 0;
    if (n&1) {
        x1 = vx[n/2];
        y1 = vy[n/2];
        for (i=0; i<n; i++) {
            if (xs[i]==x1&&ys[i]==y1) break;
            d = xs[i]-x1; if (d<0) d=-d; cost += d;
            d = ys[i]-y1; if (d<0) d=-d; cost += d;
        }
        if (i==n) c=1;
        else {
            c = 0;
            canc = 0;
            cost = 0;
            if (x1+1<=vx[n/2+1]) { can[canc][0]=x1+1; can[canc][1]=y1; canc++; x2=x1+1; y2=y1;}
            if (x1-1>=vx[n/2-1]) { can[canc][0]=x1-1; can[canc][1]=y1; canc++; x2=x1-1; y2=y1;}
            if (y1+1<=vy[n/2+1]) { can[canc][0]=x1; can[canc][1]=y1+1; canc++; x2=x1; y2=y1+1;}
            if (y1-1>=vy[n/2-1]) { can[canc][0]=x1; can[canc][1]=y1-1; canc++; x2=x1; y2=y1-1;}
            if (canc==0) printf("error\n");
            for (i=0; i<n; i++) {
                for (j=0; j<canc; j++) {
                    if (xs[i]==can[j][0]&&ys[i]==can[j][1]) {
                        c++;
                        break;
                    }
                }
                d = xs[i]-x2; if (d<0) d=-d; cost += d;
                d = ys[i]-y2; if (d<0) d=-d; cost += d;
            }
            c = canc-c;
        }
    } else {
        cost = 0; c = 0;
        x1 = vx[n/2-1]; x2 = vx[n/2];
        y1 = vy[n/2-1]; y2 = vy[n/2];
        for (i=0; i<n; i++) {
            if (xs[i]>=x1&&xs[i]<=x2&&ys[i]>=y1&&ys[i]<=y2) c++;
            d = xs[i]-x1; if (d<0) d=-d; cost += d;
            d = ys[i]-y1; if (d<0) d=-d; cost += d;
        }
        c = (x2-x1+1)*(y2-y1+1) - c;
    }
    printf("%lld %d\n", cost, c);
    return 0;
}
