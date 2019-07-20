#include<stdio.h>

int main() {
    int s, d, mv, v; 
    while(scanf("%d %d", &s, &d) == 2) {
        mv = -1;
        if (s<4*d) { v = s*3-9*d; if (v>mv) mv = v; }
        if (2*s<3*d) { v = s*6-d*6; if (v>mv) mv = v; }
        if (3*s<2*d) { v = 8*s-4*d; if (v>mv) mv = v; }
        if (4*s<d) { v = 10*s-2*d; if (v>mv) mv = v; }
        if (mv<=0) printf("Deficit\n");
        else printf("%d\n", mv);
    }
    return 0;
}
