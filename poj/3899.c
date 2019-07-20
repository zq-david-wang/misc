#include<stdio.h>
#include<stdlib.h>
#include<string.h>


long long cs[64];
void build() {
    cs[0]=1; cs[1]=2;
    int i; for (i=2; i<50; i++) {
        cs[i]=cs[i-1]*2;
    }
}
long long count(char *a, int n) {
    long long c = 0;
    int i; for (i=1; i<n; i++) c+=cs[i];
    int j;
    for (i=0; i<n; i++) {
        for (j=0; j<a[i]; j++) {
            if (j!=4&&j!=7) continue;
            c += cs[n-1-i];
        }
        if (j!=4&&j!=7) break;
    }
    return c;
}
long long count1(char *a, int n, char *b, char f) {
    long long c = 0;
    int i, j, k, m;
    for (i=0; i<n; i++) {
        for (j=0; j<a[i]; j++) {
            if (j!=4&&j!=7) continue;
            for (k=n-1;k>i; k--) {
                for (m=9; m>b[n-1-k]; m--) {
                    if (m!=4&&m!=7) continue;
                    c += cs[k-(i+1)];
                }
                if (m!=4&&m!=7) break;
            }
            // 
            if (k==i && j>=b[n-1-k]) {
                if (j>b[n-1-k]) c++;
                else {
                    for (k--; k>=0; k--) { 
                        if (a[k]<b[n-1-k]) break;
                        if (a[k]>b[n-1-k]) {
                            c++; break;
                        }
                    }
                    if (k<0&&f) c++;
                }
            }
        }
        if (j!=4&&j!=7) break;
    }
    return c;
}
long long count2(char *a, int n, char *b, char f) {
    long long c = 0;
    int i, j, k, m;
    for (i=0; i<n; i++) {
        for (j=9; j>a[i]; j--) {
            if (j!=4&&j!=7) continue;
            for (k=n-1;k>i; k--) {
                for (m=0; m<b[n-1-k]; m++) {
                    if (m!=4&&m!=7) continue;
                    c += cs[k-(i+1)];
                }
                if (m!=4&&m!=7) break;
            }
            // 
            if (k==i && j<=b[n-1-k]) {
                if (j<b[n-1-k]) c++;
                else {
                    for (k--; k>=0; k--) { 
                        if (a[k]>b[n-1-k]) break;
                        if (a[k]<b[n-1-k]) { c++; break; }
                    }
                    if (k<0&&f) c++;
                }
            }
        }
        if (j!=4&&j!=7) break;
    }
    return c;
}
int main() {
    build();
    int t, ti, i, n1, n2;
    long long c1, c2, c;
    char a[64], b[64];
    scanf("%d", &t); for (ti=0; ti<t; ti++) {
        scanf("%s %s", a, b);
        n1 = strlen(a); n2 = strlen(b);
        for (i=0; i<n1; i++) a[i]-='0';
        for (i=0; i<n2; i++) b[i]-='0';
        c1 = count(a, n1); c2 = count(b, n2);
        c = c2-c1;
        for (i=0; i<n2; i++) if (b[i]!=4&&b[i]!=7) break;
        if (i==n2) c++;
        c1 = count1(a, n1, a, 1); // smaller than a, reversed to larger than or equal to a
        c2 = 0;
        if (n1==n2) {
            c2 = count1(a, n1, b, 0); // smaller than a, reversed to larger than b
        }
        c += (c1-c2);
        c1 = count2(b, n2, b, 1); c2=0;
        if (n1==n2) {
            c2 = count2(b, n2, a, 0);
        }
        c += (c1-c2);
        printf("%lld\n", c);
    }
    return 0;
}


