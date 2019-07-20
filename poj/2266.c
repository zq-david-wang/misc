#include<stdio.h>

char qs[512*512*2+8];
char map[512][512];
int popu(int s, int r, int c, int d) {
    if (qs[s]=='B'||qs[s]=='W') {
        int i, j;
        for (i=0; i<d; i++) for (j=0; j<d; j++) map[r+i][c+j]=qs[s];
        return s+1;
    }
    d /= 2;
    s = popu(s+1, r, c, d);
    s = popu(s, r, c+d, d);
    s = popu(s, r+d, c, d);
    return popu(s, r+d, c+d, d);
}
int main() {
    int n, i, j, k, c, v;
    scanf("%d %s", &n, qs);
    popu(0, 0, 0, n);
    printf("#define quadtree_width %d\n", n);
    printf("#define quadtree_height %d\n", n);
    printf("static char quadtree_bits[] = {\n");
    for (i=0; i<n; i++) {
        for (j=0; j<n/8; j++) {
            v = 0;
            for (k=7; k>=0; k--) {
                c = map[i][j*8+k]; v*=2;
                if (c=='B') v+=1;
            }
            printf("0x%02x,", v);
        }
        printf("\n");
    }
    printf("};\n");
    return 0;
}
