#include<stdio.h>
#include<math.h>

char buf[1024];
int readline() {
    int i=0;
    char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        buf[i++] =c;
    }
    buf[i]=0;
    return i;
}
int main() {
    int n, i, m;
    int hh, mm, ss, total, r;
    double d;
    char *b, ct[8], v;
    readline();
    sscanf(buf, "%d %lf", &n, &d);
    while(readline()) {
        b = buf; while((*b)==' ')b++;
        m=0; while((*b)!=' ') { m = m*10+(*b)-'0'; b++; }
        total=0;
        v = 1;
        while(1) {
            while((*b)==' ')b++;
            if ((*b)==0)break;
            if ((*b)=='-') { v=0; break; }
            hh=0; while((*b)!=':') {hh=hh*10+(*b)-'0';b++;} b++;
            mm=0; while((*b)!=':') {mm=mm*10+(*b)-'0';b++;} b++;
            ss=0; while((*b)!=' '&&(*b)!=0) {ss=ss*10+(*b)-'0';b++;}
            total += (hh*3600+mm*60+ss);
        }
        if (v) {
            r = round(total/d);
            printf("%3d: %d:%02d min/km\n", m, r/60, r%60);
        } else {
            printf("%3d: -\n", m);
        }
    }
    return 0;
}
