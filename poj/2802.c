#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {int p1, p2;} PNode;
PNode ws[4][5];
void assert(char *p) {
    *p=0;
}
void ck1(char *p, char a, char b, int i, char c) {
    if (strlen(p)!=3) assert(NULL);
    if (a<'0'||a>'9'||b<'0'||b>'9') assert(NULL);
    if (a>b) assert(NULL);
    if (c) {
        if (i==0&&a!=b) assert(NULL);
        if (i==4&&a!='0') assert(NULL);
    }
}
int gcd(int a, int b) {
    int t; while(a) {
        t=a; a=b%a; b=t;
    }
    return b;
}
int main() {
    int tc, ti, i, j, k;
    char bb[8], ba[8], a, b;
    PNode p[6][5];
    int pc[6][5];
    int a1, a2, b1, b2, aaa, bbb, g;
    scanf("%d", &tc); for (ti=1; ti<=tc; ti++) {
        printf("data set #%d\n", ti);
        j=0; for (i=0; i<5; i++) { scanf("%s", bb); ws[j][i].p1 = bb[0]-'0'; ws[j][i].p2 = bb[2]-'0'; ck1(bb, bb[0],bb[2], i, 1);}
        j++; for (i=0; i<4; i++) { scanf("%s", bb); ws[j][i].p1 = bb[0]-'0'; ws[j][i].p2 = bb[2]-'0'; ck1(bb, bb[0],bb[2], i, 0);}
        j++; for (i=0; i<5; i++) { scanf("%s", bb); ws[j][i].p1 = bb[0]-'0'; ws[j][i].p2 = bb[2]-'0'; ck1(bb, bb[0],bb[2], i, 1);}
        j++; for (i=0; i<4; i++) { scanf("%s", bb); ws[j][i].p1 = bb[0]-'0'; ws[j][i].p2 = bb[2]-'0'; ck1(bb, bb[0],bb[2], i, 0);}
        for (i=0; i<3; i++) {
            scanf("%s %s", ba, bb);
            a = ba[0]-'A'; b = bb[0]-'A';
            if (a<0||a>4||b<0||b>4) assert(NULL);
            k=4; for (j=0; j<5; j++) { p[k][j].p1=0; p[k][j].p2=1; pc[k][j]=0; } p[k][b].p1=1; pc[k][b]=1;
            k--; for (j=0; j<4; j++) {
                a1 = p[k+1][j].p1*(ws[k][j].p2-ws[k][j].p1);
                b1 = p[k+1][j].p2*ws[k][j].p2;
                a2 = p[k+1][j+1].p1*ws[k][j].p1;
                b2 = p[k+1][j+1].p2*ws[k][j].p2;
                aaa = a1*b2+a2*b1; bbb = b1*b2;
                g = gcd(aaa, bbb); if (g) { aaa/=g; bbb/=g; }
                if (aaa==0) bbb=1;
                p[k][j].p1=aaa; p[k][j].p2=bbb;
                pc[k][j]=0; if (ws[k][j].p1) pc[k][j]+=pc[k+1][j+1]; if (ws[k][j].p2-ws[k][j].p1) pc[k][j]+=pc[k+1][j];
            }
            // for (j=0; j<4; j++) printf("%d/%d ", p[k][j].p1, p[k][j].p2); printf("\n");
            k--; for (j=0; j<5; j++) {
                a1 = p[k+1][j].p1*ws[k][j].p1;
                b1 = p[k+1][j].p2*ws[k][j].p2;
                aaa = a1; bbb = b1;
                if (j>0&&(ws[k][j].p2-ws[k][j].p1)>0) {
                    a2 = p[k+1][j-1].p1*(ws[k][j].p2-ws[k][j].p1);
                    b2 = p[k+1][j-1].p2*ws[k][j].p2;
                    aaa = a1*b2+a2*b1; bbb = b1*b2; 
                }
                g = gcd(aaa, bbb); if (g==0) g=1; aaa/=g; bbb/=g;
                if (aaa==0) bbb=1;
                p[k][j].p1=aaa; p[k][j].p2=bbb;
                pc[k][j]=0; if (ws[k][j].p1) pc[k][j]+=pc[k+1][j]; if (j>0&&(ws[k][j].p2-ws[k][j].p1)>0) pc[k][j]+=pc[k+1][j-1];
            }
            // for (j=0; j<5; j++) printf("%d/%d ", p[k][j].p1, p[k][j].p2); printf("\n");
            k--; for (j=0; j<4; j++) {
                a1 = p[k+1][j].p1*(ws[k][j].p2-ws[k][j].p1);
                b1 = p[k+1][j].p2*ws[k][j].p2;
                a2 = p[k+1][j+1].p1*ws[k][j].p1;
                b2 = p[k+1][j+1].p2*ws[k][j].p2;
                aaa = a1*b2+a2*b1; bbb = b1*b2;
                g = gcd(aaa, bbb); if (g) {aaa/=g; bbb/=g;}
                if (aaa==0) bbb=1;
                p[k][j].p1=aaa; p[k][j].p2=bbb;
                pc[k][j]=0; if (ws[k][j].p1) pc[k][j]+=pc[k+1][j+1]; if (ws[k][j].p2-ws[k][j].p1) pc[k][j]+=pc[k+1][j];
            }
            k--; for (j=0; j<5; j++) {
                a1 = p[k+1][j].p1*ws[k][j].p1;
                b1 = p[k+1][j].p2*ws[k][j].p2;
                aaa = a1; bbb = b1;
                if (j>0&&(ws[k][j].p2-ws[k][j].p1)>0) {
                    a2 = p[k+1][j-1].p1*(ws[k][j].p2-ws[k][j].p1);
                    b2 = p[k+1][j-1].p2*ws[k][j].p2;
                    aaa = a1*b2+a2*b1; bbb = b1*b2; 
                }
                g = gcd(aaa, bbb); if (g) {aaa/=g; bbb/=g;}
                if (aaa==0) bbb=1;
                p[k][j].p1=aaa; p[k][j].p2=bbb;
                pc[k][j]=0; if (ws[k][j].p1) pc[k][j]+=pc[k+1][j]; if (j>0&&(ws[k][j].p2-ws[k][j].p1)>0) pc[k][j]+=pc[k+1][j-1];
            }
            printf("%c->%c %d paths, %d%% chance\n", ba[0], bb[0], pc[0][a], p[0][a].p1*100/p[0][a].p2);
        }
    }
    return 0;
}


