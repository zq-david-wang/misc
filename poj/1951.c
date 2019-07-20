#include<stdio.h>

char buf[80];
char out[80];
char map[128];
int main() {
    char c, b=0;
    int i=0, j, k;
    while(1) {
        c = getchar();
        if (c==EOF || c== '\n') break;
        buf[i++] = c;
    }
    for (j=0; j<128; j++) map[j] = 0;
    map['A'] = 1;
    map['E'] = 1;
    map['I'] = 1;
    map['O'] = 1;
    map['U'] = 1;
    k=0; for (j=0; j<i; j++) {
        c = buf[j];
        if (map[c]) continue;
        if (c != ' ') {
           if (c>='A'&&c<='Z') {
               if (b&&k>0) out[k++] = ' ';
               map[c] = 1;
           }
           out[k++] = c;
           b = 0;
        } else { b=1; }
    }
    out[k] = 0;
    printf("%s\n", out);
    return 0;
}
