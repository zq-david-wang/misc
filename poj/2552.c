#include<stdio.h>
#include<string.h>

int vs[3000];
int main() {
    int i, j, v, n;
    vs[0] = 2;
    for (i=1; i<3000; i++) {
        v = 0;
        for (j=i-1; j>=0; j--) {
            n = vs[j];
            v = (v/(n-1))*n+(v%(n-1))+1;
        } 
        vs[i] = v+2;
    }
    while(1) {
        scanf("%d", &i); if (i==0) break;
        printf("%d\n", vs[i-1]);
    }
    return 0;
}
