#include<stdio.h>

char cows[30000];
char nline[30001];
int main() {
    int n, i, j, k;
    char b[8], *p, c;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%s", b);
        cows[i] = b[0];
    }
    i=0; j = n-1; k = 0;
    int ii, jj ,nii, njj;
    while(i<=j) {
        if (cows[i]<cows[j]) nline[k++] = cows[i++];
        else if (cows[i]>cows[j]) nline[k++] = cows[j--];
        else {
            for (ii=i+1; ii<j; ii++) if (cows[ii]!=cows[i]) break;
            if (ii==j) {
                while(i<=j) nline[k++] = cows[i++];
                continue;
            }
            for (jj=j-1; jj>i; jj--) if (cows[jj]!=cows[j]) break;
            if (cows[ii]>cows[i] && cows[jj]>cows[j]) {
                while(i<ii) nline[k++] = cows[i++];
                while(j>jj) nline[k++] = cows[j--];
            } else if (cows[ii]>cows[i] && cows[jj]<cows[j]) {
                while(j>jj) nline[k++] = cows[j--];
            } else if (cows[ii]<cows[i] && cows[jj]>cows[j]) {
                while(i<ii) nline[k++] = cows[i++];
            } else {
                // printf("small %d->%d, %d->%d\n", i, ii, jj, j);
                if ((ii-i)<(j-jj)) {
                    while(i<ii) nline[k++] = cows[i++];
                    continue;
                }
                if ((ii-i) > (j-jj)) {
                    while(j>jj) nline[k++] = cows[j--];
                    continue;
                }
                if (cows[ii]<cows[jj]) {
                    while(i<ii) nline[k++] = cows[i++];
                } else if (cows[ii]>cows[jj]) {
                    while(j>jj) nline[k++] = cows[j--];
                } else {
                    //
                    nii = ii+1; njj = jj-1;
                    while(nii<=njj) {
                        if (cows[nii] != cows[njj]) break;
                        nii++; njj--;
                    } 
                    if (nii>njj) {
                        while(i<ii) nline[k++] = cows[i++];
                    } else {
                        if (cows[nii]<cows[njj]) {
                            while(i<ii) nline[k++] = cows[i++];
                        } else {
                            while(j>jj) nline[k++] = cows[j--];
                        }
                    }
                }
            }
        }
    }
    p = nline;
    k = n;
    while(k>80) {
        c = p[80]; p[80] =0;
        printf("%s\n", p);
        p[80] = c;
        k -= 80;
        p += 80;
    }
    if (k) {
        p[k] = 0;
        printf("%s\n", p);
    }
    return 0;
}
