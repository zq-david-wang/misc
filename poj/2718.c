#include<stdio.h>

char buf[128];
int readline() {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        buf[i++] = c;
    }
    buf[i]=0;
    return i;
}
char mark[10];
char ds[10];
char tds[10];
int main() {
    int c, i, j, k, ii;
    int v1, v2, d;
    readline();
    sscanf(buf, "%d", &c);
    for (i=0; i<c; i++) {
        for (j=0; j<10; j++) mark[j]=0;
        readline(); j=0; while(buf[j]) {
            if (buf[j]>='0'&&buf[j]<='9') mark[buf[j]-'0']=1;
            j++;
        }
        k=0; for (j=0; j<10; j++) if (mark[j]) ds[k++] =j;
        if (k&1) {
            v1=ds[0]; if (v1==0) { v1=ds[1]; ds[1]=ds[0]; }
            for (j=0; j<k/2; j++) v1=v1*10+ds[j+1];
            v2=0; for (j=0; j<k/2; j++) v2=v2*10+ds[k-1-j];
            d = v1-v2;
        } else {
            if (k==2) d=ds[1]-ds[0];
            else {
                d = 0x7fffff;
                for (j=0; j<k-1; j++) {
                    if (ds[j]) {
                        for (ii=j+2; ii<k; ii++) tds[ii-2]=ds[ii];
                        v1=ds[j+1]; for (ii=0; ii<k/2-1; ii++) v1=v1*10+tds[ii];
                        v2=ds[j]; for (ii=0; ii<k/2-1; ii++) v2=v2*10+tds[k-2-1-ii];
                        if (d>(v1-v2)) d=v1-v2;
                    }
                    tds[j]=ds[j];
                }
            }
        }
        printf("%d\n", d);
    }
    return 0;
}
