#include<stdio.h>
#include<string.h>

typedef struct {
    unsigned char s[13], p, d;
}SNode;


#define MOD 262145
SNode queue[MOD];

char buf[128];
char checkstate(char *p, int n) {
    int i=0; for (i=0; i<n; i++) if (p[i/8]&(1<<((i%8)))) break;
    int j; for (j=n-1; j>=0; j--) if (p[j/8]&(1<<((j%8)))) break;
    // int k; printf("check state: "); for (k=0; k<n; k++) printf(" %d", (p[k/8]>>((k%8)))&1); printf("\n");
    for (i++;i<j;i++) if ((p[i/8]&(1<<((i%8))))==0) return 0;
    return 1;
}

char getbit(char *s, int p) {
    char c = s[p/8];
    return (c>>((p%8)))&1;
}
char setbit(char *s, int p, char b) {
    if (b) s[p/8] |= (1<<((p%8))); 
    else s[p/8] &= ~(1<<((p%8)));
}
void bflip(char *s, int p) {
    // bit p-2, p-1 = p-1, !p-2
    char b1 = getbit(s, p-2);
    char b2 = getbit(s, p-1);
    // int k; printf("before bflip %d: ", p); for (k=0; k<6; k++) printf(" %d", (s[k/8]>>((k%8)))&1); printf("\n");
    setbit(s, p-2, b2);
    setbit(s, p-1, (b1+1)&1);
    // printf("after bflip %d: ", p); for (k=0; k<6; k++) printf(" %d", (s[k/8]>>((k%8)))&1); printf("\n");
}
void fflip(char *s, int p) {
    // bit p-2, p-1 = p-1, !p-2
    // int k; printf("before fflip %d: ", p); for (k=0; k<6; k++) printf(" %d", (s[k/8]>>((k%8)))&1); printf("\n");
    char b1 = getbit(s, p);
    char b2 = getbit(s, p+1);
    setbit(s, p, (b2+1)&1);
    setbit(s, p+1, b1);
    // printf("after fflip %d: ", p); for (k=0; k<6; k++) printf(" %d", (s[k/8]>>((k%8)))&1); printf("\n");
}
void printstate(char *s, int p, int n) {
    int k;
    printf("instate %d ", p); for (k=0; k<n; k++) printf(" %d", (s[k/8]>>((k%8)))&1); printf("\n");
}
int main() {
    int i, p, l, v, ic, d, ci=0;
    char *s;
    int head, tail, ni, base=1;
    while(1) {
        scanf("%s", buf); if (buf[0]=='-') break; ci++;
        for (i=0;;i++) if (buf[i]=='F') break; p=i;
        s = queue[0].s; queue[0].p = p; l=0; ic=0; v=0;
        base=1;
        for (i=0;;i++) {
            if (buf[i]==0) break;
            if (buf[i]=='F') continue;
            if (buf[i]=='B') v+=base;
            l++; base*=2;
            if ((l%8)==0) {
                s[ic++] = v; v=0; base=1;
            }
        }
        if (l%8) s[ic++]=v;
        d = 0;
        head=1; tail=0; queue[0].d = 0;
        if (checkstate(s, l)==0) {
            while(tail!=head) {
                p=queue[tail].p; s=queue[tail].s; d=queue[tail].d;
                // printf("dequeu %d/%d ", tail, head);    printstate(s, p, l);
                if (p>0) {
                    ni = head;
                    memcpy(&queue[ni], &queue[tail], sizeof(SNode));
                    queue[ni].p -= 1;
                    queue[ni].d = d+1;
                    // printstate(queue[ni].s, queue[ni].p, l);
                    if (d<8) head=(head+1)%MOD;
                }
                if (p<l) {
                    ni = head;
                    memcpy(&queue[ni], &queue[tail], sizeof(SNode));
                    queue[ni].p += 1;
                    queue[ni].d = d+1;
                    // printstate(queue[ni].s, queue[ni].p, l);
                    if (d<8) head=(head+1)%MOD;
                }
                // flip
                if (p>1) {
                    ni = head;
                    memcpy(&queue[ni], &queue[tail], sizeof(SNode));
                    bflip(queue[ni].s, queue[ni].p);
                    if (checkstate(queue[ni].s, l)==1) { d++; break; }
                    queue[ni].p -= 2; queue[ni].d = d+1;
                    if (d<8) head=(head+1)%MOD;
                }
                if (p<l-1) {
                    ni = head;
                    memcpy(&queue[ni], &queue[tail], sizeof(SNode));
                    fflip(queue[ni].s, queue[ni].p);
                    if (checkstate(queue[ni].s, l)==1) { d++; break; }
                    queue[ni].p += 2; queue[ni].d = d+1;
                    if (d<8) head=(head+1)%MOD;
                }
                tail++; tail%=MOD;
            }
        }
        if (head==tail) d=-1;
        printf("%d. %d\n", ci, d);
    }
    return 0;
}

