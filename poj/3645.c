/*
 * =====================================================================================
 *
 *       Filename:  3645.c
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  2019年01月16日 08时47分10秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include<stdio.h>


int readline(char* b) {
    char c;
    int i = 0;
    while(1) {
        c = getchar();
        if (c==EOF || c=='\n') break;
        b[i++] = c;
    }
    b[i] = 0;
    return i;
}

char buffer[256];

double process(const char*b, int* p) {
    int i = *p;
    double vp, va, vb;
    while(b[i] ==' ')i++;
    if (b[i] == 0) return 0;
    if (b[i] == '(') {
        i++; while(b[i] ==' ')i++;
        sscanf(b+i, "%lf", &vp);
        while(b[i] !=' ')i++;
        va = process(b, &i);
        vb = process(b, &i);
        while(b[i] != ')')i++; i++;
        *p = i;
        return vp*(va+vb)+(1-vp)*(va-vb);
    } else {
        sscanf(b+i, "%lf", &vp);
        while((b[i]>='0'&&b[i]<='9') || b[i]=='.' || b[i]=='-')i++;
        *p = i;
        return vp;
    }
}
int main() {
    int i;
    double r;
    while(1) {
        readline(buffer);
        if (buffer[0]=='(' && buffer[1] == ')') break;
        i=0;
        r = process(buffer, &i);
        printf("%.2f\n", r);

    }
    return 0;
}
