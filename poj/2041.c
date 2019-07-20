#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main() {
    int n,i, j, k, m;
    char mr[16], ms[32], c, t;
    scanf("%d", &n); for (i=0; i<n; i++) {
        scanf("%s %s", mr, ms);
        j=0; while(mr[j])j++;
        m=0; while(ms[m])m++;
        for (j--; j>=0; j--) {
            c = mr[j];
            if (c=='M') {
                for (k=0; k<m; k++) { if (ms[k]=='9') ms[k]='0'; else if (ms[k]>='0'&&ms[k]<'9') ms[k]++; }
            } else if (c=='P') {
                for (k=0; k<m; k++) { if (ms[k]=='0') ms[k]='9'; else if (ms[k]>'0'&&ms[k]<='9') ms[k]--; }
            } else if (c=='A') {
                for (k=0; k<m/2; k++) { t=ms[k]; ms[k]=ms[m-k-1]; ms[m-1-k]=t; }
            } else if (c=='E') {
                for (k=0; k<m/2; k++) { t=ms[k]; ms[k]=ms[(m+1)/2+k]; ms[(m+1)/2+k]=t; }
            } else if (c=='C') {
                t=ms[0]; for (k=1; k<m; k++) ms[k-1]=ms[k]; ms[m-1]=t;
            } else if (c=='J') {
                t=ms[m-1]; for (k=m-1; k>=1; k--) ms[k]=ms[k-1]; ms[0]=t;
            } else printf("something rong\n");
        }
        printf("%s\n", ms);
    }
    return 0;
}


