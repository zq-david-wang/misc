#include<stdio.h>

char buf[1024];
typedef struct _T {
    struct _T *n;
    int b;
}NNode;
NNode pool[128];
int pc;
// NNode *nei[64];
char nei[64][64];
char cs[64];
char node[64];
int readline() {
    int i=0;
    char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        buf[i++] = c;
    }
    buf[i]=0;
    return c;
}

int parse(char *b) {
    int i=0, n=0, v;
    while(1) {
        while(b[i]==' ')i++;
        if (b[i]==0) break;
        v=0; while(b[i]>='0'&&b[i]<='9') { v=v*10+b[i]-'0'; i++; }
        cs[v]++;
        node[n++] = v;
    }
    return n;
}

int express(int s, char *b, int i, int n) {
    // printf("express %d from %d\n", s, i);
    b[i++]='(';
    int c = s/10; if (c) b[i++] = c+'0';
    b[i++] = (s%10)+'0';
    int j; for (j=1; j<=n; j++) {
        if (nei[s][j]) {
            b[i++] = ' ';
            i = express(j, b, i, n);
        }
    }
    b[i++] = ')';
    return i;
}
int main() {
    int i, c, j, n, nn, k;
    NNode *p;
    while(readline()!=EOF) {
        for (i=1; i<=50; i++) { cs[i]=0;}
        pc = 0;
        n = parse(buf);
        // for (i=0; i<n; i++) printf("%d ", node[i]); printf("\n");
        if (n==0) nn=1;
        else nn = node[n-1];
        for (i=1; i<=nn; i++) for (j=1; j<=nn; j++) nei[i][j]=0;
        for (i=0; i<n; i++) {
            j = node[i];
            for (k=1; k<=nn; k++) if (cs[k]==0) break;
            // p = &pool[pc++]; p->b=k; p->n=nei[j]; nei[j]=p;
            nei[j][k]=1;
            cs[k]=-1; cs[j]--;
            // printf("%d->%d\n", k, j);
        }
        i = express(nn, buf, 0, nn);
        buf[i]=0;
        printf("%s\n", buf);
    }
    return 0;
}
