#include<stdio.h>
#include<string.h>

char map[10000];

void build() {
    memset(map, 0, sizeof(map));
    int i,j; for (i=2; i<sizeof(map); i++) {
        if (map[i]==1) continue;
        for (j=i+i; j<sizeof(map); j+=i) map[j]=1;
    }
}

short dis[10000];
short queue[10000];
int main() {
    int tc, ti, a, b, head, tail, v, i, j;
    char n[4], c;
    build();
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%d %d", &a, &b);
        memset(dis, 0xff, sizeof(dis));
        head=tail=0; queue[head++] =a; dis[a]=0;
        while(tail<head) {
            a = queue[tail++];
            if (a==b) break;
            n[0]=a%10;
            n[1]=(a/10)%10;
            n[2]=(a/100)%10;
            n[3]=(a/1000)%10;
            for (i=0; i<4; i++) {
                c = n[i];
                for (j=0; j<=9; j++) {
                    if (i==3&&j==0) continue;
                    n[i]=j;
                    v=n[0]+n[1]*10+n[2]*100+n[3]*1000; 
                    if (dis[v]!=-1) continue;
                    if (map[v]) continue;
                    dis[v] = dis[a]+1;
                    if (v==b) break;
                    queue[head++] = v;
                }
                if (j<9) break;
                n[i]=c;
            }
            if (i<4) break;
        }
        printf("%d\n", dis[b]);
    }
    return 0;
}
