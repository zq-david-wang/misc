#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

typedef struct _T{
    struct _T *n;
    int b, d;
}NNode;
#define MAXEDGE 10000
NNode pool[MAXEDGE*2];
int pc=0;
#define MAXN 10000
NNode *nei[MAXN+4];
int dis[MAXN+4];
char flag[MAXN+4];
int queue[MAXN+4];
int dd[MAXN+4];
int temp[MAXN+4];
int gc;

int counts[MAXN+4];
int dia[MAXN+4];
int build(int s) {
    int c=1, d1=0, d2=0, b, r;
    flag[s] = 1;
    dia[s] = 0;
    NNode *p = nei[s];
    while(p!=NULL) {
        b = p->b;
        if (flag[b]==0){
            r = build(b)+p->d;
            if (r>d2){ d2=r; if (d2>d1) {r= d1; d1=d2; d2=r;} }
            c += counts[b];
            if (dia[s]<dia[b]) dia[s]=dia[b];
        }
        p = p->n;
    }
    flag[s] = 0;
    counts[s] = c;
    d2 += d1; if (dia[s]<d2) dia[s]=d2;
    return d1;
}
int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}

int findi(int v, int *s, int n) {
    int l=0, h=n-1, m;
    while(l<=h) {
        m = (l+h)/2;
        if (s[m]>v) h=m-1;
        else {
            if (l==m) break;
            l=m;
        }
    }
    while (l<=h && s[l]<=v) l++;
    return l-1;
}

int count(int s, int k, int *ds) {
    int  c, *od = ds;
    int i, j, nv, mi;
    int d, cc, b;
    NNode *p;
    int head, tail;
    int i1, i2;
    if (dia[s]<=k) {
        gc += (counts[s]*(counts[s]-1)/2);
        head=tail=0;
        queue[head++] = s;
        flag[s] = 1; dd[s] = 0;
        c=0; od[c++] = 0;
        while(tail<head) {
            i = queue[tail++];
            p = nei[i];
            while(p!=NULL) {
                b = p->b;
                if (flag[b]==0) {
                    flag[b]=1;
                    queue[head++] = b;
                    dd[b] = dd[i]+p->d;
                    if (dd[b]<=k) od[c++] = dd[b];
                }
                p = p->n;
            }
        }
        for (i=0; i<tail; i++) flag[queue[i]]=0;
        qsort(od, c, sizeof(int), mycmp);
    } else {
        flag[s] = 1;
        ds++; c=1;
        od[0] = 0;
        p = nei[s]; d=0;
        while(p!=NULL) {
            b = p->b;
            if (flag[b]==0) {
                cc = count(b, k, ds);
                for (i=0; i<cc; i++) { ds[i] += p->d; if (ds[i]>k) break; }
                cc=i; gc += cc;
                if (c>1) {
                    for (j=0; j<cc; j++) {
                        nv = k-ds[j];
                        mi = findi(nv, od+1, c-1);
                        gc += (mi+1);
                    }
                    // merge od[1, c-1], ds[0, cc-1] to temp and copy back
                    i1 = 1; i2 = 0; j=0;
                    while(1) {
                        if (i1>=c && i2>=cc) break;
                        if (i1>=c) { while(i2<cc) temp[j++]=ds[i2++]; break; }
                        if (i2>=cc) { while(i1<c) temp[j++]=od[i1++]; break; }
                        if (od[i1]<=ds[i2]) { temp[j++] = od[i1++]; }
                        else { temp[j++] = ds[i2++]; }
                    }
                    for (i=0; i<j; i++) od[i+1] = temp[i];
                }
                c+=cc; ds+=cc;
            }
            p = p->n;
        }
        flag[s] = 0;
    }
    return c;
}
int main() {
    int n, m, i, k;
    int a, b, l;
    NNode *p;
    while(1) {
        scanf("%d %d", &n, &k);
        srand (n);
        if (n==0 && k==0) break;
        for (i=1; i<=n; i++) { nei[i]=NULL; flag[i]=0; }
        pc = 0;
        for (i=1; i<n; i++) {
            scanf("%d %d %d", &a, &b, &l);
            p = &pool[pc++]; p->b=b; p->d=l; p->n=nei[a]; nei[a]=p;
            p = &pool[pc++]; p->b=a; p->d=l; p->n=nei[b]; nei[b]=p;
        }
        build(1);
        // for (i=1; i<=n; i++) { printf("%d: %d, %d\n", i, dia[i], counts[i]); }
        gc = 0; count(1, k, dis);
        printf("%d\n", gc);
    }
    return 0;
}
