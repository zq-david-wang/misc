#include<stdio.h>

int array[20][20];
int main() {
    int n, s, i, j;
    scanf("%d %d", &n, &s);
    for (i=0; i<n; i++) {
       for (j=0; j<=i; j++) {
           array[j][i] = s;
           s++; s %=10; if (s==0) s++;
       }
    }
    for (i=0; i<n; i++) {
        s = i*2; for (j=0; j<s; j++) printf(" ");
        printf("%d", array[i][i]);
        for (j=i+1; j<n; j++) printf(" %d", array[i][j]);
        printf("\n");
    }
    return 0;
}
