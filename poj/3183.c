#include<stdio.h>

int main() {
    int n, i, v, lv=-1, s=0;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &v);
        if (s==0) {
            if (v<=lv) {
                printf("%d\n", i);
                if (v<lv) s = 1;
            }
            lv = v;
        } else {
            if (v>=lv) {
                s = 0;
            }
            lv = v;
        }
    }
    if (s==0) printf("%d\n", n);
    return 0;
}
