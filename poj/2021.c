#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct { short i, pi, d, age; } ds[100];
char names[100][32];
int nc;
int addname(const char *n) {
    int i; for (i=0; i<nc; i++) if (strcmp(n, names[i])==0) return i;
    strcpy(names[nc], n);
    nc++;
    return i;
}
int calc(int i) {
    if (ds[i].age!=-1) return ds[i].age;
    int a=calc(ds[i].pi)-ds[i].d;
    ds[i].age = a;
    return a;
}
int main() {
    int tc, ti, n, i, d, id, pid, j;
    char na[32], nb[32];
    sprintf(names[0], "Ted");
    ds[0].age = 100;
    scanf("%d", &tc); for (ti=1; ti<=tc; ti++) {
        nc = 1;
        scanf("%d", &n);
        for (i=0; i<n; i++) {
            scanf("%s %s %d", na, nb, &d);
            pid = addname(na);
            id = addname(nb);
            ds[id].i=id;
            ds[id].pi=pid;
            ds[id].d=d;
            ds[id].age=-1;
        }
        for (i=0; i<nc; i++) if (ds[i].age==-1) calc(i);
        for (i=2; i<nc; i++) {
            id = ds[i].i; d = ds[i].age;
            for (j=i-1; j>0; j--) {
                if (ds[j].age > d) break;
                if (ds[j].age==d&&strcmp(names[ds[j].i], names[id])<=0) break;
                ds[j+1]=ds[j];
            }
            j++; ds[j].i=id; ds[j].age=d;
        }
        printf("DATASET %d\n", ti);
        for (i=1; i<nc; i++) printf("%s %d\n", names[ds[i].i], ds[i].age);
    }
    return 0;
}


