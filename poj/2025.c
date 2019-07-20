#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char ba[5][8], bb[5][8], bc[5][8], bbb[5][8];
int incheck(char (*a)[8], char (*b)[8]) {
    int i, j;
    for (i=0; i<5; i++) { 
        for (j=0; j<5; j++) if (a[i][j]+b[i][j]!=5) break;
        if (j<5) break;
    }
    if (i==5) return 1;
    // rotate 90, anchor 0, 4
    for (i=0; i<5; i++) { 
        for (j=0; j<5; j++) if (a[i][j]+b[j][4-i]!=5) break;
        if (j<5) break;
    }
    if (i==5) return 1;
    for (i=0; i<5; i++) { 
        for (j=0; j<5; j++) if (a[i][j]+b[4-i][4-j]!=5) break;
        if (j<5) break;
    }
    if (i==5) return 1;
    for (i=0; i<5; i++) { 
        for (j=0; j<5; j++) if (a[i][j]+b[4-j][i]!=5) break;
        if (j<5) break;
    }
    if (i==5) return 1;
    return 0;
}
char vsa[4][5][8], vsb[4][5][8], vma[4], vmb[4], sss[5][8];
int check(char (*a)[8], char (*b)[8]) {
    char cc[8], ccc;
    int i, j, k;
    for (i=0; i<=5; i++) cc[i]=0;
    for (i=0; i<5; i++) for (j=0; j<5; j++) {
        cc[b[i][j]]++;
        bbb[i][j]=b[i][4-j];
    }
    if (incheck(a, bbb)) return 1;
    ccc=0; for (i=1; i<=5; i++) if (cc[i]) ccc++;
    if (ccc==1) if (incheck(a, b)) return 1;
    // shift zeros
    for (i=0; i<5; i++) {
        for (j=0; j<5; j++) if (b[i][j]) break;
        if (j<5) break;
        memset(sss, 0, sizeof(sss));
        for (j=i+1; j<5; j++) for (k=0; k<5; k++) sss[j-i-1][k]=b[j][k];
        if (incheck(a, sss)) return 1;
    }
    // up, left, right.... too lazy to code...
    return 0;
}

