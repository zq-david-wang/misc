#include<stdio.h>
#include<string.h>

#define MAXC 50000
#define MAXL 20
char buffer[4200000];

#define readline(r) fgets(r, 128, stdin)
#define isend(x) (x==0 || x=='\n' || x=='\r') 
#define isw(x) (x>='A' && x<='Z')


int parse_words(char* l, void (*f)(const char*, int l)) {
    char* s = l;
    int i = 0;
    while (1) {
        if (isend(l[i])) return s-l;
        if (isw(l[i])) {
            s = l+i;
            while(isw(l[i])) i++;
            if (isend(l[i])){
                l[i] = 0;
                f(s, i-(s-l));
                return i;
            }
            l[i] = 0;
            f(s, i-(s-l));
            s = l+i;
        }
        i++;
    }
}


int glstats[22];
int clstats[22];

int solutioncount;
char solution[27];
char rsolution[27];
char saved_solution[27];
char error_flag;


typedef struct _wnode{
    const char* target;
    struct _wnode* cs[26], *p;
    int i, l;
}WNODE;

#define TOTALWLEN 350000
WNODE gwpool[TOTALWLEN+4];
int gwpool_size;

WNODE gdpool[TOTALWLEN+4];
int gdpool_size;

WNODE* walloc() {
    if (gwpool_size > TOTALWLEN) return NULL;
    WNODE* r = &gwpool[gwpool_size++];
    return r;
}
WNODE* root;


WNODE* dalloc() {
    if (gdpool_size > TOTALWLEN) return NULL;
    WNODE* r = &gdpool[gdpool_size++];
    return r;
}
WNODE* droot;

const char* cdict[22][MAXC];
const char* gdict[22][MAXC];

void ginit() {
    memset(glstats, 0, sizeof(glstats));
    memset(gdpool, 0, sizeof(gdpool));
    gdpool_size = 0;
    droot = dalloc();
}

void init() {
    gwpool_size = 0;
    memset(clstats, 0, sizeof(clstats));
    memset(gwpool, 0, sizeof(gwpool));
    root = walloc();
}


WNODE* _next_word(WNODE* c) {
    if (c->target != NULL) return c;
    int i; for(i=0;i<26;i++) if (c->cs[i] != NULL) return _next_word(c->cs[i]);
    // this should not happen.
    return NULL;

}
WNODE* next_word(WNODE* c, int s) {
    int i; for(i=s;i<26;i++) if (c->cs[i] != NULL) return _next_word(c->cs[i]);
    // no childern found, back trace
    if (c->p == NULL) return NULL;
    return next_word(c->p, c->i+1);
}


WNODE* find_match(WNODE* n, const char* w, int wilds) {
    char c, rc;
    int s = n->l, i;
    WNODE* rn;
    c = w[s];
    if (c == 0) {
        if (n->target != NULL) return n;
        return NULL;
    }
    rc = solution[c-'A'];
    if (rc == '*') {
        for (i=wilds; i<26; i++) {
            if (n->cs[i] == NULL) continue;
            if (rsolution[i] != '*') continue;
            rn = find_match(n->cs[i], w, 0);
            if (rn != NULL) return rn;
        }
    } else {
        if (n->cs[rc-'A'] == NULL) return NULL;
        if (wilds <= rc-'A') return find_match(n->cs[rc-'A'], w, 0);
    }
    return NULL;
}
WNODE* next_match(WNODE* n, const char* w) {
    WNODE* p = n->p, *r;
    while(p != NULL) {
        r = find_match(p, w, n->i+1);
        if (r!=NULL) return r;
        n = p;
        p = n->p;
    }
    return NULL;
}

int list_word() {
    WNODE* n = root;
    int l;
    while(1) {
        n = next_word(n, 0);
        if (n==NULL)break;
        // add the word.
        l = n->l;
        if (l > 20) return 1;
        cdict[l][clstats[l]++] = n->target;
        // printf("%s\n", n->target);
    } 
    return 0;
}


