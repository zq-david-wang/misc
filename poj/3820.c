#include<stdio.h>

char buf[40960];
int readline() {
    int i=0;
    char c;
    while(1) {
        c=getchar();
        if (c==EOF||c=='\n') break;
        buf[i++]=c;
    }
    buf[i]=0;
    if (i==0 && c==EOF) return -1;
    return i;
}
char map[128];
char ishex(char c) {
    return map[c]&1;
}
char istag(char c) {
    return map[c]&2;
}
char *stack[128];
int stop;
int main() {
    int l, i, v, j, k;
    char *p;
    for (i=0; i<128; i++) map[i]=0;
    for (i='0'; i<='9'; i++) map[i]|=3;
    for (i='a'; i<='f'; i++) map[i]|=1;
    for (i='a'; i<='z'; i++) map[i]|=2;
    for (i='A'; i<='F'; i++) map[i]|=1;
    while(1) {
        l = readline(); if (l==-1) break;
        stop=0;
        v=1; i=0; while(i<l) {
            if (buf[i]=='<') {
                for (j=i+1; j<l; j++) if (buf[j]=='>') break;
                if (j==l) {v=0; break;}
                if (buf[i+1]=='/') {
                    if (stop) {
                        p = stack[stop-1];
                        for (k=0;;k++) {
                            if (p[k]!=buf[i+1+1+k]) { break; }
                            if (i+2+k==j) break;
                        }
                        if (i+2+k==j) stop--;
                        else { if (i+2!=j) { v=0; break; } }
                        i=j+1;
                    } else {
                        if (i+2!=j) { v=0; break; }
                        i=j+1;
                    }
                } else {
                    if (buf[j-1]=='/') {
                        for (k=i+1; k<j-1; k++) {
                            if (istag(buf[k])==0) break;
                        }
                        if (k<j-1) { v=0; break; }
                        i=j+1;
                    } else {
                        p = buf+i+1;
                        for (k=i+1; k<j; k++) {
                            if (istag(buf[k])==0) break;
                        }
                        if (k<j) { v=0; break; }
                        stack[stop++]=p;
                        i = j+1;
                    }
                }
            } else if (buf[i]=='&') {
                i++; if (buf[i]=='l'&&buf[i+1]=='t') i+=2;
                else if (buf[i]=='g'&&buf[i+1]=='t') i+=2;
                else if (buf[i]=='a'&&buf[i+1]=='m'&&buf[i+2]=='p') i+=3;
                else if (buf[i]=='x') {
                    i++; for (k=i; k<=l; k++) if (ishex(buf[k])==0) break;
                    // printf("hex(%d->%d) %s\n%s\n", i, k, buf+i, buf+k);
                    if ((k-i)&1) { v=0; break; }
                    i=k;
                } else { v=0; break; }
                if (buf[i]!=';') { v=0; break; }
                i++;
            } else {
                if (buf[i]<32|| buf[i]>127 || buf[i]=='>') { v=0; break; }    
                i++;
            }
        }
        if (stop) v=0;
        if (v) printf("valid\n"); else printf("invalid\n");
    }
    return 0;
}
