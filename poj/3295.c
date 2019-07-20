#include<stdio.h>

char indexes[128];
char map[5][4] = {
    {0, 0, 0, 1},
    {0, 1, 1, 1},
    {1, 1, 0, 0},
    {1, 1, 0, 1},
    {1, 0, 0, 1},
};

int eval(int v, char* b, int* p) {
    int i = *p, j;
    char w, x, c=b[i];
    if (c>='a' && c<='z') {
        j = indexes[c];
        *p = i+1;
        return (v>>j)&1;
    }
    j = indexes[c];
    i++;
    w = eval(v, b, &i);
    *p = i;
    if (c=='N')return (w+1)%2;
    x = eval(v, b, &i);
    *p = i;
    return map[j][w*2+x];
     
}
int main() {
    indexes['K'] = 0;
    indexes['A'] = 1;
    indexes['N'] = 2;
    indexes['C'] = 3;
    indexes['E'] = 4;
    indexes['p'] = 0;
    indexes['q'] = 1;
    indexes['r'] = 2;
    indexes['s'] = 3;
    indexes['t'] = 4;
    char b[128];
    int i, v;
    while(1) {
        scanf("%s", b);
        if (b[0] == '0') break;
        for (v=0; v<32; v++) {
            i = 0;
            if (eval(v, b, &i) == 0) break;
        }
        if (v<32)printf("not\n");
        else printf("tautology\n");
    }
    return 0;
}
