#include<stdio.h>
#include<string.h>

char spei[20][24];
char speo[20][24];

char word[32];

char *owl="aeiou";
int main() {
    int l, n, i, j, k, ii;
    scanf("%d %d", &l, &n);
    for (i=0; i<l; i++) scanf("%s %s", spei[i], speo[i]);
    for (i=0; i<n; i++) {
        scanf("%s", word);
        for (k=0; k<l; k++) {
            if (strcmp(word, spei[k])==0) {
                printf("%s\n", speo[k]);
                break;
            }
        }
        if (k<l) continue;
        k = strlen(word);
        if (k>1 && word[k-1]=='y') {
            for (ii=0; ii<5; ii++) if (owl[ii]==word[k-2]) break;
            if (ii==5) {
                word[k-1]=0;
                printf("%sies\n", word);
                continue;
            }
        }
        if (word[k-1]=='o'||word[k-1]=='s'||word[k-1]=='x') {
            printf("%ses\n", word);
            continue;
        }
        if (k>1 && word[k-1]=='h'&&(word[k-2]=='c'||word[k-2]=='s')) {
            printf("%ses\n", word);
            continue;
        }
        printf("%ss\n", word);
    }
    return 0;
}
