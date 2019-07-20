#include<stdio.h>
#include<string.h>

char flag[1048576];
int queue[1048576];
int main() {
    int i, s=0, b, d, m, ns;
    for (i=0; i<20; i++) {
        scanf("%d", &b);
        s = s*2+b;
    }
    int qhead=0, qtail=0;
    queue[qhead++] = s;
    memset(flag, 0, sizeof(flag));
    flag[s] = 1;
    while(qtail<qhead) {
        b = queue[qtail++];
        s = b&0xfffff;
        d = b>>20;
        if (s==0) break;
        d++;
        ns = s^0x3;
        if (ns==0) break;
        if (flag[ns] == 0) { flag[ns] = 1; queue[qhead++] = (d<<20) | ns; }
        ns = s^0xc0000;
        if (ns==0) break;
        if (flag[ns] == 0) { flag[ns] = 1; queue[qhead++] = (d<<20) | ns; }
        m = 0x7;
        for (i=1; i<=18; i++) {
            ns = s^m;
            if (ns==0) break;
            if (flag[ns] == 0) { flag[ns] = 1; queue[qhead++] = (d<<20) | ns; }
            m <<= 1;
        }
        if (i<=18) break;
    }
    printf("%d\n", d);
    return 0;
}
