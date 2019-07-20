#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char map[16][4];
char *ns = "A23456789TJQKA";
char *ss = "shdc";
typedef struct { char n, s; } CNode;
CNode board[5];
int main() {
    int tc, ti, i, j, k, ii, jj;
    char card[8], bc, c, bbc, mc, sc[8], nc[16], ik[6], rc, oc[16];
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        memset(map, 0 ,sizeof(map));
        for (i=0; i<=13; i++) nc[i]=0;
        for (i=0; i<5; i++) {
            scanf("%s", card);
            for (j=0; j<13; j++) if (ns[j]==card[0]) break;
            for (k=0; k<4; k++) if (ss[k]==card[1]) break;
            map[j][k]=1; if (j==0) map[13][k]=1;
            for (ii=i-1; ii>=0; ii--) {
                if (board[ii].n>j) break;
                board[ii+1]=board[ii];
            }
            ii++; board[ii].n=j; board[ii].s=k;
            nc[j]++; if (j==0) nc[13]++;
        }
        for (i=0; i<=13; i++) oc[i]=0;
        for (i=0; i<2; i++) {
            scanf("%s", card);
            for (j=0; j<13; j++) if (ns[j]==card[0]) break;
            for (k=0; k<4; k++) if (ss[k]==card[1]) break;
            map[j][k]=2; if (j==0) map[13][k]=2;
            oc[j]++; if (j==0) oc[13]++;
        }
        // try Royal Flush
        for (i=0;i<4;i++) {
            bc=0; for (j=9; j<=12; j++) {
                if (map[j][i]==2) break;
                if (map[j][i]==1) bc++;
            }
            if (j<=12) continue;
            if (map[0][i]==2) continue;
            if (map[0][i]==1) bc++;
            if (bc>=3) break;
        }
        if (i<4) { printf("A%c K%c Q%c J%c T%c ROYAL FLUSH\n", ss[i], ss[i], ss[i], ss[i], ss[i]); continue; }
        // Straight Flush
        for (i=0; i<4; i++) {
            bc=0;
            if (map[0][i]==1||map[0][i]==0) {
                if (map[0][i]==1) bc++;
                for (j=12; j>=9; j--) {
                    if (map[j][i]==2) break;
                    if (map[j][i]==1) bc++;
                }
                if (j<9&&bc>=3) { j+=5; break; }
            }
            for (k=12; k>=4; k--) {
                bc=0;
                for (j=0; j<5; j++) {
                    if (map[k-j][i]==2) break;
                    if (map[k-j][i]==1) bc++;
                }
                if (j==5&&bc>=3) break;
            }
            if (k>=4) { j=k; break; }
        }
        if (i<4) {
            if (j==13) { printf("A%c", ss[i]); j--; }
            else if (j==4) printf("A%c", ss[i]);
            else { printf("%c%c", ns[j], ss[i]); j--; }
            for (k=0; k<4; k++) printf(" %c%c", ns[j-k], ss[i]);
            printf(" STRAIGHT FLUSH\n");
            continue;
        }
        // Four of a Kind
        bc=0;
        for (i=0; i<4; i++){
            if (map[0][i]==2) break;
            if (map[0][i]==1) bc++;
        }
        if (i==4&&bc>=2) {
            for (j=0; j<4; j++) printf("A%c ", ss[j]);
            printf("K* FOUR OF A KIND\n");
            continue;
        }
        for (j=12; j>=1; j--) {
            bc=0;
            for (i=0; i<4; i++) {
                if (map[j][i]==2) break;
                if (map[j][i]==1) bc++;
            }
            if (i==4&&bc>=2) break;
        }
        if (j>=1) {
            if (bc==2) {
                ii=0; while(board[ii].n==j)ii++;
                c = ss[board[ii].s];
                if (ii<4&&board[ii+1].n==board[ii].n) c='*';
                printf("%c%c ", ns[board[ii].n], c);
            } else {
                printf("A* ");
            }
            for (i=0; i<4; i++) printf("%c%c ", ns[j], ss[i]);
            printf("FOUR OF A KIND\n");
            continue;
        }
        // Full House
        for (j=13; j>=1; j--) {
            bc=0; mc=0;
            for (k=0; k<4; k++) {
                if (map[j][k]==2) mc++;
                if (map[j][k]==1) bc++;
            }
            if (bc>=1 && mc<=1) {
               for (jj=13; jj>=1; jj--) {
                   if (jj==j) continue;
                   bbc=bc; mc=0;
                   for (k=0; k<4; k++) {
                       if (map[jj][k]==1) bbc++;
                       if (map[jj][k]==2) mc++;
                   }
                   if (bbc>=3) {
                       if (j>=jj) {
                           bbc=0;
                           for (k=0; k<4; k++) {
                               if (map[j][k]==2) continue;
                               printf("%c%c ", ns[j], ss[k]);
                               bbc++; if (bbc==3) break;
                           }
                           if (nc[jj]>2||oc[jj]+nc[jj]<2) printf("%c* %c* ", ns[jj], ns[jj]);
                           else {
                               bbc=0;
                               for (k=0; k<4; k++) {
                                   if (map[jj][k]==2) continue;
                                   printf("%c%c ", ns[jj], ss[k]);
                                   bbc++; if (bbc==2) break;
                               }
                           }
                       } else {
                           if (nc[jj]>2||oc[jj]+nc[jj]<2) printf("%c* %c* ", ns[jj], ns[jj]);
                           else {
                               bbc=0;
                               for (k=0; k<4; k++) {
                                   if (map[jj][k]==2) continue;
                                   printf("%c%c ", ns[jj], ss[k]);
                                   bbc++; if (bbc==2) break;
                               }
                           }
                           bbc=0;
                           for (k=0; k<4; k++) {
                               if (map[j][k]==2) continue;
                               printf("%c%c ", ns[j], ss[k]);
                               bbc++; if (bbc==3) break;
                           }
                       }
                       printf("FULL HOUSE\n");
                       break;
                   }
               } 
               if (jj>=1) break;
            }
        }
        if (j>=1) continue;
        // Flush
        for (i=0; i<4; i++) { sc[i] = 0; }
        for (i=0; i<5; i++) {
            sc[board[i].s]++;
            if (sc[board[i].s]>=3) break;
        }
        if (i<5) {
            i=board[i].s;
            bbc = 0; bc=2;
            for (j=13; j>=1; j--) {
                if (map[j][i]==2) continue;
                if (map[j][i]==0) {
                    if (bc==0) continue;
                    bc--;
                }
                printf("%c%c ", ns[j], ss[i]);
                bbc++; if (bbc==5) break;
            }
            printf("FLUSH\n");
            continue;
        }
        // Straight
        for (j=0; j<=13; j++) nc[j]=0;
        for (k=0; k<5; k++) { nc[board[k].n]++; if (board[k].n==0) nc[13]++; }
        for (j=13; j>=4; j--) {
            bc=0;
            for (k=0; k<5; k++) {
                if (nc[j-k]) bc++;
            }
            if (bc<3) continue;
            bbc = 2;
            for (k=0; k<5; k++) ik[k]=k;
            if (j==4) {
                ik[0]=4; for (k=1; k<5; k++) ik[k]=k-1;
            }
            rc = 5;
            for (ii=0; ii<5; ii++) {
                k = ik[ii];
                if (nc[j-k]==0|| bc+bbc>rc) printf("%c* ", ns[j-k]);
                else {
                    for (i=0; i<4; i++) if (map[j-k][i]==1) break;
                    printf("%c%c ", ns[j-k], ss[i]);
                }
                rc--;
                if (nc[j-k]) bc--;
                if (nc[j-k]==0) bbc--;
            }
            printf("STRAIGHT\n");
            break;
        }
        if (j>=4) continue;
        // Three of a Kind
        for (j=13; j>=1; j--) {
            if (nc[j]==0) continue;
            if (oc[j]==2) continue;
            break;
        }
        if (nc[j]==1) {
            bc=0;
            for (i=0; i<5; i++) {
                if (bc>=2) break;
                if (board[i].n<=j) continue;
                printf("%c%c ", ns[board[i].n], ss[board[i].s]);
                bc++;
            }
            bbc = 2;
            for (i=0; i<4; i++) {
                if (map[j][i]==2) continue;
                if (map[j][i]==0) {
                    if (bbc==0) continue;  bbc--;
                    if (oc[j]==0) printf("%c* ", ns[j]);
                    else printf("%c%c ", ns[j], ss[i]);
                }
                else printf("%c%c ", ns[j], ss[i]);
            }
            for (i=0; i<5; i++) {
                if (bc>=2) break;
                if (board[i].n>=j) continue;
                printf("%c%c ", ns[board[i].n], ss[board[i].s]);
                bc++;
            }
        } else {
            // oc[j]==1
            bc = 0;
            if (j<13) { printf("A* "); }
            for (i=0; i<5; i++) {
                if (board[i].n<=j) continue;
                printf("%c%c ", ns[board[i].n], ss[board[i].s]);
                bc++;
                break;
            }
            for (i=0; i<4; i++) {
                if (map[j][i]==2) continue;
                printf("%c%c ", ns[j], ss[i]);
            }
            if (j==13) { printf("K* "); }
            if (bc==0) for (i=0; i<5; i++) {
                if (board[i].n>=j) continue;
                printf("%c%c ", ns[board[i].n], ss[board[i].s]);
                break;
            }
        }
        printf("THREE OF A KIND\n");
    }
    return 0;
}


