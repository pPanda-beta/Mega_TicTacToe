#include "all.h"








void myturn(int bt, int st,int x, int y)
{
 register int i,j;
 if(st==GLUT_DOWN && bt==GLUT_LEFT_BUTTON)
 {
  
  px=((float)x/wd)*2 ;
  py=((float)y/ht)*2 ;
 
  for(j=0;j<cgm.n;j++)
   if(gx+j*(cw+bd) < px && px < gx+j*(cw+bd) +cw) break;
  
  for(i=0;i<cgm.n;i++)
   if(gy+i*(ch+bd) < py && py < gy+i*(ch+bd) +ch) break;

  printf("ser_Clicked on cell : %d,%d.\n",i,j);

  if(sgflg){ if(doturn(i,j)==2){  postturn(i,j);  gameplay();} }
 // else sermain(1);
 }
// else if(pst<=0){ reset();  glutPostRedisplay(); printf("Clicked after game end\n");  return ;}
 
}




void norm(int bt, int st,int x, int y)
{
 if(st==GLUT_DOWN && bt==GLUT_LEFT_BUTTON) 
  {
   Beep(500,300);
   display();
  }
 if(st==GLUT_DOWN && !sgflg)
  fullend(1);
 
}

