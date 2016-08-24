#include "all.h"

char msg[80]={0},msg2[80]="ggf";




void sertext(float x, float y, GLfloat scale, char* format, ...)
{

    va_list args;
    char buffer[255], *p;
    static GLfloat font_scale = 119.05 + 33.33;

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);



 x*=wd*.5; 
 y=((1-y*.5)*ht) - (scale*.667) ;
 //scale*=( wd<ht? (wd/512) : (ht/512) );



    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    gluOrtho2D(0, wd, 0, ht);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(x, y, 0.0);
    glScalef((scale/font_scale)*(wd/512), (scale/font_scale)*(ht/512), scale/font_scale);
// printf("%f,%f\a\n",x,y);

 glLineWidth(2.5*(scale/35)*( wd<ht? (wd/512) : (ht/512) ));

    for(p = buffer; *p; p++)
     glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);


 //   glPopAttrib();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

}


void sertable(int m,int n,float x,float y,float sc,float sx,float sy)
{
 register float i,j ;
 int k;
 for(i=0;i<n;i++)
  {
   for(j=0;j<m;j++)
   {
 
    if(((char (*)[cgm.n])s)[(int)i][(int)j] == stdsyms[0])
		    glColor3fv(stdcolor[0].v);   
    else
     for(k=0;k<cgm.pln;k++)
	  if(((char (*)[cgm.n])s)[(int)i][(int)j]==cgm.pllist[k].sym)
	   {
		glColor3fv(cgm.pllist[k].color);
		//printf("Got k=%d for sym=%c\n",k,((char (*)[sn])s)[(int)i][(int)j]);
		//printf("Color is = %3f,%3f,%3f\n",cgm.pllist[k].color[0],cgm.pllist[k].color[1],cgm.pllist[k].color[2]);
	    break;
	   }

	sertext(x+j*sx,   y+ i*sy ,sc,"%c",((char (*)[n])s)[(int)i][(int)j]);
//   text(x+(j+.5)*(cw+bd),   y+ i*sy ,sc,"%c",((char (*)[n])s)[(int)i][(int)j]);
   }
  }
}








void det_state(int cpst)
{
 if(cpst>0){ sprintf(msg,"Turn for %s :",cgm.pllist[(pst-1)%pln].name); }
 if(cpst==0){ sprintf(msg,"Its a Draw"); }
 if(cpst<0){ sprintf(msg,"%s won!!!",cgm.pllist[(-pst-1)%pln].name); }
}






void sdis()
{

 printf("serdisplay is Called\n"); 
 initgvars();
  glutSetWindow(main_win);
 glClear( GL_COLOR_BUFFER_BIT);

 glColor3f(0, 0, 1);
 grid(cgm.n,cgm.n,gx,gy, cw, ch,bd);
 
 
 //det_state(pst);
 glColor3f(1, 1, 0);
 sertext(0.01,0.015,35,msg);
 glColor3f(.7, 0, 0);
 sertext(0.01,0.165,25,msg2);
 
 
 glColor3f(0, 1, 1);
 if(pst<0)
        boldline(gx+(vj1)*(cw+bd)+.5*cw,
		    	 gy+(vi1)*(ch+bd)+.5*ch,
				 gx+(vj2)*(cw+bd)+.5*cw,
			 	 gy+(vi2)*(ch+bd)+.5*ch,
				  .05*3/n ); 		
				 
// glColor3f(0, 0, 0);
 sertable(n,n,
  	   gx+.35*cw,
	   gy+.27*ch,
	   59*(5/(float)n)*( wd<ht? (wd/512) : (ht/512) ),
	   (cw+bd),
	   (ch+bd)			);
 
 
 
 if(cgm.pst<0)
 {
  glColor3f(.7, 1, 1);
  boldline(gx+(vj1)*(cw+bd)+.5*cw,
           gy+(vi1)*(ch+bd)+.5*ch,
		   gx+(vj2)*(cw+bd)+.5*cw,
		   gy+(vi2)*(ch+bd)+.5*ch,
				  .05*3/n ); 
 }
 
 
 glFlush();
 glFinish();
 glutSwapBuffers();

}









