#include<stdio.h>

char map[235][235];
int nei[235][235];
int neic[235];
int rnei[235][235];
int rneic[235];

int main() {
    int n, t, i, ci=0, j;
    int a, b, c;
    int i1, i2, ta, tb;
    while(1) {
        scanf("%d %d", &n, &t); if (n==0) break; ci++;
        for (i=1; i<=n; i++) { 
            for (j=1; j<=n; j++) map[i][j]=0;
            map[i][i]=1;
            neic[i]=0;
            rneic[i]=0;
        }
        c=0; for (i=0; i<t; i++) {
            scanf("%d %d", &a, &b);
            if (map[b][a]) c++;
            else {
                if (map[a][b]==0) {
                    map[a][b] = 1; nei[a][neic[a]++] = b; rnei[b][rneic[b]++] = a;
                    for (i1=0; i1<rneic[a]; i1++) {
                        ta = rnei[a][i1]; if (map[ta][b]==0) { nei[ta][neic[ta]++] = b; rnei[b][rneic[b]++] = ta; map[ta][b]=1; }
                    }
                    for (i1=0; i1<neic[b]; i1++) {
                        tb = nei[b][i1];
                        if (map[a][tb]==0) {
                            map[a][tb]=1; nei[a][neic[a]++] = tb; rnei[tb][rneic[tb]++] = a;
                            for (i2=0; i2<rneic[a]; i2++) {
                                ta = rnei[a][i2];
                                if (map[ta][tb]==0) { nei[ta][neic[ta]++] = tb; rnei[tb][rneic[tb]++] = ta; map[ta][tb]=1; }
                            }
                        }
                    }
                }
            }
        }
        printf("%d. %d\n", ci, c);
    }
    return 0;
}
