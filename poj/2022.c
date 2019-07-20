#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char line[1024];
int readline() {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        line[i++]=c;
    }
    line[i]=0;
    return i;
}
char stack[128][8];
int main() {
    int tc, ti, i, l, j, k, c;
    int stop, valid, header;
    readline(); sscanf(line, "%d", &tc); for (ti=0; ti<tc; ti++) {
        l = readline();
        stop=0; valid=1; header=0;
        i=0; while(1) {
            while(line[i]==' ') i++;
            if (i==l) break;
            // printf("processing %s\n", line+i);
            if (line[i]=='<') {
                if (line[i+1]=='/') {
                    if (stop==0) { valid=0; break;}
                    j=i+1; while(j<l) { if (line[j]=='>') break; j++; }
                    if (j==l) { valid=0; break; }
                    c = strlen(stack[stop-1]);
                    if (strncmp(stack[stop-1], line+i+2, c)!=0) { valid=0; break; }
                    stop--;
                    i=j+1;
                } else {
                    j=i+1; while(j<l) { if (line[j]=='>') break; j++; }
                    if (j==l) { valid=0; break; }
                    if (line[i+1]=='A') {
                        i+=2; if (line[i]!=' ') { valid=0; break; }
                        while(line[i]==' ') i++;
                        if (strncmp(line+i, "HREF=http://", 12)!=0) { valid=0; break;}
                        i+=12;
                        k = j-1; while(line[k]==' ')k--;
                        c=k-i+1; if (c<4) { valid=0; break; }
                        if (strncmp(line+k-3, ".com", 4)!=0) { valid=0; break; }
                        for (;i<k; i++) if (line[i]=='<'||line[i]=='>') { valid=0; break; }
                        if (i<k) break;
                        stack[stop][0]='A'; stack[stop][1]=0; stop++;
                    } else {
                        c = j-i-1;
                        if (c!=1&&c!=4) { valid=0; break; }
                        if (j-i==l) { valid=0; break; }
                        if (stop==0) { if (header||c!=4||strncmp(line+i+1, "HTML", 4)!=0) { valid=0; break;} header=1;}
                        else if (stop==1) { if (header==2||c!=4||strncmp(line+i+1, "BODY", 4)!=0) { valid=0; break;} header=2;}
                        else if (line[i+1]!='B'&&line[i+1]!='I') { valid=0; break; }
                        // push tag
                        strncpy(stack[stop], line+i+1, c);
                        stack[stop][c]=0;
                        stop++;
                    }
                    i = j+1;
                }
            } else if (line[i]=='>') {
                valid = 0; break;
            } else {
                if (stop<2) { valid = 0; break; }
                i++;
            }
            if (valid==0) { 
                break;
            }
        }
        if (valid&&header) printf("Syntax Included\n");
        else printf("No Syntax Included\n");
    }
    return 0;
}


