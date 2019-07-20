#include<stdio.h>
#include<string.h>

int ip[1000000];
int main() {
    char buf[8];
    scanf("%s", buf);
    int i, v=0;
    for (i=0; i<6; i++) {
        if (buf[i]==0) break;
        v=v*10+buf[i]-'0';
    }
    int  mv, cv, nv, ncv;
    memset(ip, 0xff, sizeof(ip));
    mv = v/10; mv %= 10000;
    cv = v;
    ip[v] = 0;
    i=0;
    for (;;) {
        i++;
        ncv = mv*mv;
        ncv %= 1000000;
        // printf("round %d: cv %d mv %d, ncv %d\n", i, cv, mv, ncv);
        if (ip[ncv]!=-1) {
            printf("%d %d %d\n", ncv, i-ip[ncv], i);
            break;
        }
        cv = ncv;
        ip[cv] = i;
        mv = cv/10; mv %= 10000;
    }

    return 0;
}
