#include<stdio.h>

char lines[400][256];
char instack[500], valid[500];
int nei[500];
int lvl[500], glevel, low[500];
int tags[400];
char mark[500];
#define MOD 512
int stack[MOD], stop;
struct {short n, b; } pool[400*20];
int pc;

void tarjan(int a) {
    lvl[a] = low[a] = glevel; glevel++;
    stack[stop++] = a; instack[a]=1;
    int b, i, n = nei[a];
    while(n!=-1) {
        b=pool[n].b;
        if (lvl[b]==0) {
            tarjan(b);
            if (low[a]>low[b]) low[a]=low[b];
        } else if (instack[b]) {
            if (low[a]>low[b]) low[a]=low[b];
        }
        n=pool[n].n;
    } 
    if (low[a]==lvl[a]) {
        int c=0;
        while(stop) {
            b = stack[--stop];
            instack[b]=0;
            valid[b]=0;
            c++;
        }
        if (c==1) {
            // single 
            valid[a]=1;
            n=nei[a]; while(n!=-1) {
                b=pool[n].b;
                if (valid[b]==0) { valid[a]=0; break; }
                n=pool[n].n;
            }
        }
    }
}
int main() {
    int n=0, i, j, k; 
    int a, b;
    while(scanf("%s", lines[n])==1) n++;
    pc=0; 
    for (i=0; i<500; i++) { nei[i]=-1; mark[i]=0; }
    for (i=0; i<n; i++) {
        j=0; while(lines[i][j]!='=')j++; lines[i][j]=0;
        k=0; while(lines[i][k]!='R')k++;
        a = ((lines[i][k+1]-'0')*10+lines[i][k+2]-'0')*20+(lines[i][k+4]-'0')*10+lines[i][k+5]-'0';
        k=j+1; while(1) {
            while(lines[i][k]!='R' && lines[i][k]!=0) k++;
            if (lines[i][k]==0) break;
            b = ((lines[i][k+1]-'0')*10+lines[i][k+2]-'0')*20+(lines[i][k+4]-'0')*10+lines[i][k+5]-'0';
            if (b==a) mark[a]=1;
            else {pool[pc].b=b; pool[pc].n=nei[a]; nei[a]=pc; pc++;}
            k++;
            // printf("connect %d->%d\n", a ,b);
        }
        tags[i]=a;
        lvl[a]=0; instack[a]=0; valid[a]=1;
    }
    glevel=1; stop=0;
    for (i=0; i<n; i++) {
        a = tags[i]; if (lvl[a]) continue;
        tarjan(a);
    }
    for (i=0;i<n; i++) {
        a = tags[i];
        if (valid[a]==0||mark[a]) printf("%s circular\n", lines[i]);
        else printf("%s ok\n", lines[i]);
    }
    return 0;
}
