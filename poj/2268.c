#include<stdio.h>
#include<string.h>

char names[20][32];
int findname(int n, char *w) {
    int i; for (i=0; i<n; i++) if (strcmp(names[i], w)==0) return i;
    return -1;
}
char namea[32], nameb[32];
char score[20], gamec[20][20], best[20], worst[20];
struct {char a, b;}games[32];
int gc, gn;
void dfs(int s) {
    if (s==gc) {
        int i, j, c; for (i=0; i<gn; i++) {
            c=0; for (j=0; j<gn; j++) if (score[j]>score[i]) c++;
            c++; if (best[i]>c) best[i]=c;
            c=0; for (j=0; j<gn; j++) if (score[j]<score[i]) c++;
            c=gn-c; if (worst[i]<c) worst[i]=c;
        }
        return;
    }
    int a, b;
    a=games[s].a; b=games[s].b;
    score[a]+=3; dfs(s+1); score[a]-=3;
    score[b]+=3; dfs(s+1); score[b]-=3;
    score[a]+=1; score[b]+=1; dfs(s+1); score[b]-=1; score[a]-=1;
}
int main() {
    int n, i, tc=0, m, j;
    int sa, sb, ia, ib;
    while(1) {
        scanf("%d", &n); if (n==0) break; tc++;
        for (i=0; i<n; i++) scanf("%s", names[i]);
        scanf("%d", &m);
        memset(gamec, 0, sizeof(gamec));
        for (i=0; i<n; i++) { score[i]=0; best[i]=n+1; worst[i]=0; }
        for (i=0; i<m; i++) {
            scanf("%s %s %d %d", namea, nameb, &sa, &sb);
            ia = findname(n, namea);
            ib = findname(n, nameb);
            gamec[ia][ib]++; gamec[ib][ia]++;
            if (sa>sb) { score[ia] += 3; }
            else if (sa==sb) { score[ia]+=1; score[ib]+=1; }
            else score[ib] += 3;
        }
        gc=0; for (i=0; i<n; i++) for (j=i+1; j<n; j++) {
            if (gamec[i][j]==2) continue;
            games[gc].a=i; games[gc].b=j; gc++;
            if (gamec[i][j]==1) continue;
            games[gc].a=i; games[gc].b=j; gc++;
        }
        gn=n;
        dfs(0);
        printf("Group #%d\n", tc);
        for (i=0; i<n; i++) printf("%s %d-%d\n", names[i], best[i], worst[i]);
        printf("\n");
    }
    
    return 0;
}
