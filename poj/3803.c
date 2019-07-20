#include<stdio.h>
#include<stdlib.h>
#include<string.h>


long long as[12];
long long ras[12];
int las[12];
char bs[12][16];
char temp[128];
struct { char s[12]; short d, l; } queue[10240];
int main() {
    int n, d, l, tl, m;
    char target[16], a[16], *p;
    int head, tail, mod=sizeof(queue)/sizeof(queue[0]);
    long long v, r, t;
    int i, j, k, ss, kk;
    while(1) {
        scanf("%d", &n); if (n==0) break;
        for (i=0; i<n; i++) {
            scanf("%s %s", a, bs[i]);
            r=1; v=0; j=0; while(a[j]) {
                v=v*26+a[j]-'a'; j++;
                r*=26;
            }
            as[i]=v; las[i]=j; ras[i]=r/26;
        }
        scanf("%s %s", queue[0].s, target);
        tl = strlen(target);
        i=0; t=0; while(target[i]) {
            t=t*26+target[i]-'a'; i++;
        }
        head=1, tail=0; queue[0].d=0; queue[0].l=strlen(queue[0].s);
        while(tail!=head) {
            p = queue[tail].s;
            d = queue[tail].d;
            l = queue[tail].l;
            // printf("deque %s(%d)\n", p, l);
            tail++; tail %= mod;
            for (i=0; i<n; i++) {
                if (las[i]>l) continue;
                k=0; ss=0;
                j=0; while(j<l) {
                    v=0; for (kk=0; kk<las[i]-1&&j<l; j++, kk++) {
                        v=v*26+p[j]-'a';
                    }
                    for (; j<l; j++) {
                        v=v*26+p[j]-'a';
                        if (v==as[i]) {
                            j++;
                            ss = j;
                            m=0; while(bs[i][m]) {
                                temp[k++] = bs[i][m++];
                            }
                            break;
                        } else {
                            v -= ras[i]*(p[j-las[i]+1]-'a');
                            // append 
                            temp[k++] = p[ss++];
                        }
                    }
                }
                for (; ss<l; ss++) temp[k++] = p[ss];
                if (k==tl) {
                    v=0; for (j=0; j<k; j++) v=v*26+temp[j]-'a';
                    if (v==t) { d++; head=1; tail=0; break; }
                } else if (k>l && k<tl) {
                    temp[k]=0;
                    for (j=0; j<=k; j++) queue[head].s[j]=temp[j];
                    queue[head].d=d+1;
                    queue[head].l=k;
                    head++; head %= mod;
                }
            }
            if (i<n) break;
        }
        if (head==tail) d=-1;
        printf("%d\n", d);
    }
    return 0;
}


