#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char op, ma, mb;
    short a, b;
}INode;
#define MOD 8000
INode memory[MOD];

int getop(int s, char m, int v) {
    int addr;
    if (m==0) return v;
    if (m==1) return memory[(s+v)%MOD].b;
    addr = (s+v)%MOD;
    addr = addr+memory[addr].b; addr %=MOD;
    return memory[addr].b;
}
int getaddr(int s, int m, int v) {
    if (m==1) return (s+v)%MOD;
    int addr = (s+v)%MOD;
    addr = addr+memory[addr].b; addr %=MOD;
    return addr;
}
int addrs[2];
int opcmp(int s1, int s2) {
    if (memory[s1].op != memory[s2].op) return 1;
    if (memory[s1].ma != memory[s2].ma) return 1;
    if (memory[s1].mb != memory[s2].mb) return 1;
    if (memory[s1].a != memory[s2].a) return 1;
    if (memory[s1].b != memory[s2].b) return 1;
    return 0;
}
int exec(int p) {
    int s = addrs[p];
    char op, ma, mb;
    short a, b;
    int addra, addrb;
    addrs[p]++; addrs[p] %= MOD;
    op = memory[s].op;
    ma = memory[s].ma;
    mb = memory[s].mb;
    a = memory[s].a;
    b = memory[s].b;
    if (op==0) return 0;
    if (op==1) {
        addrb = getaddr(s, mb, b);
        if (ma==0) memory[addrb].b = a;
        else {
           addra = getaddr(s, ma, a); 
           memory[addrb]=memory[addra];
        }
        return 1;
    }
    if (op==2) {
        addrb = getaddr(s, mb, b);
        if (ma==0) memory[addrb].b += a;
        else {
           addra = getaddr(s, ma, a); 
           memory[addrb].a += memory[addra].a;
           memory[addrb].b += memory[addra].b;
        }
        return 1;
    }
    if (op==3) {
        addra = getaddr(s, ma, a);
        addrs[p] = addra;
        return 1;
    }
    if (op==4) {
        addrb = getaddr(s, mb, b);
        if (memory[addrb].b==0) {
            addra = getaddr(s, ma, a);
            addrs[p] = addra;
        }
        return 1;
    }
    if (op==5) {
        addrb = getaddr(s, mb, b);
        if (ma==0) {
            if (a<memory[addrb].b) { addrs[p]++; addrs[p]%=MOD; }
        } else {
            addra = getaddr(s, ma, a);
            if (memory[addra].b < memory[addrb].b) { addrs[p]++; addrs[p]%=MOD; }
        }
        return 1;
    }
    if (op==6) {
        addra = getaddr(s, ma, a);
        addrb = getaddr(s, mb, b);
        if (opcmp(addra, addrb)==0) { addrs[p]++; addrs[p]%=MOD; }
        return 1;
    }
    return 1;

}

int main() {
    int ti, tc, i, j, k;
    int c, v;
    int addr1, addr2, p;
    char cmd[8], op1[8], op2[8];
    scanf("%d", &tc); for (ti=0; ti<tc; ti++) {
        memset(memory, 0, sizeof(memory));
        scanf("%d %d", &c, &addr1);
        addr1 %= MOD; k=addr1;
        for (i=0; i<c; i++) {
            scanf("%s %s %s", cmd, op1, op2);
            // printf("----%s %s %s\n", cmd, op1, op2);
            switch(cmd[0]) {
                case 'D':
                    memory[k].op=0;
                    break;
                case 'M':
                    memory[k].op=1;
                    break;
                case 'A':
                    memory[k].op=2;
                    break;
                case 'S':
                    memory[k].op=5;
                    break;
                case 'C':
                    memory[k].op=6;
                    break;
                default:
                    if (cmd[2]=='P') memory[k].op=3;
                    else memory[k].op=4;
                    break;
            }
            sscanf(op1+1, "%d", &v); v%=MOD; v=(v+MOD)%MOD; memory[k].a=v;
            sscanf(op2+1, "%d", &v); v%=MOD; v=(v+MOD)%MOD; memory[k].b=v;
            if (op1[0]=='#') memory[k].ma=0;
            else if (op1[0]=='$') memory[k].ma=1;
            else memory[k].ma=2;
            if (op2[0]=='#') memory[k].mb=0;
            else if (op2[0]=='$') memory[k].mb=1;
            else memory[k].mb=2;
            // printf("%d: %d %d %d %d %d\n", k, memory[k].op, memory[k].ma, memory[k].a, memory[k].mb, memory[k].b);
            k++; k%=MOD;
        }
        // load 2
        scanf("%d %d", &c, &addr2);
        addr2 %= MOD; k=addr2;
        for (i=0; i<c; i++) {
            scanf("%s %s %s", cmd, op1, op2);
            // printf("-------%s %s %s\n", cmd, op1, op2);
            switch(cmd[0]) {
                case 'D':
                    memory[k].op=0;
                    break;
                case 'M':
                    memory[k].op=1;
                    break;
                case 'A':
                    memory[k].op=2;
                    break;
                case 'S':
                    memory[k].op=5;
                    break;
                case 'C':
                    memory[k].op=6;
                    break;
                default:
                    if (cmd[2]=='P') memory[k].op=3;
                    else memory[k].op=4;
                    break;
            }
            sscanf(op1+1, "%d", &v); v%=MOD; v=(v+MOD)%MOD; memory[k].a=v;
            sscanf(op2+1, "%d", &v); v%=MOD; v=(v+MOD)%MOD; memory[k].b=v;
            if (op1[0]=='#') memory[k].ma=0;
            else if (op1[0]=='$') memory[k].ma=1;
            else memory[k].ma=2;
            if (op2[0]=='#') memory[k].mb=0;
            else if (op2[0]=='$') memory[k].mb=1;
            else memory[k].mb=2;
            // printf("%d: %d %d %d %d %d\n", k, memory[k].op, memory[k].ma, memory[k].a, memory[k].mb, memory[k].b);
            k++; k%=MOD;
        }
        addrs[0]=addr1;
        addrs[1]=addr2;
        p=0;
        for (i=0; i<32000; i++) {
            addrs[p] %= MOD;
            if (exec(p)==0) break;
            p=(p+1)&1;
        }
        if (i==32000) printf("Programs are tied.\n");
        else printf("Program #%d is the winner.\n", ((p+1)&1)+1);
        //
    }
    return 0;
}


