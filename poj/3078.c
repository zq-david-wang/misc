#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char names[64][16];
char queue[64];
char queue2[64];
char mark[64];
int main() {
    int tc, ti, m, n, i, j, a, b;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d %d", &m, &n);
        for (i=0; i<m; i++) scanf("%s", names[i]);
        for (i=0; i<m; i++) { queue[i]=i; queue2[i]=-1; mark[i]=0;}
        for (i=0; i<n; i++) {
            scanf("%d %d", &a, &b); a--; b--;
            queue2[b] = queue[a]; mark[queue[a]]=1;
        }
        j=0; for (i=0; i<m; i++) {
            if (mark[i]) continue;
            while(queue2[j]!=-1) j++;
            queue2[j]=i;
        }
        for (i=0; i<m; i++) { if (i==0)printf("%s", names[queue2[i]]); else printf(" %s", names[queue2[i]]);}
        printf("\n");
    }
    return 0;
}


