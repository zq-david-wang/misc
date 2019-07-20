#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ws[16], hs[16];
int main() {
    int w, h, i, j, t, v;
    while(1) { 
        scanf("%d %d", &w, &h); if (w==0&&h==0) break;
        for (i=0; i<w; i++) {
            scanf("%d", &v);
            for (j=i-1; j>=0; j--) {
                if (ws[j]<=v) break;
                ws[j+1]=ws[j];
            }
            ws[j+1]=v;
        }
        for (i=0; i<h; i++) {
            scanf("%d", &v);
            for (j=i-1; j>=0; j--) {
                if (hs[j]<=v) break;
                hs[j+1]=hs[j];
            }
            hs[j+1]=v;
        }
        // for (i=0; i<w; i++) printf(" %d", ws[i]); printf("\n");
        // for (i=0; i<h; i++) printf(" %d", hs[i]); printf("\n");
        i=w-1; j=h-1;
        t=0;
        while(1) {
            if (i<0) { while(j>=0) t+=hs[j--]; break; }
            if (j<0) { while(i>=0) t+=ws[i--]; break; }
            if (hs[j]==ws[i]) { t+=hs[j]; j--; i--; }
            else if (hs[j]>ws[i]) { t+=hs[j]; j--; }
            else { t+=ws[i--]; }
        }
        printf("%d\n", t);
    } 
    return 0;
}


