#include<stdio.h>


int vs[100000];
int si[100000];
int main() {
    int c, n, i, s, j;
    while(1) {
        scanf("%d %d", &c, &n); if (c==0) break;
        for (i=0; i<n; i++) scanf("%d", &vs[i]);
        for (i=0; i<c; i++) si[i]=-1;
        s=0; for (i=0; i<n; i++) {
            if ((vs[i]%c)==0) { printf("%d\n", i+1); break;}
            s += vs[i]; s%=c;
            if (s==0) {
                printf("1"); for (j=1; j<=i; j++) printf(" %d", j+1); printf("\n");
                break;
            }
            if (si[s]==-1) si[s]=i;
            else {
                j=si[s]+1; printf("%d", j+1);
                for (j++; j<=i; j++) printf(" %d", j+1);
                printf("\n");
                break;
            }
        }
    }
    return 0;
}
