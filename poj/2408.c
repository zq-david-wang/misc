#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char buf[30000*80];
char cs[30000*27];
typedef struct {
    char *s, *c;
}WNode;
WNode words[30000];
int mycmp(const void *a, const void*b) {
    const WNode *pa = (const WNode*)a;
    const WNode *pb = (const WNode*)b;
    int i; for (i=0; i<26; i++) if (pa->c[i]!=pb->c[i]) return pa->c[i]-pb->c[i];
    return strcmp(pa->s, pb->s);
}
typedef struct {
    int s, c;
}GNode;
GNode groups[30000];
int mycmp2(const void *a, const void *b) {
    const GNode *pa = (const GNode*)a;
    const GNode *pb = (const GNode*)b;
    if (pa->c != pb->c) return pb->c - pa->c;
    return strcmp(words[pa->s].s, words[pb->s].s);
}

int main() {
    int c, i, wc=0;
    char *w, *wcs;
    w = buf;
    wcs = cs;
    while(scanf("%s", w)!=EOF) {
        for (i=0; i<26; i++) wcs[i] = 0;
        c=0; while(w[c]!=0) {
            wcs[w[c]-'a']++;
            c++;
        }
        words[wc].s = w;
        words[wc].c = wcs;
        wc++;
        w += (c+1);
        wcs += 26;
    }
    qsort(words, wc, sizeof(words[0]), mycmp);
    int gc = 0, s = 0, j;
    for (i=1; i<wc; i++) {
        for (j=0; j<26; j++) if (words[i].c[j]!=words[s].c[j]) break;
        if (j<26) {
            groups[gc].s=s;
            groups[gc].c = i-s;
            gc++; s=i;
        } 
    }
    groups[gc].s = s;
    groups[gc].c = i-s;
    gc++;
    qsort(groups, gc, sizeof(groups[0]), mycmp2);
    if (gc>5) gc=5;
    for (i=0; i<gc; i++) {
        printf("Group of size %d: ", groups[i].c);
        for (j=0; j<groups[i].c; j++) { 
            if (j>0 && strcmp(words[groups[i].s+j].s, words[groups[i].s+j-1].s)==0) continue;
            printf("%s ", words[groups[i].s+j].s);
        }
        printf(".\n");
    }
    return 0;
}
