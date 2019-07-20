#include<stdio.h>

char homen[32], guestn[32];
char hmem[9][32], gmem[9][32];
double hph[9], hps[9];
double gph[9], gps[9];
long long seed;
void reset() {
    seed=1;
}
int next_random() {
    seed = (seed * 25173 + 13849) % 65536;
    return seed;
}
char gmark[8], hmark[8];
struct { char t, i; } runs[1024];
char sep[100];
int main() {
    int cc, ci;
    int i, gi, hi, j, outs;
    int rc, hc, grc, ghc, hrc, hhc;
    int rn, chc, crc;
    for (i=0; i<60; i++) sep[i]='='; sep[i]=0;
    scanf("%d", &cc); for (ci=1; ci<=cc; ci++) {
        scanf("%s", guestn); for (i=0; i<9; i++) scanf("%s %lf %lf", gmem[i], &gph[i], &gps[i]);
        scanf("%s", homen); for (i=0; i<9; i++) scanf("%s %lf %lf", hmem[i], &hph[i], &hps[i]);
        reset(); gi=0; hi=0; grc=0; ghc=0; hrc=0; hhc=0;
        if (ci>1) printf("%s\n", sep);
        printf("Game %d: %s vs. %s\n\n", ci, guestn, homen);
        for (i=1; ; i++) {
            if (i>9 && grc != hrc) break;
            printf("Inning %d:\n", i);
            printf("Hits:\n");
            for (j=0; j<4; j++) hmark[j]=gmark[j]=-1;
            outs = 0; rc=0; hc=0;
            chc=0; crc=0;
            //. guest run
            while(outs<3) {
               if ((gmark[1]!=-1 && outs==0)|| (gmark[2]!=-1 && outs==1)) {
                   outs++;
                   rn = next_random();
                   if (rn <= gps[gi]*65536) {
                       //success
                       for (j=3; j>=1; j--) gmark[j]=gmark[j-1]; gmark[j]=-1;
                       if (gmark[3]!=-1) { runs[rc].i = gmark[3]; runs[rc].t = 0; rc++; gmark[3]=-1; }
                   }
               } else {
                    rn = next_random();
                    if (rn <= gph[gi]*65536) {
                        hc++;
                        printf("  %15s %15s\n", gmem[gi], guestn);
                       for (j=3; j>=1; j--) gmark[j]=gmark[j-1]; gmark[j]=gi;
                       if (gmark[3]!=-1) { runs[rc].i = gmark[3]; runs[rc].t = 0; rc++; gmark[3]=-1; }
                    } else outs++;
               }
               gi++; gi%=9;
            }
            grc += rc; ghc += hc;
            crc += rc; chc += hc;
            if (i!=9 || (hrc <= grc)) {
                //. home run
                outs = 0; hc=0;
                while(outs<3) {
                   if ((hmark[1]!=-1 && outs==0)|| (hmark[2]!=-1 && outs==1)) {
                       outs++;
                       rn = next_random();
                       if (rn <= hps[hi]*65536) {
                           //success
                           for (j=3; j>=1; j--) hmark[j]=hmark[j-1]; hmark[j]=-1;
                           if (hmark[3]!=-1) { runs[rc].i = hmark[3]; runs[rc].t = 1; rc++; hmark[3]=-1; }
                       }
                   } else {
                        rn = next_random();
                        if (rn <= hph[hi]*65536) {
                            hc++;
                            printf("  %15s %15s\n", hmem[hi], homen);
                           for (j=3; j>=1; j--) hmark[j]=hmark[j-1]; hmark[j]=hi;
                           if (hmark[3]!=-1) { runs[rc].i = hmark[3]; runs[rc].t = 1; rc++; hmark[3]=-1; }
                        } else outs++;
                   }
                   hi++; hi%=9;
                }
                hrc += (rc-crc); hhc += hc;
                chc += hc;
            }
            if (chc==0) printf("  none\n");
            printf("\n");
            printf("Runs:\n");
            if (rc==0) printf("  none\n");
            else {
                for (j=0; j<rc; j++) {
                    if (runs[j].t==0) printf("  %15s %15s\n", gmem[runs[j].i], guestn);
                    else printf("  %15s %15s\n", hmem[runs[j].i], homen);
                }
            }
            printf("\n");
        }
        printf("End of Game:\n");
        printf("  %15s %d runs, %d hits\n", guestn, grc, ghc);
        printf("  %15s %d runs, %d hits\n", homen, hrc, hhc);
    }
    return 0;
}
