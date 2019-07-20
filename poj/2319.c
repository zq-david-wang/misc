#include<stdio.h>

char line[128];
int main() {
    int i, j, k, ii;
    int f, c, r, fc;
    int lf, lc, lr;
    char *pr, *pc, *pf;
    int nr, base;
    char bc[32];
    while(scanf("%s", line)==1) {
        pf = line;
        f=0; i=0; j=i; while(line[j]!='-'){
            f=f*10+line[j]-'0'; j++;
        }
        r=0; k=j+1; while(line[k]!=0) { 
            r = r*10 + line[k]-'0'; k++;
        }
        line[j]=0; pr=line+j+1;
        //
        lr = k-j-1; lf=j;
        c=0; base=1; fc=0; bc[31]=0; pc=bc+31;
        for (lc=1; lc<=lr; lc++) {
            // c = k-1-i+1..k-1
            pc--; *pc = line[k-lc];
            // printf("try c %s\n", pc);
            c += base*(pc[0]-'0'); if (j-lc>=0) fc+=base*(line[j-lc]-'0');
            base *= 10;
            nr=0;
            for (i=0; i<lf-lc; i++) nr = 10*nr+pf[i]-'0';
            for (i=0;i<lc; i++) nr=10*nr+pc[i]-'0';
            // printf("nr %d, r %d, c %d fc %d\n", nr, r, c, fc);
            if (fc<c) { if (nr==r) break;
            } else { if (nr+base==r) break; }
        }
        if (lc<=lr) printf("%s-%s\n", pf, pc);
        else printf("%s-%s\n", pf, pr);

    }
    return 0;
}
