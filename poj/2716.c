#include<stdio.h>

char endl[128];;
short ima[256*256][2];
short imb[9*9][2];
short imc[256*256][2];
int imac, imbc, imcc;
char map[258][258];
char imap[258][258];
char omap[258][258];
char lins[16];
int main() {
    int m, n, i, j, s, ic=0, k;
    int a, b;
    char *line;
    for (i=0; i<75; i++) endl[i]='='; endl[i]=0;
    while(1) {
        scanf("%d %d %d", &m, &n, &s); if (m==0) break; ic++;
        imac=0; for (i=1; i<=m; i++) {
            scanf("%s", imap[i]+1); line = imap[i]+1;
            for (j=0; j<n; j++) {
                if (line[j]=='*') {
                    ima[imac][0]=i; ima[imac][1]=j+1; imac++;
                }
            }
        }
        imbc=0; for (i=-s; i<=s; i++) {
            scanf("%s", lins);
            for (j=0; j<s+s+1; j++) { 
                if (lins[j]=='*') { imb[imbc][0]=i; imb[imbc][1]=j-s; imbc++; }
            }
        }
        if (ic>1) printf("%s\n", endl);
        printf("Case %d\n", ic);
        ////////////
        for (i=1; i<=m; i++) {
            for (j=1; j<=n; j++) map[i][j]=omap[i][j]='.';
            map[i][j]=omap[i][j]=0;
        }
        imcc=0; for (i=1; i<=m; i++) for (j=1; j<=n; j++) {
            for (k=0; k<imbc; k++) {
                a = i+imb[k][0]; if (a<1||a>m) break;
                b = j+imb[k][1]; if (b<1||b>n) break;
                if (imap[a][b]=='.') break;
            }
            if (k==imbc) { imc[imcc][0]=i; imc[imcc][1]=j; imcc++; }
        }
        for (i=0; i<imcc; i++) {
            for (j=0; j<imbc; j++) {
                a = imc[i][0]+imb[j][0];
                if (a<1||a>m) continue;
                b = imc[i][1]+imb[j][1];
                if (b<1||b>n) continue;
                omap[a][b]='*';
            }
        }
        printf("\n");
        for (i=1; i<=m; i++) printf("%s\n", omap[i]+1);
        ////////////
        for (i=1; i<=m; i++) {
            for (j=1; j<=n; j++) map[i][j]=omap[i][j]='.';
            map[i][j]=omap[i][j]=0;
        }
        imcc=0; for (i=0; i<imac; i++) {
            for (j=0; j<imbc; j++) {
                a = ima[i][0]+imb[j][0];
                if (a<1||a>m) continue;
                b = ima[i][1]+imb[j][1];
                if (b<1||b>n) continue;
                if (map[a][b]=='.') {
                    map[a][b]='*';
                    imc[imcc][0]=a; imc[imcc][1]=b; imcc++;
                }
            }
        }
        for (i=1; i<=m; i++) for (j=1; j<=n; j++) {
            for (k=0; k<imbc; k++) {
                a = i+imb[k][0]; if (a<1||a>m) break;
                b = j+imb[k][1]; if (b<1||b>n) break;
                if (map[a][b]=='.') break;
            }
            if (k==imbc) { omap[i][j]='*'; }
        }
        //
        printf("\n");
        for (i=1; i<=m; i++) printf("%s\n", omap[i]+1);

    }
    return 0;
}
