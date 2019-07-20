#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define UW (!strcmp(argv[0]+strlen(argv[0])-4,".cmd"))

#define WRONG (UW?1:2)
#define FORMAT (UW?2:1)
#define OK 0


int r,e,i,k,j,n,dun;
int x[300], y[300], z[300];
double a,b,c,d,w;
int ret = OK;

main(int argc, char **argv){
   FILE *f;
   if (UW) {
      char buf[100];
      strcpy(buf,argv[0]);
      strcpy(buf+strlen(buf)-3,"dat");
      f = fopen(buf,"r");
   } else f = fopen(argv[1],"r");

   while (1 == fscanf(f,"%d",&r) && r >= 0) {
      printf("===%d\n",++k);
      scanf("%lg%lg%lg%lg",&a,&b,&c,&d);
      for (i=0;i<r;i++) {
         fscanf(f,"%d%d%d",&x[i],&y[i],&z[i]);
         if (a*x[i]+b*y[i]+c*z[i]+d > 0) {
            printf("Wrong classifier\n"); ret = WRONG; exit(WRONG);
         }
      }
      fscanf(f,"%d",&e);
      n = r + e;
      for (i=r;i<n;i++) {
         fscanf(f,"%d%d%d",&x[i],&y[i],&z[i]);
         if (a*x[i]+b*y[i]+c*z[i]+d <= 0) {
            printf("Wrong classifier\n"); ret = WRONG; exit(WRONG);
         }
      }
   again:;}
   printf("Judge says OK\n");
   return ret;
}
