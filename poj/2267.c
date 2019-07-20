#include<stdio.h>
#include<string.h>

char names[100][32];
int nc;
int addname() {
    int i; for (i=0; i<nc; i++) if (strcmp(names[i], names[nc])==0) return i;
    return i;
}
struct { char s, d; short b, n; } pool[1001];
int pc, nei[100];
int spath[100];
int flag[100];
#define INF 0x7fffffff
int main() {
    int t, ci, n, i, j, k;
    int a, b;
    int s, d;
    int cc, nd, md, mi, start, td, rc;
    int si, di;
    scanf("%d", &t); for (ci=1; ci<=t; ci++) {
        nc=0; pc=0;
        scanf("%d", &n);
        for (i=0; i<100; i++) nei[i]=-1;
        for (i=0; i<n; i++) {
            scanf("%s", names[nc]);
            a=addname(); if (a==nc) nc++;
            scanf("%s", names[nc]);
            b=addname(); if (b==nc) nc++;
            scanf("%d %d", &s, &d); s%=24;
            if (d>12) continue;
            if (s>=6&&s<18) continue;
            td = s+d; td %= 24;
            if (td>6&&td<=18) continue;
            pool[pc].s=s; pool[pc].d=d;
            pool[pc].b=b; pool[pc].n=nei[a]; nei[a]=pc++;
            // printf("add route from %d to %d, start %d for %d\n", a, b, s, d);
        }
        scanf("%s", names[nc]); a=addname(); if (a==nc) nc++;
        scanf("%s", names[nc]); b=addname(); if (b==nc) nc++;
        si = a; di=b;
        // printf("travel from %d to %d\n", si, di);
        rc = -1;
        i = nei[a]; while(i!=-1) {
            start = pool[i].s;
            // dij
            for (j=0; j<nc; j++) { spath[j]=INF; flag[j]=0; }
            spath[a]=0;
            while(1) {
                md = INF;
                for (j=0; j<nc; j++) {
                    if (flag[j]) continue;
                    if (md>spath[j]) {
                        md = spath[j]; mi=j;
                    }
                }
                if (md==INF) break;
                flag[mi] = 1;
                // printf("find next spath for %d %d[%d]\n", mi, md, nc);
                k = nei[mi];
                while(k!=-1) {
                    b = pool[k].b; s = pool[k].s; d = pool[k].d;
                    if (flag[b]==0) {
                        nd = (s+24-((md+start)%24))%24+md+d;
                        // printf("try relaxing %d from %d to %d via %d\n", b, spath[b], nd, mi);
                        if (nd<spath[b]) spath[b]=nd;
                    }
                    k = pool[k].n;
                }
            }
            if (spath[di]!=INF) {
                // printf("took %d to reach %d,start is %d\n", spath[di], di, start);
                td = start + spath[di];
                cc =  (td+6)/24;
                if (start>12) cc--;
                if (rc<0||rc>cc) rc=cc;
            }
            i = pool[i].n;
        }
        printf("Test Case %d.\n", ci);
        if (rc==-1) printf("There is no route Vladimir can take.\n");
        else printf("Vladimir needs %d litre(s) of blood.\n", rc);
    }
    return 0;
}
