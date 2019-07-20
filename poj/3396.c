#include<stdio.h>
#include<math.h>

int main() {
    int a, b, c, d, r, s;
    int v1, v2, t1, t2, t3;
    for (a=1; a<=500; a++) {
        for (b=a;;b++) {
            t1=a+b; if (t1>1000) break;
            r = (2000-t1)/2;
            t2=a*b;
            s = 1000000/t2+1;
            if (s<b) s=b;
            for (c=s; c<=r; c++) {
                v1 = t2*c-1000000;
                t3 = t1+c;
                v2 = 1000000*t3;
                if ((v2%v1)) continue;
                d = v2/v1;
                if (d<c) continue;
                if((t3+d)<=2000) printf("%d.%02d %d.%02d %d.%02d %d.%02d\n", a/100, a%100, b/100, b%100, c/100, c%100, d/100, d%100);
            }
        }
    }
    return 0;
}
