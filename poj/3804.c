#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct { short t, c, dt; } Player;
Player ps[50];
int buf[50];
#define MOD 128
#define INF 0xffffff
int lane1[MOD], lane2[MOD];
int main() {
    int n, i, t, c, j, k, kk;
    int h1, t1, h2, t2, dt1, dt2, dt, tt;
    while(1) {
        scanf("%d", &n); if (n==0) break;
        for (i=0; i<n; i++) {
            scanf("%d %d", &t, &c);
            ps[i].t=t; ps[i].c=c; ps[i].dt=t;
            for (j=i-1; j>=0; j--) {
                if (ps[buf[j]].t <= t) break;
                buf[j+1]=buf[j];
            }
            buf[j+1] = i;
        }
        tt = 0;
        h1=t1=h2=t2=0;
        for (i=0; i<n; i++) lane1[t1++]=buf[i]; 
        while(1) {
            dt1 = INF; dt2 = INF;
            if (h1!=t1) dt1 = ps[lane1[h1]].dt;
            if (h2!=t2) dt2 = ps[lane2[h2]].dt;
            if (dt1>dt2) dt1=dt2;
            if (dt1==INF) break;
            tt += dt1;
            for (i=h1; i!=t1; ){ j=lane1[i]; i++; i%=MOD; ps[j].dt-=dt1; }
            for (i=h2; i!=t2; ){ j=lane2[i]; i++; i%=MOD; ps[j].dt-=dt1; }
            k=0; while(h1!=t1) {
                j = lane1[h1]; if (ps[j].dt) break;
                h1++; h1%=MOD;
                for (kk=k-1; kk>=0; kk--) {
                    if (ps[buf[kk]].t <= ps[j].t) break;
                    buf[kk+1]=buf[kk];
                }
                buf[kk+1] = j; k++;
            }
            for (i=0; i<k; i++) {
                j = buf[i];
                dt=0; if (h2!=t2) dt = ps[lane2[(t2+MOD-1)%MOD]].dt;
                if (dt<ps[j].t) dt=ps[j].t;
                ps[j].dt=dt; lane2[t2++]=j; t2%=MOD;
            }
            k=0; while(h2!=t2) {
                j=lane2[h2]; if (ps[j].dt) break;
                h2++; h2%=MOD;
                ps[j].c--;
                if (ps[j].c) {
                    for (kk=k-1; kk>=0; kk--) {
                        if (ps[buf[kk]].t <= ps[j].t) break;
                        buf[kk+1]=buf[kk];
                    }
                    buf[kk+1] = j; k++;
                }
            }
            for (i=0; i<k; i++) {
                j = buf[i];
                dt=0; if (h1!=t1) dt = ps[lane1[(t1+MOD-1)%MOD]].dt;
                if (dt<ps[j].t) dt=ps[j].t;
                ps[j].dt=dt; lane1[t1++]=j; t1 %=MOD;
            }
        }
        printf("%d\n", tt);
    }
    return 0;
}


