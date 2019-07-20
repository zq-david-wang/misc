#include<stdio.h>

struct {int x, y, t;}peb[8];
char map[16][16];
int main() {
    int p, b1, b2, r, i, j;
    scanf("%d %d %d %d", &p, &b1, &b2, &r);
    if (b1>b2) { i=b1; b1=b2; b2=i; }
    for (i=0; i<p; i++) {
        scanf("%d %d %d", &peb[i].x, &peb[i].y, &peb[i].t);
    }
    for (i=0; i<9; i++) for (j=0; j<9; j++) map[i][j] = '-';
    int d1, d2, d11, d12, d, k, td;
    int tb = b2-b1-1;
    for (i=-4; i<=4; i++) {
        for (j=-4; j<=4; j++) {
            if (i==b1||i==b2) { map[4-j][4+i] = 'X'; continue; }
            d = 0;
            for (k=0; k<p; k++) {
                if (peb[k].t > r) continue;
                if (peb[k].x<b1&&i>b1) continue;
                if (peb[k].x>b1&&i<b1) continue;
                if (peb[k].x<b2&&i>b2) continue;
                if (peb[k].x>b2&&i<b2) continue;
                d1 = peb[k].x-i; if (d1<0) d1=-d1;
                d2 = peb[k].y-j; if (d2<0) d2=-d2;
                if (d1+d2 == r-peb[k].t) d++;
                if (d1+d2 == r-peb[k].t-2) d--;
                d11 = peb[k].x-b1; if (d11<0) d11=-d11;
                d12 = i-b1; if (d12<0) d12=-d12;
                d1 = d11+d12-1;
                if (d1+d2 == r-peb[k].t) d++;
                if (d1+d2 == r-peb[k].t-2) d--;
                d11 = peb[k].x-b2; if (d11<0) d11=-d11;
                d12 = i-b2; if (d12<0) d12=-d12;
                d1 = d11+d12-1;
                if (d1+d2 == r-peb[k].t) d++;
                if (d1+d2 == r-peb[k].t-2) d--;
                // if mutiple refrect
                if (tb > 0 && i>b1 && i<b2) {
                    d11 = peb[k].x-b1; d12 = i-b1;
                    td = (r-peb[k].t)-d11-d12+1-d2;
                    if (td>0 && (td%tb)==0) {
                        td /= tb; if ((td&1)==0) d++;
                    }
                    td = (r-peb[k].t-2)-d11-d12+1-d2;
                    if (td>0 && (td%tb)==0) {
                        td /= tb; if ((td&1)==0) d--;
                    }
                    d11 = peb[k].x-b1; d12 = b2-i;
                    td = (r-peb[k].t)-d11-d12+1-d2;
                    if (td>0 && (td%tb)==0) {
                        td /= tb; if ((td&1)==1) {
                            d++;
                        }
                    }
                    td = (r-peb[k].t-2)-d11-d12+1-d2;
                    if (td>0 && (td%tb)==0) {
                        td /= tb; if ((td&1)==1) d--;
                    }
                    
                    d11 = b2-peb[k].x; d12 = i-b1;
                    td = (r-peb[k].t)-d11-d12+1-d2;
                    if (td>0 && (td%tb)==0) {
                        td /= tb; if ((td&1)==1) d++;
                    }
                    td = (r-peb[k].t-2)-d11-d12+1-d2;
                    if (td>0 && (td%tb)==0) {
                        td /= tb; if ((td&1)==1) d--;
                    }
                    d11 = b2-peb[k].x; d12 = b2-i;
                    td = (r-peb[k].t)-d11-d12+1-d2;
                    if (td>0 && (td%tb)==0) {
                        td /= tb; if ((td&1)==0) d++;
                    }
                    td = (r-peb[k].t-2)-d11-d12+1-d2;
                    if (td>0 && (td%tb)==0) {
                        td /= tb; if ((td&1)==0) d--;
                    }
                }
            }
            if (d==0) map[4-j][4+i] = '-';
            else if (d>0) map[4-j][4+i]= '*';
            else map[4-j][4+i] = 'o';
        }
    }
    for (i=0; i<9; i++) { 
        map[i][9] = 0;
        printf("%s\n", map[i]);
    }
    return 0;
}
