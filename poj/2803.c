#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char word[128];
void postfix(int s, int e) {
    int l = e-s+1;
    if (l>2 && strncmp(word+e-1, "er", 2)==0) {
        word[e-1]=0;
        printf("one who %ss", word+s);
    } else if (l>3 && strncmp(word+e-2, "ing", 3)==0) {
        word[e-2]=0;
        printf("to actively %s", word+s);
    } else if (l>3 && strncmp(word+e-2, "ize", 3)==0) {
        word[e-2]=0;
        printf("change into %s", word+s);
    } else if (l>1 && word[e]=='s') {
        word[e]=0;
        printf("multiple instances of %s", word+s);
    } else if (l>4 && strncmp(word+e-3, "tion", 4)==0) {
        word[e-3]=0;
        printf("the process of %sing", word+s);
    } else printf("%s", word+s);
}
void prefix() {
    int l = strlen(word);
    if (strncmp(word, "anti", 4)==0) {
        printf("against "); postfix(4, l-1); printf("\n");
    } else if (strncmp(word, "post", 4)==0) {
        printf("after "); postfix(4, l-1); printf("\n");
    } else if (strncmp(word, "pre", 3)==0) {
        printf("before "); postfix(3, l-1); printf("\n");
    } else if (strncmp(word, "re", 2)==0) {
        postfix(2, l-1); printf(" again\n");
    } else if (strncmp(word, "un", 2)==0) {
        printf("not "); postfix(2, l-1); printf("\n");
    } else {
        postfix(0, l-1);  printf("\n");
    }
}
int main() {
    int tc, ti;
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        scanf("%s", word);
        prefix();
    } 
    return 0;
}


