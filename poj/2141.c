#include<stdio.h>

char key[26];
char message[128];
int readline(char *buf) {
    int i=0;
    char c;
    while(1) {
        c = getchar();
        if (c==EOF || c=='\n') break;
        buf[i++] = c;
    }
    return i;
}

int main() {
    int i, l;
    char c;
    readline(key);
    l = readline(message);
    for (i=0; i<l; i++) {
        c = message[i];
        if (c>='A'&&c<='Z') {
            c = key[c-'A']-'a'+'A';
        } else if (c>='a'&&c<='z') {
            c = key[c-'a'];
        }
        message[i] = c;
    }
    message[l] = 0;
    printf("%s\n", message);
    return 0;
}
