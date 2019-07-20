#include<stdio.h>
#include<string.h>

char map[12][12];
struct { char r, c; } powns[12];
char steps[8][2] = {
    {1, 2},
    {1, -2},
    {2, 1},
    {2, -1},
    {-1, 2},
    {-1, -2},
    {-2, 1},
    {-2, -1}
};
char block[8][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {1, 0},
    {0, 1},
    {0, -1},
    {-1, 0},
    {-1, 0},
};
int try(int r, int c, int n) {
    // printf("try %d,%d,%d\n", r, c, n);
    int ri, ci, j, d, k, cc, nr, nc;
    int i; for (i=0; i<n; i++) {
       ri=powns[i].r; ci=powns[i].c; 
       if (map[ri][ci]==1) continue; // taken by 
       if (map[ri][ci]=='G') {
            if (ci != c) continue;
            for (j=r+1; j<ri; j++) if (map[j][ci]) break;
            if (j>=ri) return 1;
       } else if (map[ri][ci]=='R') {
           if (ri==r) {
               d=1; if (ci>c) d=-1;
               for (j=ci+d;;j+=d) {
                   if (j==c) break;
                   if (map[r][j]) break;
               }
               if (j==c) return 1;
           }
           if (ci==c) {
               d=1; if (ri>r) d=-1;
               for (j=ri+d;;j+=d) {
                   if (j==r) break;
                   if (map[j][c]) break;
               }
               if (j==r) return 1;
           }

       } else if (map[ri][ci]=='H') {
           for (k=0; k<8; k++) {
               nr = ri+steps[k][0]; nc = ci+steps[k][1];
               if (nr != r|| nc != c) continue;
               nr = ri+block[k][0]; nc = ci+block[k][1];
               if (map[nr][nc]) continue;
               return 1;
           }

       } else if (map[ri][ci]=='C') {
            if (r==ri) {
                cc=0; d=1; if (ci>c) d=-1;
                for (j=ci+d;;j+=d) {
                    if (j==c) break;
                    if (map[r][j])cc++;
                }
                if (cc==1) return 1;
            }
            if (c==ci) {
                cc=0; d=1; if (ri>r) d=-1;
                for (j=ri+d;;j+=d) {
                    if (j==r) break;
                    if (map[j][c])cc++;
                }
                if (cc==1) return 1;
            }
       }
    }
    return 0;
}
int main() {
    int n, r, c, i, ri, ci;
    char b[8], t, s;
    while(1) {
        scanf("%d %d %d", &n, &r, &c); if (r==0) break;
        memset(map, 0, sizeof(map));
        for (i=0; i<n; i++) {
            scanf("%s %d %d", b, &ri, &ci);
            powns[i].r = ri; powns[i].c = ci;
            map[ri][ci]=b[0];
        }
        if (r>1) { t=map[r-1][c]; map[r-1][c]=1; s=try(r-1, c, n); map[r-1][c]=t;  if (s==0) { printf("NO\n"); continue; }}
        if (r<3) { t=map[r+1][c]; map[r+1][c]=1; s=try(r+1, c, n); map[r+1][c]=t;  if (s==0) { printf("NO\n"); continue; }}
        if (c>4) { t=map[r][c-1]; map[r][c-1]=1; s=try(r, c-1, n); map[r][c-1]=t;  if (s==0) { printf("NO\n"); continue; }}
        if (c<6) { t=map[r][c+1]; map[r][c+1]=1; s=try(r, c+1, n); map[r][c+1]=t;  if (s==0) { printf("NO\n"); continue; }}
        printf("YES\n");
    }
    return 0;
}
