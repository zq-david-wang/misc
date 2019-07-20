#include<stdio.h>

char line[256];
void opit(char *a, char *b, char op) {
    int j; if (op=='+') { for (j=0;j<26; j++) if (b[j]) a[j]=1; }
    else if (op=='-') { for (j=0;j<26;j++) if (b[j]) a[j]=0; }
    else {
        for (j=0; j<26; j++) {
            if (a[j]) { if (b[j]==0) a[j]=0; }
        }
    }
}
int process(int s, char *o) {
    char b[26], c[26], op1='+', op2, f=0;
    char *p;
    int i=s, j; for (j=0; j<26; j++) b[j]=0;
    while(1) {
        if (line[i]==0) break;
        if (line[i]=='(') {
            if (f==0) p=b; else p=c;
            for (j=0; j<26; j++) p[j]=0;
            i=process(i+1, p)+1;
        } else if (line[i]=='{') {
            if (f==0) p=b; else p=c;
            for (j=0; j<26; j++) p[j]=0;
            i++; while(line[i]!='}') { p[line[i]-'A']=1; i++; } i++;
        } else if (line[i]=='+'||line[i]=='-'||line[i]=='*') {
            if (f==0) { f=1;}
            else {
                if (op2=='*') opit(b, c, op2);
                else {
                    opit(o, b, op1);
                    for (j=0; j<26; j++) b[j]=c[j];
                    op1=op2;
                }
            }
            op2 = line[i]; i++;
        } else break;
    }
    if (f==0) opit(o, b, op1);
    else {
        if (op2=='*') { opit(b, c, op2); opit(o, b, op1); }
        else {
            opit(o, b, op1);
            for (j=0; j<26; j++) b[j]=c[j];
            opit(o, b, op2);
        }
    }
    // printf("%d: {", s); for (j=0; j<26; j++) if (o[j]) printf("%c", j+'A'); printf("}\n");
    return i;
}
int main() {
    char cs[26], i;
    while(scanf("%s", line)==1) {
        for (i=0; i<26; i++) cs[i]=0;
        process(0, cs);
        printf("{"); for (i=0; i<26; i++) if (cs[i]) printf("%c", i+'A'); printf("}\n");
    }
    return 0;
}
