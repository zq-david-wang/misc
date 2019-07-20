#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UW (!strcmp(argv[0]+strlen(argv[0])-4,".cmd"))

#define WRONG (UW?1:2)
#define FORMAT (UW?2:1)
#define OK 0

double res[] ={
81252196,
1602756,
89538,
0,
94361,
44782,
49785,
0,
0};

struct ss{
  double abil;
  char name[30];
} s[10000], t[10000], *sp;

int compname(struct ss *a, struct ss *b){
   return strcmp(a->name,b->name);
}

int comp(struct ss *a, struct ss *b){
  if (a->abil < b->abil) return -1;
  if (a->abil > b->abil) return 1;
  return 0;
}

int b,i,j,k,m,n;
double sum;
main(int argc, char **argv){
   FILE *f;
   if (UW) {
      char buf[100];
      strcpy(buf,argv[0]);
      strcpy(buf+strlen(buf)-3,"dat");
      f = fopen(buf,"r");
   } else f = fopen(argv[1],"r");
   while (fscanf(f,"%d",&k) && k) {
      for (i=0;i<k;i++) fscanf(f,"%s%lf",&s[i].name,&s[i].abil);
      qsort(s,k,sizeof(struct ss),compname);
      for (j=1;j<k;j+=j);
      b = j-k;
      //printf("k %d j %d bye %d\n",k,j,b);
      for (i=0;i<b;i++) {
         scanf("%s",&t[i].name);
         sp = bsearch(&t[i],s,k,sizeof(struct ss),compname);
         if (!sp) {printf("bad knight %s\n",t[i].name); exit(WRONG);}
         if (sp->abil == -1) {printf("dupe knight %s\n",t[i].name); exit(WRONG);}
         sp->abil = -1;
      }
      qsort(s,k,sizeof(struct ss),comp);
      for (i=0;s[i].abil == -1;i++);
      for (sum=0;i<k;i+=2) {
         sum += (s[i].abil-s[i+1].abil)*(s[i].abil-s[i+1].abil);
      }
      printf("%0.10lg\n",sum);
      if (sum != res[m]) {
         printf("wrong! should be %0.10lg\n",res[m]); exit(WRONG);
      }
      m++;
   }
   printf("judge says OK\n"); exit(OK);
}
