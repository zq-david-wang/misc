#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char map[16][32];
char rpos[16][32], cpos[16][32];
char words[100][128];
int cs[32], wcs[32];
char flag[128];
char wci[16][100];
typedef struct _T{
    struct _T *cs[26];
    char cc[26];
    int i;
}WNode;
WNode wpool[100*26];
int wpc;
WNode *root[16];
WNode *wrpos[16][16];
WNode *wcpos[16][16];
WNode *alloc() {
    WNode *p = &wpool[wpc++];
    int i; for (i=0; i<26; i++) { p->cs[i]=NULL; p->cc[i]=0; }
    p->i = -1;
    return p;
}
void init() {
    wpc=0;
    int i; for (i=0; i<16; i++) root[i] = alloc();
}
void addword(WNode *p, char *w, int i) {
    char c;
    while(1) {
        c = *w++;
        if (c==0) break; c-='A';
        p->cc[c]++;
        if (p->cs[c]==NULL) p->cs[c]=alloc();
        p=p->cs[c];
    }
    p->i=i;
}
int findi(WNode *p, char *w) {
    char c;
    while(1) {
        c = *w++;
        if (c==0) break; c-='A';
        if (p->cs[c]==NULL) return -1;
        p=p->cs[c];
    }
    return p->i;
}
int dfs(int r, int c, int h, int w) {
    int i;
    WNode *pr, *pc;
    while(1) {
        if (c>=w) { c=0; r++; }
        if (r==h) break;
        if (wrpos[r][c]||wcpos[r][c]) break;
        c++;
    }
    if (r==h) return 1;
    pr = wrpos[r][c];
    pc = wcpos[r][c];
    if (pr) {
        if (pc) {
            for (i=0; i<26; i++) {
                if (pr->cc[i]&&pc->cc[i]) {
                    // try i
                    map[r][c]=i+'A';
                    pr->cc[i]--; pc->cc[i]--;
                    if (pr->cs[i]->i<0) wrpos[r][c+1]=pr->cs[i];
                    if (pc->cs[i]->i<0) wcpos[r+1][c]=pc->cs[i];
                    if (dfs(r, c+1, h, w)) return 1;
                    pr->cc[i]++; pc->cc[i]++;
                } 
            }
        } else {
            for (i=0; i<26; i++) {
                if (pr->cc[i]==0) continue;
                map[r][c]=i+'A';
                pr->cc[i]--;
                if (pr->cs[i]->i<0) wrpos[r][c+1] = pr->cs[i];
                if (dfs(r, c+1, h, w)) return 1;
                pr->cc[i]++;
            }
        }
    } else {
        for (i=0; i<26; i++) {
            if (pc->cc[i]==0) continue;
            map[r][c]=i+'A';
            pc->cc[i]--;
            if (pc->cs[i]->i<0) wcpos[r+1][c] = pc->cs[i];
            if (dfs(r, c+1, h, w)) return 1;
            pc->cc[i]++;
        }
    }
    return 0;
}
int main() {
    int tc, ti, i, j, w, h, l, n, c;
    scanf("%d", &tc); for (ti=1; ti<=tc; ti++) {
        printf("Puzzle #%d\n", ti);
        init();
        scanf("%d %d", &w, &h);
        for (i=0; i<h; i++) scanf("%s", map[i]);
        // for (i=0; i<h; i++) for (j=0; j<w; j++) rpos[i][j]=cpos[i][j]=0;
        for (i=0; i<h; i++) for (j=0; j<w; j++) { wrpos[i][j]=NULL; wcpos[i][j]=NULL; }
        for (i=0; i<32; i++) cs[i]=0;
        for (i=0; i<h; i++) {
            j=0; while(j<w) {
                while(j<w&&map[i][j]=='.')j++; if(j>=w) break;
                c=0; while(j+c<w&&map[i][j+c]=='#') c++;
                if (c>1) { cs[c]++; wrpos[i][j]=root[c]; } 
                j += c;
            }
        }
        for (i=0; i<w; i++) {
            j=0; while(j<h) {
                while(j<h&&map[j][i]=='.')j++; if(j>=h) break;
                c=0; while(j+c<h&&map[j+c][i]=='#') c++;
                if (c>1) { cs[c]++; wcpos[j][i]=root[c]; }
                j += c;
            }
        }
        scanf("%d", &n);
        for (i=0; i<32; i++) wcs[i]=0; wcs[0]=1;
        for (i=0; i<n; i++) { 
            scanf("%s", words[i]);
            l = strlen(words[i]);
            addword(root[l], words[i], i);
            if (l<16) wci[l][wcs[l]]=i;
            if (l>=31) wcs[31]=100;
            else wcs[l]++;
            flag[i]=0;
        }
        for (i=1; i<32; i++) if (wcs[i]!=cs[i]) break;
        if (i==32&&dfs(0, 0, h, w)) {
            for (i=0; i<h; i++) printf("%s\n", map[i]);
        } else printf("I cannot generate this puzzle.\n");
    }
    return 0;
}


