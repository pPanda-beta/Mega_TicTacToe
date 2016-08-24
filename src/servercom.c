#include "all.h"



//int sn=3,spln=2;
int cplno,mplno,sgflg;
int IamHost=0,IamLoggedIn=0;

player me={"Palash",'@',{1,1,1}};

USER I={ 100001,"palashkok3@gmail.com","panda1995" };
USER admin;
USER guest={ 0,"guest@ppanda.com","qwerty" };

char serroot[]="http://programmerpanda.byethost22.com/mt3v1";
//char *serroot="file:///G:/Server";
char *ua="Mega Tic Tac Toe/v1Beta311_libcurl:win32";

char servmsg[300]="You are not logged in.\n\
If you don't have any account contact us at http://programmerpanda.byethost22.com";



void pr(char *);


GAME *gmlist;


 
 
GAME cgm={ 007,"Current Game","TestOverall",3,2,1,1,0,NULL } ;
 
 
 

int totalgms=sizeof(gmlist)/sizeof(*gmlist);









void sermain(int gtype)
{
 music(5);
 glutSetWindow(main_win);
// glui[3]->set_main_gfx_window(main_win);
 glutSetMenu(sermenu);
 glutAttachMenu(GLUT_RIGHT_BUTTON);
 
// n=sn=cgm.n;
 n=cgm.n;
 initvars();
 
// pln=spln=cgm.pln;
 pln=cgm.pln;
 sgflg=1; 
 neworder();

 cgm.pst=pst=1;

 if(gtype==1)mplno=0;
 
 sergetpllist(&cgm);

// GLUI_Master.set_glutDisplayFunc(sdis);
 GLUI_Master.set_glutReshapeFunc(myGlutReshape);
 gmflag=3;
 GLUI_Master.set_glutIdleFunc(NULL);
 GLUI_Master.set_glutMouseFunc(norm);
 
// printf("%d,%d,%d\n",sn,spln,pst);
 pr(s);
 myGlutReshape(0,0);
 glutPostRedisplay();

 gameplay();
}





void rnd(int oldpst)
{
 int i,j;
 if(!sgflg) return ;
 if(oldpst==cgm.pst)
 {
   while(doturn(i=rand()%cgm.n,j=rand()%cgm.n)<0 && cgm.pst>0);
   postturn(i,j);
   gameplay();
 }
 
 
 
}


void serverturn(int oldpst)
{
// printf("Server turn is requested with sgflg=%d>>>>>>>>>>\n",sgflg);
//  if(!sgflg)fullend(5);
 if(oldpst==cgm.pst)
 {
  //doturn(rand()%sn,rand()%sn);
  getstate();
  gameplay();
 }
// else GLUI_Master.set_glutTimerFunc(5000,rnd,cgm.pst);
 
 
}



void gameend()
{
 
 sgflg=0;
 sprintf(msg2,"Click to start a new round...");
 GLUI_Master.set_glutMouseFunc(norm);
 
}


void fullend(int gtype)
{
 if(IamHost) managegame(105);
 managegame(110);
 gmflag=0;

 GLUI_Master.set_glutMouseFunc(NULL);
 
 sui->close();
 if(glui[3])glui[3]->close();
 
 glui[0]->enable();
 glui[0]->show();
 glui[0]->refresh();
 
 
 
 glutSetWindow(main_win);
 glutSetMenu(mainmenu);
 glutAttachMenu(GLUT_RIGHT_BUTTON);
        
 sprintf(ttl,"Mega TicTacToe by PD");
 glutSetWindowTitle(ttl);
          
 
 printf("fullend completed\n");
 
}



int gameplay()
{
 if(!sgflg){  /*fullend(5);*/ return -1; };
 
  static int oldpst=0;
  
  cplno=(cgm.pst-1)%pln ;
  printf("\n\n\nIts player %d s turn,%d\n",cplno,(cgm.pst-1)%pln);
  if(cplno==mplno)
  {
   if(oldpst!=cgm.pst)
   {
  	printf("Human's turn\n\a");
  	 glutSetWindow(main_win);
    GLUI_Master.set_glutMouseFunc(myturn);
    GLUI_Master.set_glutTimerFunc(30000,rnd,cgm.pst);
    sprintf(msg2,"Its your turn n u have 30 sec left...");
    oldpst=cgm.pst;
   }
  }
  else 
  {
   printf("server's turn\n");
    glutSetWindow(main_win);
   GLUI_Master.set_glutMouseFunc(norm);
   GLUI_Master.set_glutTimerFunc(2500,serverturn,cgm.pst);
   sprintf(msg2,"Server will be refreshed within 5 sec..");   
  }
  
 //gmain();
 gmain_org(&cgm.pst,cgm.n);
 
 if(cgm.pst>0){ sprintf(msg,"Turn for %s :",cgm.pllist[cplno].name); }
 if(cgm.pst==0){ sprintf(msg,"Its a Draw");  oldpst=0; gameend(); }
 if(cgm.pst<0)
  { 
    sprintf(msg,"%s won!!!",cgm.pllist[(-cgm.pst-1)%pln].name);
    oldpst=0;
    gameend();
   }
 
 glutPostRedisplay();
// sdis();
 printf("Gameplay loop ends\n\n\n");
}










int doturn(int i,int j)
{
 //printf("\t\t\t doturn is called\n\n");

 if(i<cgm.n && j<cgm.n && ((char (*)[cgm.n])s)[i][j]=='?')
 {
  
  
  ((char (*)[cgm.n])s)[i][j]=cgm.pllist[cplno].sym ; 
  
  //if(cplno==mplno)postturn(i,j);
  
  //printf("\t\t\t###########%d,%d\n",cplno,(cgm.pst-1)%cgm.pln);
  
   cgm.pst++;
   
  cplno=(cgm.pst-1)%cgm.pln ;
//  printf("%d,%d,\n",pst,pst%pln);
//  printf("Currently  cgm.pst=%d\n",cgm.pst);
  glutPostRedisplay();
 // printf(".................\n");
  /*gameplay();*/
 // gmain_org(&cgm.pst,cgm.n);
  return 2;
 } 
 
 else { /*printf("\a"); */ Beep(3000,100); printf("Wrong turn\n\n"); /*gameplay(); */return -1; }
 
}






