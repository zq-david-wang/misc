/*
 * =====================================================================================
 *
 *       Filename:  3640.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2019年01月18日 20时52分40秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include<stdio.h>

typedef struct _T{
    struct _T *cs[10];
    int c;
}Node;
Node gpool[100000];
int gpc;
Node *alloc() {
    Node *r = &gpool[gpc++];
    int i; for (i=0; i<10; i++) r->cs[i] = NULL;
    r->c = 0;
    return r;
}
void init() {
    gpc = 0;
}
int count(Node *r, int d, int m) {
    if (r==NULL) return 0;
    if (d==0) {
        if (m==r->c) return m;
        return 0;
    }
    int i, c=0;
    for (i=0; i<10; i++) c+=count(r->cs[i], d-1, m);
    return c;
}

int main() {
    int n, vs[5];
    int i, j, k, t;
    int m;
    Node *r, *p;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        init(); r = alloc();
        m = 0;
        for (i=0; i<n; i++) {
            for (j=0; j<5; j++) scanf("%d", &vs[j]);
            for (j=1; j<5; j++) {
                t = vs[j];
                for (k=j-1; k>=0; k--) {
                    if (vs[k]<=t)break;
                    vs[k+1] =vs[k];
                }
                vs[k+1] = t;
            }
            p = r;
            for (j=0; j<5; j++) {
               t = vs[j];
               for (k=0; k<3; k++) {
                   if (p->cs[t%10] == NULL) p->cs[t%10] = alloc();
                   p = p->cs[t%10];
                   t /= 10;
               }
            }
            p->c++;
            if (m<p->c)m = p->c;
        }
        i = count(r, 15, m);
        printf("%d\n", i);
    }
    return 0;
}
