#include<stdio.h>
#include<string.h>

char map[1024][2050];
int main() {
    int n, l, i, j, k, d;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        l=1; for (i=0; i<n; i++) l*=2;
        for (i=0; i<l; i++) memset(map[i], ' ', 2*l);
        // draw base
        map[l-1][0]='/'; map[l-1][1]='_'; map[l-1][2]='_'; map[l-1][3]='\\';
        map[l-2][1]='/'; map[l-2][2]='\\';
        // copy
        d = 1;
        for (i=1; i<n; i++) {
            // l-i*2, i*2*2
            d*=2;
            for (j=l-d; j<l; j++) for (k=0; k<d*2; k++) {
                map[j-d][k+d] = map[j][k+d*2]=map[j][k];
            }
        }
        // mark margin
        for (i=0; i<l; i++) map[i][l+i+1]=0;
        for (i=0; i<l; i++) printf("%s\n", map[i]); 
        printf("\n");
    }
    return 0;
}
