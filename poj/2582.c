#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char line[1024];
int readline() {
    int i=0; char c;
    while(1) {
        c = getchar();
        if (c==EOF||c=='\n') break;
        line[i++] = c;
    }
    if (i&&line[i-1]=='\r') i--;
    line[i]=0;
    return i;
}
char map[24][24][24];
char steps[6][3] = {
    {0, 0, 1},
    {0, 0, -1},
    {0, 1, 0},
    {0, -1, 0},
    {1, 0, 0},
    {-1, 0, 0},
};
int main() {
    int l, w, d, i, j;
    char b[8];
    int x, y, z, nx, ny, nz;
    while(1) {
        readline();
        if (line[0]=='E') break;
        sscanf(line, "%s %d %d %d", b, &l, &w, &d);
        memset(map, 0, sizeof(map));
        readline();
        i=0; while(1) {
            while(line[i]==' ') i++; if (line[i]==0) break;
            x=0; while(line[i]>='0'&&line[i]<='9') { x=x*10+line[i]-'0'; i++; } i++;
            y=0; while(line[i]>='0'&&line[i]<='9') { y=y*10+line[i]-'0'; i++; } i++;
            z=0; while(line[i]>='0'&&line[i]<='9') { z=z*10+line[i]-'0'; i++; }
            if (z>d) z=d;
            map[x][y][z]=1;
            for (j=0; j<6; j++) {
                nx = x+steps[j][0];
                ny = y+steps[j][1];
                nz = z+steps[j][2];
                if (nx<0||ny<0||nz<0) continue;
                map[nx][ny][nz]=1;
            }
        }
        readline();
        j=0;i=0; while(1) {
            while(line[i]==' ') i++; if (line[i]==0) break;
            x=0; while(line[i]>='0'&&line[i]<='9') { x=x*10+line[i]-'0'; i++; } i++;
            y=0; while(line[i]>='0'&&line[i]<='9') { y=y*10+line[i]-'0'; i++; } i++;
            z=0; while(line[i]>='0'&&line[i]<='9') { z=z*10+line[i]-'0'; i++; }
            if (map[x][y][z]) j++;
        }
        readline();
        if (j==0) printf("None of dem fish blowed up!\n");
        else printf("AIEE, I got %d fish, me!\n", j);
    } 
    return 0;
}


