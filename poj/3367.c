#include<stdio.h>

typedef struct _T {
    struct _T *left, *right;
    char op, v;
}CNode;
CNode pool[10008];
int pc;

char expline[10008];
char outline[10008];
CNode *stack[10008];
int main() {
    int n, i, stop, j, c;
    int head, tail;
    CNode *p;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%s", expline);
        pc=0; stop=0;
        j=0; while(1) {
            c = expline[j];
            if (c==0) break;
            j++;
            p = &pool[pc++];
            if (c>='a'&&c<='z') {
                p->left = NULL; p->right = NULL;
                p->op = 0; p->v = c;
                stack[stop++] = p;
            } else {
                p->left = stack[--stop];
                p->right = stack[--stop];
                p->op = c;
                stack[stop++] = p;
            }
        }
        p = stack[0]; outline[j--]=0;
        head=tail=0; stack[head++] = p;
        while(tail<head) {
            p = stack[tail++];
            c = p->op; if (c==0) c=p->v;
            outline[j--]= c;
            if (p->right) stack[head++] = p->right;
            if (p->left) stack[head++] = p->left;
        }
        printf("%s\n", outline);
    } 
    return 0;
}
