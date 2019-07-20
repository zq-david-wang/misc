#include<stdio.h>

int main() {
    int n, s1, s2, v;
    for (n=2992; n<=9999; n++) {
        s1=0; v=n; while(v) { s1+= (v%10); v/=10; }
        s2=0; v=n; while(v) { s2+= (v%16); v/=16; }
        if (s1!=s2) continue;
        s2=0; v=n; while(v) { s2+= (v%12); v/=12; }
        if (s1==s2) printf("%d\n", n);
    }
    return 0;
}
