#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int mdays[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30 ,31 };
int base[12];
int mins[1004], vs[1004];
char sigs[1004];
int mycmp(const void *a, const void *b) {
    return *((const int*)a) - *((const int*)b);
}
struct { short i, j, c, ss, es; } year[1000];
int findi(int v, int n) {
    int l=0, h=n-1, m;
    while(l<=h) {
        m = (l+h)/2;
        if (vs[m]==v) return m;
        if (vs[m]>v) h=m-1;
        else l=m+1;
    }
    return -1;
}
int dp[1000][1000];
int level[1000][1000];
int dfs(int cy, int lt, int ny) {
    if (cy==ny) return 0;
    if (dp[cy][lt]!=-1)  return dp[cy][lt];
    int i, j, c1, c2, t, c, lv;
    i=year[cy].i; j=year[cy].j, c=year[cy].c;
    int r = -2;
    if (lt>=mins[i]) {
        c1 = dfs(cy+1, mins[j], ny);
        c2 = dfs(cy+1, year[cy].es, ny);
        if (year[cy].c==0) {
            // try largest smaller or equal to lt
            lv = level[cy][lt];
            t = dfs(cy+1, lv, ny); if (t>=0) { t+=1; if (r<0||r>t) r=t; }
            if (mins[j]!=lv) {
                t = c1; if (t>=0) { t+=2; if (r<0||r>t) r=t; }
            }
        } else {
            if (lt>=year[cy].ss) {
                t = c2; // dfs(cy+1, year[cy].es, ny);
                if (t>=0) { t+=c; if (r<0||r>t) r=t; }
                if (year[cy].es != mins[j]) {
                    t = c1; // dfs(cy+1, mins[j], ny);
                    if (t>=0) { t += (c+1); if (r<0||r>t) r=t; }
                }
            } else {
                t=c2; if (t>=0) { t+=(c+1); if (r<0||r>t) r=t; }
                if (year[cy].es != mins[j]) {
                    t = c1; // dfs(cy+1, mins[j], ny);
                    if (t>=0) { t += (c+2); if (r<0||r>t) r=t; }
                }
            }
        }
    }
    dp[cy][lt] = r;
    return r;
}
int main() {
    int n, i, c, ri, j, k, cn, yc, kk;
    char ts[16], sig[8], nm[32];
    char mo, d, h, mi;
    base[0]=0; for (i=1; i<12; i++) base[i]=base[i-1]+mdays[i-1];
    while(1) {
        scanf("%d", &n); if (n==0) break;
        for (i=0; i<n; i++) {
            scanf("%s %s %s", ts, nm, sig);
            mo=(ts[0]-'0')*10+ts[1]-'0';
            d=(ts[3]-'0')*10+ts[4]-'0';
            h=(ts[6]-'0')*10+ts[7]-'0';
            mi=(ts[9]-'0')*10+ts[10]-'0';
            mins[i] = (base[mo-1]+d)*24*60+h*60+mi;
            sigs[i]=0; if (sig[0]=='+')sigs[i]=1;
            vs[i]=mins[i];
        }
        for (i=0; i<n; i++) if (sigs[i]) break; 
        if (i==n) { printf("0\n"); continue; }
        ri = i;
        qsort(vs, n, sizeof(vs[0]), mycmp);
        cn=0; for (i=0; i<n; i++) {
            if (i>0&&vs[i]==vs[i-1]) continue;
            vs[cn++]=vs[i];
        }
        for (i=0; i<n; i++) mins[i]=findi(mins[i], cn);
        i=ri; yc=0;
        for (; i<n; ) {
            for (j=i+1; j<n; j++) if (mins[j]<=mins[j-1]) break; j--;
            //[i, j] a year
            year[yc].i = i; year[yc].j = j; c=0;
            for (k=i; k<=j; k++) { if (sigs[k]) c++; }
            if (c) {
                for (k=i; k<=j; k++) if (sigs[k]) break; year[yc].ss=mins[k];
                for (k=j; k>=i; k--) if (sigs[k]) break; year[yc].es=mins[k];
            } else year[yc].es = mins[j];
            // level it
            for (k=i; k<j; k++) {
                for (kk=mins[k]; kk<mins[k+1]; kk++) level[yc][kk]=mins[k];
            }
            for (kk=mins[j]; kk<cn; kk++) level[yc][kk]=mins[j];
            year[yc].c = c; yc++;
            i = j+1;
        }
        for (i=0; i<yc; i++) memset(dp[i], 0xff, (cn+1)*sizeof(dp[i][0]));
        i = dfs(0, cn, yc);
        // printf("%d years of record uncovered\n", yc);
        printf("%d\n", i);
    }
    return 0;
}
