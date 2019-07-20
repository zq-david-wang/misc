#include<stdio.h>
#include<string.h>

char nums[16][82000];
int ls[16];
void build() {
    sprintf(nums[0], "{}");
    ls[0]=2;
    char *p;
    int i, j; for (i=1; i<=15; i++) {
        p = nums[i];
        p += sprintf(p, "{{}");
        for (j=1; j<i; j++) {
            p += sprintf(p, ",%s", nums[j]);
        }
        sprintf(p, "}");
        ls[i] = strlen(nums[i]);
        // printf("%d:%d\n", i, ls[i]);
    }
}
char line[82000];
int main() {
    build();
    int n, i, a, b, l;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%s", line); l = strlen(line);
        for (a=0; a<=15;a++) if (l==ls[a]) break;
        if (a>15) { printf("a not foudn\n"); break; }
        scanf("%s", line); l = strlen(line);
        for (b=0; b<=15 ;b++) if (l==ls[b]) break;
        if (b>15) { printf("b not foudn\n"); break; }
        printf("%s\n", nums[a+b]);
    }
    return 0;
}
