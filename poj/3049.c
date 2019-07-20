#include<stdio.h>

char cmap[26];
char mark[26];
char ccan[26];
char *vow = "aeiou";
char vrc[28], nvrc[28], path[32];
int gl, gc;
void dfs(int s, int c, int vc, int nvc) {
    if (vrc[s]+vc<1) return;
    if (nvrc[s]+nvc<2) return;
    if (c==gl) {
        path[c] = 0;
        printf("%s\n", path);
        return;
    }
    int i; for (i=s; i<gc; i++) {
        path[c] = 'a'+ccan[i];
        if (mark[ccan[i]]) dfs(i+1, c+1, vc+1, nvc);
        else dfs(i+1, c+1, vc, nvc+1);
    }
}
int main() {
    int l, c, i;
    int cc;
    char b[8];
    scanf("%d %d", &l, &c);
    for (i=0; i<26; i++) {
        cmap[i] = 0;
        mark[i] = 0;
    }
    for (i=0; i<c; i++) {
        scanf("%s", b);
        cmap[b[0]-'a'] = 1;
    }
    for (i=0; ;i++) {
        if (vow[i]==0) break;
        mark[vow[i]-'a'] = 1;
    }
    cc=0; for (i=0; i<26; i++) {
        if (cmap[i]==0) continue;
        ccan[cc++] = i;
    }
    vrc[cc] = 0; nvrc[cc] = 0;
    for (i=cc-1; i>=0; i--) {
        vrc[i] = vrc[i+1];
        nvrc[i] = nvrc[i+1];
        if (mark[ccan[i]])vrc[i]++;
        else nvrc[i]++;
    }
    gl = l;
    gc = cc;
    dfs(0, 0, 0, 0);
    return 0;
}
