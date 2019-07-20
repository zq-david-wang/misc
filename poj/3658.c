#include<stdio.h>

#define INF 0x7fffffff
long long ws[100002];
int hs[100002];
int stack[100002];
long long ts[100002];
int main() {
    int n, i, mh=1000001, mi, j, k, stop, w;
    scanf("%d", &n);
    for (i=1; i<=n; i++){
        scanf("%d %d", &w, &hs[i]);
        ws[i] = w;
        if (hs[i]<mh) {
            mh = hs[i];
            mi = i;
        }
    }
    hs[0] = INF; hs[n+1] = INF;
    //start with mi
    int s=mi, e=mi, ci=mi, si;
    long long sh;
    long long t=0;
    while(1) {
        if (s==1 && e==n) {
            ts[ci] = t+ws[ci];
            break;
        }
        // printf("processing %d->%d\n", s, e);
        sh = INF;
        if (hs[s-1]<sh) { sh = hs[s-1]; si = s-1; }
        if (hs[e+1]<sh) { sh = hs[e+1]; si = e+1; }
        if (sh > hs[ci] ) {
            ts[ci] = t+ws[ci];
            t += ws[ci] *(sh-hs[ci]);
            ws[si] += ws[ci];
            ci = si;
            if (si<s) s = si;
            else e= si;
        } else {
            if (si<s) {
                // stack towards left
                stop = 0; stack[stop++] = ci;
                for (i=si; i>=0; i--) {
                    while(stop>0) {
                        j = stack[stop-1];
                        if (hs[i]>hs[j]) {
                            if (stop>1) {
                                ts[j] = t + ws[j];
                                k = stack[stop-2];
                                if (hs[k]>hs[i]) {
                                    t += (hs[i]-hs[j])*ws[j];
                                    ws[i] += ws[j];
                                } else {
                                    t += (hs[k]-hs[j])*ws[j];
                                    ws[k] += ws[j];
                                }
                            }
                            stop--;
                        } else { stack[stop++] = i; break; }
                    }
                    if (stop==0) break;
                }
                s = i+1;
            } else {
                // stack towards right
                stop = 0; stack[stop++] = ci;
                for (i=si; i<=n+1; i++) {
                    while(stop>0) {
                        j = stack[stop-1];
                        if (hs[i]>hs[j]) {
                            if (stop>1) {
                                ts[j] = t + ws[j];
                                k = stack[stop-2];
                                if (hs[k]>hs[i]) {
                                    t += (hs[i]-hs[j])*ws[j];
                                    ws[i] += ws[j];
                                } else {
                                    t += (hs[k]-hs[j])*ws[j];
                                    ws[k] += ws[j];
                                }
                            }
                            stop--;
                        } else { stack[stop++] = i; break; }
                    }
                    if (stop==0) break;
                }
                e = i-1;
            }
        }
    }
    // 
    for (i=1; i<=n; i++) printf("%lld\n", ts[i]);
    return 0;
}
