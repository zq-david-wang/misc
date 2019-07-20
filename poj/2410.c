#include<stdio.h>

short memory[32];
char buf[16];
int main() {
    int i, v, j, pc, acc, ins, opr;
    while(1) {
        for (i=0; i<32; i++) {
            if (scanf("%s", buf)==EOF) break;
            v = 0;
            for (j=0; j<8; j++) v=v*2+buf[j]-'0';
            memory[i] = v;
        }
        if (i<32) break;
        pc = 0; acc = 0;
        while(1) {
            v = memory[pc];
            pc++; pc &= 0x1f;
            ins = v>>5;
            opr = v&0x1f;
            // printf("%d <== %d %d, accu: %d\n", pc, ins, opr, acc);
            if (ins==0) memory[opr] = acc;
            else if (ins==1) acc = memory[opr];
            else if (ins==2) { if (acc==0) pc = opr; }
            else if (ins==3) {}
            else if (ins==4) { acc--; acc&=0xff;}
            else if (ins==5) { acc++; acc&=0xff;}
            else if (ins==6) pc = opr;
            else break;
        }
        for (j=0; j<8; j++) buf[7-j]=((acc>>j)&1)+'0';
        buf[8]=0;
        printf("%s\n", buf);
    }
    return 0;
}
