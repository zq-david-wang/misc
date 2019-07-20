#include<stdio.h>

int ps[150000];
int main() {
    int p, i;
    scanf("%d", &p);
    for (i=0; i<p; i++) scanf("%d", &ps[i]);
    int h1=0, h2=0, nh1, nh2;
    for (i=p-1; i>=0; i--) {
        nh1 = ps[i]+h2; 
        if (nh1<h1) nh1=h1;
        nh2 = h1-ps[i];
        if (nh2<h2) nh2=h2;
        h1 = nh1;
        h2 = nh2;
    }
    printf("%d\n", h1);
    return 0;
}