void dfs(int l, int iw) {
    // printf("dfs %d  %d\n", l, iw);
    int i, j, k, ki;
    char backup[26], tc, rbackup[26], backupc, rbackupc;
    const char *w, *d;
    int c1, c2;
    int wilds[24], wildc = 0;
    WNODE* n;
    for (i=l; i>0; i--){
        // printf("size: %d/%d:%d\n", i, clstats[i], iw);
        for (j=iw; j<clstats[i]; j++){
            w = cdict[i][j];
            // printf("check %d/%d  %s\n", i, j, w);
            n = find_match(droot, w, 0);
            // printf("after find match\n");
            if (n == NULL) return;
            wildc = 0;
            backupc = rbackupc = 0;
            for (k=0; k<i; k++) if (solution[w[k]-'A'] =='*') wilds[wildc++]=k;
            if (wildc == 0)continue;
            for (k=0; k<26; k++) if (solution[k] == '*') backup[backupc++]=k;
            for (k=0; k<26; k++) if (rsolution[k] == '*') rbackup[rbackupc++]=k;
            while (n != NULL) {
                // check current map w:n->target
                // printf("try %s match %s\n", w, n->target);
                d = n->target;
                for (k=0; k<wildc; k++) {
                    ki = wilds[k];
                    // w[ki] <-> d[ki]
                    if (solution[w[ki]-'A'] == '*' && rsolution[d[ki]-'A'] == '*') {
                        solution[w[ki]-'A'] = d[ki];
                        rsolution[d[ki]-'A'] = w[ki];
                    } else {
                        if (solution[w[ki]-'A'] != d[ki] || \
                                rsolution[d[ki]-'A'] != w[ki] )break;
                    }
                }
                if (k>=wildc) dfs(i, j+1);
                if (error_flag == 1)return;
                for (k=0; k<backupc; k++) {
                    solution[backup[k]]='*';
                    rsolution[rbackup[k]]='*';
                }
                n = next_match(n, w);
            }
            return;
        }
        iw = 0;
    }
    // check solution
    {
        // printf("find a solution\n");
        if (solutioncount > 0) {
            // compare solution
            for (j=0;j<26;j++) {
                if (saved_solution[j] != rsolution[j]) break;
            }
            if (j<26) {
                error_flag = 1;
            }
            return;
        }
        for (j=0; j<26; j++) saved_solution[j] = rsolution[j];
        solutioncount = 1;
        return;
    }
}

void process() {
    int i;
    i = list_word();
    if (i != 0) {
        printf("#No solution#\n");
        return;
    }
    for (i=1; i<=20; i++) {
        if (clstats[i] > glstats[i])break;
    }
    if (i<=20) {
        printf("#No solution#\n");
        return;
    }
    // start dfs
    solutioncount = 0;
    for (i=0; i<26; i++)solution[i] = '*';
    for (i=0; i<26; i++)rsolution[i] = '*';
    error_flag = 0;
    dfs(20, 0);
    if (error_flag == 0) {
        if (solutioncount == 1){
            saved_solution[26] = 0;
            printf("%s\n", saved_solution);
        } else {
            printf("#No solution#\n");
        }
    } else {
        printf("#More than one solution#\n");
    }
}


void add_dict(const char* w, int l) {
    if (l>20) return;
    gdict[l][glstats[l]] = w;
    int i, j;
    if (glstats[l] > 0) {
        const char* lw = gdict[l][glstats[l]-1];
        i = 0; while(w[i] != 0) {
            if (lw[i] != w[i])break;
            i++;
        }
        // duplicated word
        if (w[i] == lw[i])return;

    }
    glstats[l]++;
    WNODE* n = droot;
    for (i=0; i<l; i++){
        j = w[i] - 'A';
        if (n->cs[j] == NULL) {
            n->cs[j] = dalloc();
            n->cs[j]->i = j;
            n->cs[j]->p = n;
            n->cs[j]->l = i+1;
        }
        n = n->cs[j];
    }
    n->target = w;
}


void add_word(const char* w, int l) {
    // printf("add word %s/%d\n", w, l);
    WNODE* n = root;
    int i, j; for (i=0; i<l; i++){
        j = w[i] - 'A';
        if (n->cs[j] == NULL) {
            n->cs[j] = walloc();
            if (n->cs[j] == NULL) printf("!!!!\n");
            n->cs[j]->i = j;
            n->cs[j]->p = n;
        }
        n = n->cs[j];
    }
    n->target = w;
    n->l = l;
    //printf("add_word %s done, total %d\n", w, gwpool_size );
}

int main()
{
    int c, i, j;
    char *b = buffer, *r, *b2;
    ginit();
    r = readline(b);
    sscanf(r, "%d", &c);
    for (i=0; i<c; i++){
        r = readline(b);
        j=parse_words(r, add_dict);
        b += (j+1);
    }
    r = readline(b);
    sscanf(r, "%d", &c);
    // skip first blank line.
    readline(b);
    for (i=0; i<c; i++) {
        init();
        // read until blank or EOF
        while (1) {
            r = readline(b);
            if (r == NULL) break;
            j = parse_words(r, add_word);
            if (j==0) break;
            b += (j+1);
        }
        process();
    }
}
