#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char line[512];
int readline() {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        line[i++]=c;
    }
    line[i]=0;
    return i;
}
struct { char text[260]; char c1, c2, flag, n; } lines[128];
int dfs(int s) {
    if (lines[s].c1==0) return 1;
    if (lines[s].c1==-1) return 0;
    int c = lines[s].c1;
    if (lines[c].flag==0) {
        lines[c].flag=1;
        if (dfs(c)) { lines[s].n = c; return 1; }
    }
    c = lines[s].c2;
    if (lines[c].flag==0) {
        lines[c].flag=1;
        if (dfs(c)) { lines[s].n = c; return 1; }
    }
    return 0;
}
int main() {
    int tc, ti, n, i, j1, j2, c1, c2;
    readline();
    sscanf(line, "%d", &tc); for (ti=1; ti<=tc; ti++) {
        readline();
        sscanf(line, "%d", &n);
        for (i=1; i<=n; i++) {
            lines[i].flag=0;
            readline();
            j1 = 1; while(line[j1]!='"') j1++; j1++;
            j2 = j1; while(line[j2]!='"') j2++; j2--;
            strncpy(lines[i].text, line+j1, j2-j1+1); lines[i].text[j2-j1+1]=0;
            if (line[0]=='C') {
                sscanf(line+j2+2, "%d %d", &c1, &c2);
                lines[i].c1=c1; lines[i].c2=c2;
            } else {
                j2+=2; while(line[j2]==' ')j2++;
                if (line[j2]=='G') lines[i].c1=-1;
                else lines[i].c1=0;
            }
        }
        lines[1].flag=1; dfs(1);
        printf("STORY %d\n", ti);
        i=1; while(1) {
            printf("%s\n", lines[i].text);
            if (lines[i].c1==0) break;
            i = lines[i].n;
        }
    }
    return 0;
}