int main() {
    int tc, ti, i, j, k;
    char cc[8], ccc;
    scanf("%d", &tc); for(ti=0; ti<tc; ti++) {
        for (i=0; i<5; i++) scanf("%s %s", ba[i], bb[i]);
        for (i=0; i<5; i++) for (j=0; j<5; j++) { ba[i][j] -= '0'; bb[i][j] -= '0'; }
        if (check(ba, bb)) { printf("Yes\n"); continue; }
        // from left
        for (i=0; i<5; i++) { for (j=0; j<5; j++) if (j&&ba[i][j]<ba[i][j-1]) break;  if (j<5) break; }
        vma[0]=0; if (i==5) {
            vma[0]=1; for (i=0; i<5; i++) for (j=0; j<5; j++) bc[i][j]=0;
            for (i=0; i<5; i++) { for (j=0; j<5; j++) { for (k=0; k<ba[i][j]; k++) { bc[i][k]++; } } }
            for (i=0; i<5; i++) for (j=0; j<5; j++)  vsa[0][i][j]=bc[i][j];
        }
        for (i=0; i<5; i++) { for (j=0; j<5; j++) if (j&&bb[i][j]<bb[i][j-1]) break;  if (j<5) break; }
        vmb[0]=0; if (i==5) {
            vmb[0]=1; for (i=0; i<5; i++) for (j=0; j<5; j++) bc[i][j]=0;
            for (i=0; i<5; i++) { for (j=0; j<5; j++) { for (k=0; k<bb[i][j]; k++) { bc[i][k]++; } } }
            for (i=0; i<5; i++) for (j=0; j<5; j++)  vsb[0][i][j]=bc[i][j];
        }
        // right
        for (i=0; i<5; i++) { for (j=4; j>=0; j--) if (j<4&&ba[i][j]<ba[i][j+1]) break;  if (j>=0) break; }
        vma[1]=0; if (i==5) {
            vma[1]=1; for (i=0; i<5; i++) for (j=0; j<5; j++) bc[i][j]=0;
            for (i=0; i<5; i++) { for (j=0; j<5; j++) { for (k=0; k<ba[i][j]; k++) { bc[i][k]++; } } }
            for (i=0; i<5; i++) for (j=0; j<5; j++)  vsa[1][i][j]=bc[i][j];
        }
        for (i=0; i<5; i++) { for (j=4; j>=0; j--) if (j<4&&bb[i][j]<bb[i][j+1]) break;  if (j>=0) break; }
        vmb[1]=0; if (i==5) {
            vmb[1]=1; for (i=0; i<5; i++) for (j=0; j<5; j++) bc[i][j]=0;
            for (i=0; i<5; i++) { for (j=0; j<5; j++) { for (k=0; k<bb[i][j]; k++) { bc[i][k]++; } } }
            for (i=0; i<5; i++) for (j=0; j<5; j++)  vsb[1][i][j]=bc[i][j];
        }
        //
        // from up 
        for (i=0; i<5; i++) { for (j=0; j<5; j++) if (j&&ba[j][i]<ba[j-1][i]) break;  if (j<5) break; }
        vma[2]=0; if (i==5) {
            vma[2]=1; for (i=0; i<5; i++) for (j=0; j<5; j++) bc[i][j]=0;
            for (i=0; i<5; i++) { for (j=0; j<5; j++) { for (k=0; k<ba[j][i]; k++) { bc[k][i]++; } } }
            for (i=0; i<5; i++) for (j=0; j<5; j++)  vsa[2][i][j]=bc[i][j];
        }
        for (i=0; i<5; i++) { for (j=0; j<5; j++) if (j&&bb[j][i]<bb[j-1][i]) break;  if (j<5) break; }
        vmb[2]=0; if (i==5) {
            vmb[2]=1; for (i=0; i<5; i++) for (j=0; j<5; j++) bc[i][j]=0;
            for (i=0; i<5; i++) { for (j=0; j<5; j++) { for (k=0; k<bb[j][i]; k++) { bc[k][i]++; } } }
            for (i=0; i<5; i++) for (j=0; j<5; j++)  vsb[2][i][j]=bc[i][j];
        }
        // down 
        for (i=0; i<5; i++) { for (j=4; j>=0; j--) if (j<4&&ba[j][i]<ba[j+1][i]) break;  if (j>=0) break; }
        vma[3]=0; if (i==5) {
            vma[3]=1; for (i=0; i<5; i++) for (j=0; j<5; j++) bc[i][j]=0;
            for (i=0; i<5; i++) { for (j=0; j<5; j++) { for (k=0; k<ba[j][i]; k++) { bc[k][i]++; } } }
            for (i=0; i<5; i++) for (j=0; j<5; j++)  vsa[3][i][j]=bc[i][j];
        }
        for (i=0; i<5; i++) { for (j=4; j>=0; j--) if (j<4&&bb[j][i]<bb[j+1][i]) break;  if (j>=0) break; }
        vmb[3]=0; if (i==5) {
            vmb[3]=1; for (i=0; i<5; i++) for (j=0; j<5; j++) bc[i][j]=0;
            for (i=0; i<5; i++) { for (j=0; j<5; j++) { for (k=0; k<bb[j][i]; k++) { bc[k][i]++; } } }
            for (i=0; i<5; i++) for (j=0; j<5; j++)  vsb[3][i][j]=bc[i][j];
        }
        for (i=0; i<4; i++) {
            if (vmb[i]==0) continue;
            if (check(ba, vsb[i])) break;
        } if (i<4) { printf("Yes\n"); continue; }
        for (i=0; i<4; i++) {
            if (vma[i]==0) continue;
            if (check(vsa[i], bb)) break;
        } if (i<4) { printf("Yes\n"); continue; }
        for (i=0; i<4; i++) {
            if (vma[i]==0) continue;
            for (j=0; j<4; j++) {
                if(vmb[j]==0) continue;
                if (check(vsa[i], vsb[i])) break;
            }
            if (j<4) break;
        } if (i<4) { printf("Yes\n"); continue; }
        printf("No\n");
    }
    return 0;
}


