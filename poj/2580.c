#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char line[128];
int readline() {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        line[i++]=c;
    }
    if (i && line[i-1]=='\r') i--;
    line[i]=0;
    return i;
}
struct {
    int n, a, b, k;
} keys[1000];
char map[24][24];
char flag[24];
int queue[32], rooms[32];
int main() {
    int m, n, i, j, k, l, pk, kc, ckey, ppk, ib;
    char b[16];
    int head, tail;
    while(1) {
        readline();
        if (line[0]=='E') break;
        kc = 0; pk = -1;
        sscanf(line, "%s %d %d", b, &m, &n);
        for (i=0; i<n; i++) {
            l = readline();
            j=0; while(j<l) {
                while(line[j]==' ')j++;
                if (j==l) break;
                ib=0; while(line[j]>='0'&&line[j]<='9') { ib=ib*10+line[j]-'0'; j++; }
                k=0; while(line[j]>='A'&&line[j]<='Z') { k|= (1<<(line[j]-'A')); j++; }
                // add key i, b, k
                keys[kc].a = i; keys[kc].b=ib; keys[kc].k=k; keys[kc].n=pk; pk=kc++;
                // printf("%d->%d:%d\n", i, ib, k);
            }
        }
        for (i=0; i<n; i++) {
            rooms[i]=0;
            l = readline();
            for(j=0; j<l; j++) {
                if (line[j]<'A'||line[j]>'Z') continue;
                rooms[i] |= (1<<(line[j]-'A'));
            }
            // printf("rooms %d has key %d\n", i, rooms[i]);
        }
        //
        memset(map, 0, sizeof(map));
        for (i=0; i<n; i++) flag[i]=0; flag[m]=1;
        ckey = rooms[m];
        // printf("start with room %d, key %d, pk is %d\n", m, ckey, pk);
        while(1) {
            head=tail=0;
            k=pk; ppk=-1; while(k!=-1) {
                i=keys[k].a; j=keys[k].b;
                // printf("process %d,%d, need key %d\n", i, j, keys[k].k);
                if (map[i][j]==0 && ((~ckey)&keys[k].k)==0) {
                    // printf("connect %d with %d\n", i, j);
                    map[i][j]=map[j][i]=1;
                    if (flag[i]==1) queue[head++]=i;
                    if (flag[j]==1) queue[head++]=j;
                    // remove it
                    if (ppk==-1) pk=k;
                    else {
                        keys[ppk].n=keys[k].n;
                    }
                }
                ppk = k;
                k = keys[k].n;
            }
            if (head==0) break;
            while(tail<head) {
                i = queue[tail++];
                for (j=0; j<n; j++) {
                    if (flag[j]||map[i][j]==0) continue;
                    flag[j]=1; ckey |= rooms[j];
                    // printf("enter %d, current key %x\n", j, ckey);
                    queue[head++] = j;
                }
            }
        }
        if (flag[0]) printf("YES\n");
        else printf("NO\n");
        readline();
    } 
    return 0;
}


