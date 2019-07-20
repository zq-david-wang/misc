#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char ds[] = {
    126,
    48,
    109,
    121,
    51,
    91,
    95,
    112,
    127,
    123,
};
short map[8];
int main() {
    int ct, ci, i, j, v, m, h;
    char ts[8], vs[8], a, b;
    scanf("%d", &ct); for (ci=0; ci<ct; ci++) {
        for (i=0; i<8; i++) {
            scanf("%s", ts);
            v=0; for (j=0; j<7; j++) v=v*2+ts[j]-'0';
            vs[i]=v;
        }
        for (i=0; i<4; i++) {
            a=vs[i]; b=vs[i+4];
            map[i]=0; map[i+4]=0;
            for (j=0; j<10; j++) {
                if (i==0&&j==0) {
                    if (a==0) map[i]|=(1<<j);
                    continue;
                }
                if (a&(~ds[j])) continue;
                if (ds[j]&(~a)&b) continue;
                map[i] |= (1<<j);
                // printf("%d could be %d\n", i, j);
            }
            for (j=0; j<10; j++) {
                if (i==0&&j==0) {
                    if (b==0) map[i+4]|=(1<<j);
                    continue;
                }
                if (b&(~ds[j])) continue;
                if (ds[j]&(~b)&a) continue;
                map[i+4] |= (1<<j);
                // printf("%d could be %d\n", i+4, j);
            }
        }
        // check hours
        for (i=0; i<3; i++) {
            if ((map[4]&(1<<i))==0) continue;
            for (j=0; j<10; j++) {
                if (j==0&&i==0) continue;
                if (map[5]&(1<<j)) break;
            }
            break;
        }
        h=i*10+j;
        for (i=0; i<6; i++) {
            if ((map[6]&(1<<i))==0) continue;
            for (j=0; j<10; j++) {
                if (map[7]&(1<<j)) break;
            }
            break;
        }
        m=i*10+j;
        printf("%d:%02d\n", h, m);
    }
    return 0;
}


