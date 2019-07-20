#include<stdio.h>
#include<string.h>


typedef struct _T {
    struct _T *next, *prev, *head, *tail;
    char name[24];
}ENode;
ENode pool[1024];
ENode *freelist;

void init() {
    freelist = NULL;
    int i; for (i=0; i<sizeof(pool)/sizeof(pool[0]); i++) {
        pool[i].next = freelist;
        freelist = &pool[i];
    }
}

ENode *alloc() {
    ENode *p = NULL;
    if (freelist) {
        p = freelist;
        freelist = freelist->next;
        p->next = p->head = p->tail = p->prev = NULL;
    }
    return p;
}

void dealloc(ENode *p) {
    p->next = freelist;
    freelist = p;
}

char line[128];
int readline() {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c=='\n'|| c==EOF) break;
        line[i++] = c;
    }
    line[i]=0;
    return i;
}
char b1[32], b2[32], b3[32];
char hire(ENode *r, char *bn, char *en) {
    if (r==NULL) return 0;
    char *p = r->name;
    int i=0; while(1) {
        if (p[i]!=bn[i]) break;
        if (bn[i]==0) break;
        i++;
    }
    if (p[i]==bn[i]) {
        ENode *n = alloc();
        i=0; while(1) { n->name[i]=en[i]; if (en[i]==0) break; i++; }
        if (r->head==NULL) {
            r->head=r->tail = n;
        } else {
            r->tail->next = n;
            n->prev = r->tail;
            r->tail = n;
        }
        return 1;
    }
    ENode *t = r->head;
    while(t!=NULL) {
        if (hire(t, bn, en)) return 1;
        t = t->next;
    }
    return 0;
}

char fire(ENode *r, char *n, ENode *boss) {
    ENode *p = r->head;
    if (strcmp(r->name, n)==0) {
        // promt child if any
        if (p!=NULL) {
            // no need to make change to its parent
            int i; for (i=0; i<24; i++) r->name[i]=p->name[i];
            fire(p, r->name, r);
        } else {
            if (r->next==NULL&&r->prev==NULL) { boss->head=NULL; boss->tail=NULL; }
            else {
                if (boss->head == r) { boss->head = r->next; r->next->prev = NULL; }
                else if (boss->tail==r) { boss->tail=r->prev; r->prev->next=NULL; }
                else {
                    r->prev->next = r->next;
                    r->next->prev = r->prev;
                }
            }
            dealloc(r);
        }
        return 1;
    }
    while(p!=NULL) {
        if (fire(p, n, r)) return 1;
        p = p->next;
    }
    return 0;
}
char sep[80];
char mark[128];
void iprint(ENode *p, int l) {
    if (p==NULL) return;
    mark[l]=0; printf("%s%s\n", mark, p->name); mark[l]='+';
    ENode *cp = p->head;
    while(cp!=NULL) {
        iprint(cp, l+1);
        cp = cp->next;
    }
}
void printit(ENode *ceo) {
    iprint(ceo, 0);
    printf("%s\n", sep);
}
int main() {
    init();
    int i, j;
    for (i=0; i<60; i++) sep[i]='-'; sep[i]=0;
    for (i=0; i<128; i++) mark[i]='+';
    readline();
    sscanf(line, "%s", b1);
    // add CEO
    ENode *ceo = alloc();
    i=0; while(1) {
        ceo->name[i] = b1[i];
        if (b1[i]==0) break;
        i++;
    }
    while(readline()!=0) {
        j = sscanf(line, "%s %s %s", b1, b2, b3);
        if (j==1) { printit(ceo); }
        else if (j==2) {
            fire(ceo, b2, NULL);
        } else {
            hire(ceo, b1, b3);
        }
    }
    return 0;
}
