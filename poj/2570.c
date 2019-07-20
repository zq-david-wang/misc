#include<stdio.h>
#include<string.h>

typedef struct _T {
    struct _T *n;
    short b;
    char cy[26];
}ENode;
ENode pool[201*200];
ENode *nei[201];
int pc;
char buf[80];
char flag[201];
char dp[201][201][26];
char cflag[201];
short queue[201];
int main() {
    int n, i, a, b;
    int j, c, sc;
    int head, tail;
    char rb[32];
    ENode *p;
    while(1) {
        scanf("%d", &n);
        if (n==0) break;
        pc = 0;
        for (i=1; i<=n; i++) nei[i]=NULL;
        while(1) {
            scanf("%d %d", &a, &b);
            if (a==0&&b==0) break;
            scanf("%s", buf);
            p = &pool[pc++]; p->b=b; p->n=nei[a]; nei[a]=p;
            for (i=0; i<26; i++) p->cy[i]=0;
            i=0; while(buf[i]!=0) { p->cy[buf[i]-'a']=1; i++; }
        }
        for (i=1; i<=n; i++) cflag[i]=0;
        memset(dp, 0, sizeof(dp));
        while(1) {
            scanf("%d %d", &a, &b);
            if (a==0&&b==0) break;
            if (cflag[a]==0) {
                for (i=0; i<26; i++) {
                    for (j=1; j<=n; j++) flag[j]=0;
                    flag[a] = 1;
                    head=tail=0;
                    queue[head++] = a;
                    while(tail<head) {
                        j = queue[tail++];
                        p = nei[j];
                        while(p!=NULL) {
                            if (flag[p->b]==0&&p->cy[i]) {
                                flag[p->b] = 1;
                                queue[head++] = p->b;
                            }
                            p = p->n;
                        }
                    }
                    for (j=0; j<tail; j++) dp[a][queue[j]][i]=1;
                }
                cflag[a]=1;
            }
            sc = 0;
            for (i=0; i<26; i++) {
                if (dp[a][b][i]) rb[sc++] = i+'a';
            }
            if (sc==0) rb[sc++] = '-';
            rb[sc] = 0;
            printf("%s\n", rb);
        }
        printf("\n");
    }
    return 0;
}
