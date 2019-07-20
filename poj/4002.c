#include<stdio.h>
#include<string.h>

char *mons[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
int days[] = {31, 28, 31, 30, 31,30, 31,31,30,31,30,31};
int yhs[64], mhs[12];
struct { int h, c; } orders[2500];
int costs[100000];
void prep() {
    int y = 2000; yhs[0]=0;
    int i, leap; for (i=1; i<64; i++) {
        leap = 0; if ((y%4)==0) { if ((y%400)==0) leap=1; else if (y%100) leap=1; }
        yhs[i] = yhs[i-1]+(365+leap)*24;
        y++;
    }
    mhs[0]=0;
    for (i=1; i<12; i++) { mhs[i]=mhs[i-1]+days[i-1]*24; }
}

long long minvs[100001];
typedef struct { long long c; int i; } HNode;
HNode heap[100001];
int heapi[100001], hpc;
void heapify(int s) {
    int ms=s, ns;
    ns = s*2+1;
    if (ns>=hpc) return;
    if (heap[ns].c < heap[ms].c) ms=ns;
    ns = s*2+2;
    if (ns<hpc&&heap[ns].c<heap[ms].c) ms=ns;
    if (ms==s) return;
    HNode t;
    t=heap[ms]; heap[ms]=heap[s]; heap[s]=t;
    heapi[heap[ms].i]=ms;
    heapi[heap[s].i]=s;
    heapify(ms);
}
void adjust(int s) {
    int p;
    HNode t;
    while(s>0) {
        p = (s-1)/2;
        if (heap[p].c<=heap[s].c) break;
        t=heap[p]; heap[p]=heap[s]; heap[s]=t;
        heapi[heap[p].i]=p;
        heapi[heap[s].i]=s;
        s = p;
    }
}
void assert(int* p) {
    *p = 0;
}
int main() {
    int n, m, i;
    char mb[8];
    int day, year, hour, order, month;
    int t,s, leap, ii;
    long long rc, lv;
    prep();
    while(1) {
        scanf("%d %d", &n, &m); if (n==0) break;
        for (i=0; i<n; i++) {
            scanf("%s  %d %d  %d %d", mb, &day, &year, &hour, &order);
            for (month=0; month<12; month++) if (strcmp(mons[month], mb)==0) break;
            leap = 0; if ((year%4)==0) { if ((year%400)==0) leap=24; else if (year%100) leap=24; }
            orders[i].c = order;
            orders[i].h = yhs[year-2000]+mhs[month]+(day-1)*24+hour; if (month>2) orders[i].h+=leap;
        }
        scanf("%d %d", &t, &s);
        for (i=0; i<m; i++) scanf("%d", &costs[i]);
        // build up heap from day 0 to 100000
        hpc=0; for (i=0; i<=orders[n-1].h; i++) {
            // extract i-t
            if (i>=t && hpc>0) {
                ii = heapi[i-t]; heap[ii]=heap[--hpc]; heapi[heap[ii].i]=ii; heapify(ii);
            }
            // add costs[i]-s
            if (i<m) {
                heap[hpc].i=i; heap[hpc].c=costs[i]-i*s; heapi[i]=hpc; hpc++; adjust(hpc-1);
            }
            // put heap[0]+(i+1)*s to i
            if (hpc==0) assert(0);
            minvs[i] = heap[0].c+i*s;
            // printf("minvs for %d is %d\n", i, minvs[i]);
        } 
        rc=0; for(i=0; i<n; i++) {
            lv = minvs[orders[i].h];
            lv *= orders[i].c;
            rc += lv;
        }
        printf("%lld\n", rc);
    }
    return 0;
}
