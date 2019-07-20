#include<stdio.h>
int main() {
    int n, i, j, k, r, mi, mk;
    char b[16];
    int fs[] = {9, 3, 7};
    scanf("%d", &n);
    for (i=1; i<=n; i++) {
        scanf("%s", b);
        j=0; while(b[j]!=0)j++;
        r=0;k=0;for (j--; j>=0; j--) {
            if (b[j]=='?') {
                mi = j;
                mk = fs[k];
            } else {
                r += fs[k]*(b[j]-'0');
            }
            k++; k%=3;
        }
        for (j=0; j<9; j++) {
            if (((j*mk+r) % 10)==0)break;
        }
        b[mi] = j+'0';
        printf("Scenario #%d:\n", i);
        printf("%s\n", b);
        printf("\n");
    }
    return 0;
}
