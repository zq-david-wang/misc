#include<stdio.h>

typedef struct _T{
    struct _T* cs[4];
}NNode;
NNode pool[25000*8];
int pc=0;

NNode *root;
void assert(int *p) {
    *p = 0;
}
NNode *alloc() {
    NNode *p = &pool[pc++];
    p->cs[0]=p->cs[1]=p->cs[2]=p->cs[3]=NULL;
    if (pc>=sizeof(pool)/sizeof(pool[0]))assert(NULL);
    return p;
}
void init() {
    pc = 0;
    root = alloc();
}
struct { short x,y,z; }ps[25001];

void addpoint(int x, int y, int z) {
    NNode *p = root;
    int i,b; for (i=0; i<16; i+=2) {
        b = x&3; x>>=2;
        if (p->cs[b]==NULL) p->cs[b] = alloc();
        p = p->cs[b];
    }
    for (i=0; i<16; i+=2) {
        b = y&3; y>>=2;
        if (p->cs[b]==NULL) p->cs[b] = alloc();
        p = p->cs[b];
    }
    for (i=0; i<16; i+=2) {
        b = z&3; z>>=2;
        if (p->cs[b]==NULL) p->cs[b] = alloc();
        p = p->cs[b];
    }
}
int pexist(int x, int y, int z) {
    if (z<0) return 1;
    NNode *p = root;
    int i,b; for (i=0; i<16; i+=2) {
        b = x&3; x>>=2;
        if (p->cs[b]==NULL) return 0;
        p = p->cs[b];
    }
    for (i=0; i<16; i+=2) {
        b = y&3; y>>=2;
        if (p->cs[b]==NULL) return 0;
        p = p->cs[b];
    }
    for (i=0; i<16; i+=2) {
        b = z&3; z>>=2;
        if (p->cs[b]==NULL) return 0;
        p = p->cs[b];
    }
    return 1;
}

char *dir = "LRFBOU";
char steps[6][3] = {
    {-1, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {0, -1, 0},
    {0, 0, 1},
    {0, 0, -1},
};
int main() {
    init();
    int n, i, k;
    int x, y, z, a;
    int nx, ny, nz;
    char d[8], c;
    scanf("%d", &n);
    ps[1].x=0; ps[1].y=0; ps[1].z=0; 
    addpoint(0, 0, 0);
    for (i=2; i<=n; i++) {
        scanf("%d %s", &a, d);
        for (k=0; k<6; k++) if (dir[k]==d[0]) break;
        x = ps[a].x; y = ps[a].y; z = ps[a].z;
        nx = x+steps[k][0];
        ny = y+steps[k][1];
        nz = z+steps[k][2];
        if (pexist(nx, ny, nz)) break;
        ps[i].x=nx; ps[i].y=ny; ps[i].z=nz;
        addpoint(nx, ny, nz);
    }
    if (i<=n) printf("-1\n");
    else {
        int r = 0;
        for (i=1; i<=n; i++) {
            x = ps[i].x; y = ps[i].y; z = ps[i].z;
            if (pexist(x, y, z+1)==0)r++; 
            if (pexist(x, y, z-1)==0)r++; 
            if (pexist(x, y+1, z)==0)r++; 
            if (pexist(x, y-1, z)==0)r++; 
            if (pexist(x+1, y, z)==0)r++; 
            if (pexist(x-1, y, z)==0)r++; 
        }
        printf("%d\n", r);
    }
    return 0;
}
