#include<stdio.h>

int gn, gc;
char op[16];
void printexp() {
    int i; printf("1");
    for (i=2; i<=gn; i++) printf(" %c %d", op[i-1], i);
    printf("\n");
}
void dfs(int s, int a, int b, int o) {
    if (s==gn) {
        if (o==0) {
            a += b; if (a==0) { gc++; if (gc<=20) printexp(); }
        } else {
            a -= b; if (a==0) {gc++; if (gc<=20) printexp(); }
        }
        return;
    }
    op[s] = '+';
    if (o==0) dfs(s+1, a+b, s+1, 0);
    else dfs(s+1, a-b, s+1, 0);
    op[s] = '-';
    if (o==0) dfs(s+1, a+b, s+1, 1);
    else dfs(s+1, a-b, s+1, 1);
    op[s] = '.';
    if (s>=9) dfs(s+1, a, b*100+s+1, o);
    else dfs(s+1, a, b*10+s+1, o);
}
int main() {
    int n; 
    scanf("%d", &n);
    gn = n; gc=0;
    dfs(1, 0, 1, 0);
    printf("%d\n", gc);
    return 0;
}
