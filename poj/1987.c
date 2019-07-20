#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct _T{
    struct _T *n;
    int b, d;
}NNode;
#define MAXEDGE 100000
NNode pool[MAXEDGE*2];
int pc=0;
#define MAXN 40000
NNode *nei[MAXN+4];
int dis[MAXN+4];
char flag[MAXN+4];
int queue[MAXN+4];
int dd[MAXN+4];
int gc;

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
    int cs[4], c;
    int *rs[4], *od = ds;
    int i, j, mi, nv;
    int d, cc, b;
    NNode *p;
    cc=0;p = nei[s]; while(p!=NULL) { if(flag[p->b]==0) cc++; p = p->n; }
    int head, tail, os;
    os=s;
    if (cc==1) {
        flag[s] = 1;
        head = tail = 0;
        queue[head++] = s;
        while(tail<head) {
            i = queue[tail++];
            p = nei[i];
            while(p!=NULL) {
                b = p->b;
                if (flag[b]==0) {
                    flag[b]=1;
                    queue[head++] = b;
                }
                p = p->n;
            }
        }
        for (i=0; i<tail; i++) flag[queue[i]]=0;
        s = queue[rand()%tail];
    }
    flag[s] = 1;
    ds++; c=1;
    od[0] = 0;
    p = nei[s]; d=0;
    while(p!=NULL) {
        b = p->b;
        if (flag[b]==0) {
            cc = count(b, k, ds);
            for (i=0; i<cc; i++) ds[i] += p->d;
            if (cc>1) qsort(ds, cc, sizeof(int), mycmp);
            mi = findi(k, ds, cc);
            gc += (mi+1);
            if (c>1) {
                for (j=0; j<cc; j++) {
                    nv = k-ds[j];
                    mi = findi(nv, od+1, c-1);
                    gc += (mi+1);
                }
            }
            c+=cc; ds+=cc;
            qsort(od+1, c-1, sizeof(int), mycmp);
        }
        p = p->n;
    }
    flag[s] = 0;
    // adjust to os
    if (s!=os) {
        head=tail=0;
        queue[head++] = os;
        flag[os] = 1; dd[os] = 0;
        cc=0; od[cc++] = 0;
        while(tail<head) {
            i = queue[tail++];
            p = nei[i];
            while(p!=NULL) {
                b = p->b;
                if (flag[b]==0) {
                    flag[b]=1;
                    queue[head++] = b;
                    dd[b] = dd[i]+p->d;
                    od[cc++] = dd[b];
                }
                p = p->n;
            }
        }
        for (i=0; i<tail; i++) flag[queue[i]]=0;
    }
    return c;
}
int main() {
    int n, m, i, k;
    int a, b, l;
    char c, d, buf[8];
    NNode *p;
    scanf("%d %d", &n, &m);
    for (i=1; i<=n; i++) { nei[i]=NULL; flag[i]=0; }
    for (i=0; i<m; i++) {
        scanf("%d %d %d %s", &a, &b, &l, buf);
        p = &pool[pc++]; p->b=b; p->d=l; p->n=nei[a]; nei[a]=p;
        p = &pool[pc++]; p->b=a; p->d=l; p->n=nei[b]; nei[b]=p;
    }
    scanf("%d", &k);
    gc = 0; count(1, k, dis);
    printf("%d\n", gc);
    return 0;
}
