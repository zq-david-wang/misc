#include<stdio.h>

int readline(char *b) {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        b[i++] = c;
    }
    b[i]=0;
    return i;
}
char key[88], plain[10008];
char mx[100][100];
int main() {
    int i, l, s, j, k, k1;
    int r, c;
    char cc;
    while(1) {
        l = readline(key); if (l==0) break;
        l = readline(plain);
        s = (key[0]-'0')*10+key[1]-'0'; if (s==0) s=100;
        r=0; c=0; i=0;
        for (i=0; i<l; i++) {
            cc = plain[i]; if (cc>='a'&&cc<='z') cc=cc-'a'+'A';
            mx[r][c]=cc;
            c++; if (c==s) {c=0; r++; }
        }  cc= 'A';
        while(r<s) {
            mx[r][c]=cc; cc++; if (cc>'Z') cc='A';
            c++; if (c==s) {c=0; r++; }
        }
        for (i=2;;i++) {
            cc = key[i]; if (cc==0) break;
            if (cc=='S') {
                for (j=0; j<s; j+=2) { cc = mx[0][j]; for (k=0; k<s-1; k++) mx[k][j]=mx[k+1][j]; mx[k][j]=cc; }
                for (j=1; j<s; j+=2) { cc = mx[s-1][j]; for (k=s-2; k>=0; k--) mx[k+1][j]=mx[k][j]; mx[0][j]=cc; }
            } else if (cc=='R') {
                for (j=1; j<s; j+=2) { cc = mx[j][0]; for (k=0; k<s-1; k++) mx[j][k]=mx[j][k+1]; mx[j][k]=cc; }
                for (j=0; j<s; j+=2) { cc = mx[j][s-1]; for (k=s-2; k>=0; k--) mx[j][k+1]=mx[j][k]; mx[j][0]=cc; }
            } else {
                for (j=0; j<s/2; j++) {
                    if (j&1) {
                        cc = mx[j][j]; 
                        for (k1=j; k1<s-j-1;k1++) mx[j][k1]=mx[j][k1+1];
                        for (k1=j; k1<s-j-1;k1++) mx[k1][s-j-1]=mx[k1+1][s-j-1];
                        for (k1=s-j-1; k1>j;k1--) mx[s-j-1][k1]=mx[s-j-1][k1-1];
                        for (k1=s-j-1; k1>j+1;k1--) mx[k1][j]=mx[k1-1][j];
                        mx[k1][j] = cc;
                    } else {
                        cc = mx[j][j]; 
                        for (k1=j; k1<s-j-1;k1++) mx[k1][j]=mx[k1+1][j];
                        for (k1=j; k1<s-j-1;k1++) mx[s-j-1][k1]=mx[s-j-1][k1+1];
                        for (k1=s-j-1; k1>j;k1--) mx[k1][s-j-1]=mx[k1-1][s-j-1];
                        for (k1=s-j-1; k1>j+1;k1--) mx[j][k1]=mx[j][k1-1];
                        mx[j][k1] = cc;
                    }
                }
            }
        }
        i=0; for (j=0; j<s; j++) for (k=0; k<s; k++) plain[i++] = mx[j][k];
        plain[i]=0;
        printf("%s\n", plain);
    }
    return 0;
}
