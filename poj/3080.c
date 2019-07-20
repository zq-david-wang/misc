#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char seqs[10][64];
typedef struct { char *w; int i; } WNode;
WNode ws[640];
int gl;
char outline[64];
int mycmp(const void *a, const void *b) {
    const char *pa = *((const char **)a);
    const char *pb = *((const char **)b);
    return strncmp(pa, pb, gl);
}
int main() {
    int tc, ti, m, i, j, k;
    int l, h, s, cc;
    char f[10];
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d", &m); for (i=0; i<m; i++) scanf("%s", seqs[i]);
        l=3; h=60;
        while(l<=h) {
            s = (l+h)/2; k=0;
            for (i=0; i<m; i++) for (j=0; j+s<=60; j++) { ws[k].w = seqs[i]+j; ws[k].i = i; k++;}
            gl = s;
            qsort(ws, k, sizeof(ws[0]), mycmp);
            for (i=0; i<m; i++) f[i]=0; f[ws[0].i]=1; cc=1;
            for (i=1; i<k; i++) {
                if (strncmp(ws[i].w, ws[i-1].w, s)==0) {
                    if (f[ws[i].i]==0) { cc++; f[ws[i].i]=1; }
                    if (cc==m) break;
                } else {
                    for (j=0; j<m; j++) f[j]=0;
                    f[ws[i].i]=1; cc=1;
                }
            }
            if (cc==m) { if (l==s)break; l=s; }
            else h=s-1;
        }
        if (l>h) printf("no significant commonalities\n");
        else {
            // should try l+1
            for (j=0; j<s; j++) outline[j]=ws[i].w[j]; outline[j]=0;
            if (l<h) {
                s=h; k=0;
                for (i=0; i<m; i++) for (j=0; j+s<=60; j++) { ws[k].w = seqs[i]+j; ws[k].i = i; k++;}
                gl = s;
                qsort(ws, k, sizeof(ws[0]), mycmp);
                for (i=0; i<m; i++) f[i]=0; f[ws[0].i]=1; cc=1;
                for (i=1; i<k; i++) {
                    if (strncmp(ws[i].w, ws[i-1].w, s)==0) {
                        if (f[ws[i].i]==0) { cc++; f[ws[i].i]=1; }
                        if (cc==m) break;
                    } else {
                        for (j=0; j<m; j++) f[j]=0;
                        f[ws[i].i]=1; cc=1;
                    }
                }
                if (cc==m) { 
                    for (j=0; j<s; j++) outline[j]=ws[i].w[j]; outline[j]=0;
                }
            }
            printf("%s\n", outline);
        }
    }
    return 0;
}


