#include<stdio.h>

char isbn[32];
int main() {
    int mi, i, s=0, c;
    scanf("%s", isbn);
    for (i=0; i<10; i++) {
        if (isbn[i]=='?') mi = i;
        else {
           if (isbn[i] != 'X') c=isbn[i]-'0';
           else c=10; 
           s += c*(10-i);
        }
    }
    for (i=0; i<10; i++) {
        if (((s+(10-mi)*i) % 11)==0) break;
    }
    if (i<10) printf("%d\n", i);
    else{
        if (mi==9 && ((s+10)%11)==0) printf("X\n");
        else printf("-1\n");
    }
    return 0;
}
