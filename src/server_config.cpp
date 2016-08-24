#include "all.h"


int sci=3;
char ssi[2]={0};
GLUI_List *glist,*plist;
GLUI_TextBox *tb;


void prep_glist()
{
 int i;
 char buf[1800];
 
 sergetgamelist();
 glist->delete_all();
 
// glist->glui->add_statictext("dfs");
 for(i=0;i<totalgms;i++)
  {
   sprintf(buf,"%-25s %2d %3d/%-3d     %-250s\n",gmlist[i].name,gmlist[i].n,gmlist[i].pln,gmlist[i].maxpln,gmlist[i].desc);
   while(strchr(buf,' '))*strchr(buf,' ')='_';
   glist->add_item(i,buf);
  }
}



void prep_plist(GAME *gm)
{
 int i;
 char buf[50];
 
 plist->delete_all();
 //printf("gm->pln : %d ",gm->pln);
 //gm->pln=2+rand()%(gm->maxpln - 1);
 sergetpllist(gm);
 //printf("---> %d\n",gm->pln);
 for(i=0;i< gm->pln ;i++)
  {
   sprintf(buf,"%3d  %-25s %c",i+1,gm->pllist[i].name,gm->pllist[i].sym);
   while(strchr(buf,' '))*strchr(buf,' ')='_';
   puts(buf);
   plist->add_item(i,buf);
//   new GLUI_StaticText(plist,"");
  }
}



void wtost(int flg)
{
 if(gmflag==3){sui->close(); return;}
 switch(getinfo())
 {
  case  5: 
  		   prep_plist(&cgm);
  		   
  		  // break;
  case  1: 
  		   GLUI_Master.set_glutTimerFunc(2500,wtost,0);
  		   break;
  case  7: 
  		   /*
  		   glui[0]->enable();
  		   sui->close();
  		   */
  		   
  		   fullend(5);
  		   break;
  case -5: 
  		   //glui[0]->enable();
  		   printf("Game Started:::\a\a\a\a\a");
  		   
		   sui->close();
  		   
  		   break;
  default: 
   		   GLUI_Master.set_glutTimerFunc(2000,wtost,0);
  		   break;
  
 }
}








void scb(GLUI_Control* control)
{
 int id=control->get_id();

 printf("scb called with %d\n",id);
 
 nscb(id,control);
}


void nscb(int id,void *c)
{
 GLUI_Control* control=(GLUI_Control *)c;
 switch(id)
 {
  case 712:
  	
  	if(cgm.maxpln>=cgm.n) cgm.maxpln=cgm.n-1;
  	break;
  	
  case 713:
  	
  	if(cgm.maxpln>=cgm.n) cgm.maxpln=cgm.n-1;
  	break;
  
  case 711:
  	glui[0]->enable();
  	control->glui->close();
  	sui->close();
   break;
  
  case 714:
  	
  //	cgm.n=sn;
  //cgm.maxpln=spln;
   if(hostgame()<=0)break;
   sergetpllist(&cgm);	
   sergmpllist(&sui,&cgm);
   music(4);
  // sergetgamelist();
 //  sergamelist(&sui);
   break;
   
   
   
  
  case 611:
   I=guest;
   login();
   control->disable();
   
   break;
  
  case 614:
   login();
   break;
  
  
  
  
  
  
  
  case 631:
   printf("Color set at %d\n",sci);
   memcpy(me.color,stdcolor[sci].v, 3*sizeof(float));
   printf("%.3f_%.3f_%.3f\n",me.color[0],me.color[1],me.color[2]);
   break;
   
   
  case 632:
   printf("Symbol set to %s\n",ssi);
   me.sym=*ssi;
   break;
  
  
  
  
  
  
  
  case 811:
  	glui[0]->enable();
   control->glui->close();
   //serhostwin(&sui);
   break;
   
  case 812:

   prep_glist();
   //sergamelist(&sui);
   break;
   
  case 813:
   //control->glui->close();
  // sergetpllist(&gmlist[glist->get_current_item()]);
  // if(glist->g)
   printf("Joined %dth Game.\n",glist->get_current_item());
   
   
   cgm=gmlist[glist->get_current_item()];
   if(joingame(cgm.gmid)<=0) break;
   
   sergmpllist(&sui,&cgm);
   IamHost=0;
   music(4);
   GLUI_Master.set_glutTimerFunc(1000,wtost,0);
   break;
  
  
  
  case 822:
   printf("%dth Game selected.\n",glist->get_current_item());
   
   break;
  
  
  
  
  
  case 921:
   glui[0]->enable();
   control->glui->close();
   fullend(-3);
  // serhostwin(&sui);
   break;
  
  case 922:
  // sergetpllist(&gmlist[glist->get_current_item()]);
   prep_plist(&cgm);
   
   break;
   
  case 923:
   kick(plist->get_current_item());
   prep_plist(&cgm);
   
   
   break;
  
  case 924:
   if(managegame(101)<=0)break;
   control->glui->close();

   gmflag=1;
   //serpausewin(&glui[3]);
   IamHost=1;
   glui[0]->enable();
   glui[0]->hide();
   glui[1]->hide();
  // serpausewin(&glui[3]);
   sermain(1);
   break;
  
  
  
  
  
  case 1011:
   //control->glui->hide();
  // pause=!pause;
   keyboard(27,0,0);
   
   break;

  case 1012:
   
   //managegame(110);
   fullend(3);
   break;

  case 1013:
   
   sergmpllist(&sui,&cgm);
   break;

  case 1014:
   
   //managegame(110);
   fullend(3);
   exit(0);
   break;
  
  
  default:
   
   break;
 }
 
  GLUI_Master.sync_live_all();




}








GLUI_Panel *myset(GLUI *ui)
{
 int j;
 
 if(!IamLoggedIn)
 {
  GLUI_Panel *p1 = new GLUI_Panel(ui,"Sign In ",true);
  new GLUI_Button(p1,"Log in as Guest",611,scb);   new GLUI_Column(p1,false);
  (new GLUI_EditText(p1,"E-mail",I.email))->set_w(205);    new GLUI_Column(p1,false);
  new GLUI_EditText(p1,"Password",I.pass);   new GLUI_Column(p1,false);
  new GLUI_Button(p1,"Log in",614,scb);
  
  
  
  tb=new GLUI_TextBox(ui,true);
  //tb->disable();
  tb->set_h(70);
  tb->set_w(500);
  tb->set_text(servmsg);
 }
 
 
  GLUI_Panel *p3 = new GLUI_Panel(ui,"Your Informations",true);
  new GLUI_EditText(p3,"Your Name",me.name,630,scb);   new GLUI_Column(p3,false); 
  
  *ssi=me.sym;
  new GLUI_EditText(p3,"Your Symbol",ssi,632,scb); new GLUI_Column(p3,false); 
 // new GLUI_EditText(p3,"Your Symbol",&me.sym,632); new GLUI_Column(p3,false); 
 
  GLUI_Listbox *ll= new GLUI_Listbox(p3,"Your color ",&sci,631,scb);
   for(j=1;j<=totalclr;j++) ll->add_item(j,stdcolor[j].n);
 

}











GLUI *serhostwin(GLUI **pui)
{
 int i,j;
 
 GLUI *ui;
 
 ui=*pui;
 ui->close();
// printf("%u,%d+++\n",ui,ui->get_glut_window_id());
 
// ui=GLUI_Master.create_glui_subwindow( main_win, GLUI_SUBWINDOW_BOTTOM ); 
 

 ui=GLUI_Master.create_glui("Server Host",0,350,200);
 ui->set_main_gfx_window( main_win );
 
 ui->bkgd_color[0]=100;
 ui->bkgd_color[1]=200;
 ui->bkgd_color[2]=100;
 
// ui->set_main_gfx_window( main_win );
 
 
// GLUI_Panel *p2 = new GLUI_Panel(ui,"DEF",true);
 
 myset(ui);
 
 GLUI_Panel *p1 = new GLUI_Panel(ui,"Configure your game",true);
 
 
 new GLUI_Button(p1,"Back",711,scb);
 new GLUI_Column(p1,false); 
 
 
 GLUI_Spinner *sorder= new GLUI_Spinner(p1,"Order",&cgm.n,712,scb);
 sorder->set_int_limits(2,100);
 sorder->set_speed(.005);
 
 GLUI_EditText *gn=new GLUI_EditText(p1,"Game Name",cgm.name,715,scb);
 gn->set_w(200);
 new GLUI_Column(p1,false); 
 
 
 
 GLUI_Spinner *splno= new GLUI_Spinner(p1,"Player No.",&cgm.maxpln,713,scb);
 splno->set_int_limits(2,99);
 splno->set_speed(.005);
 GLUI_EditText *gd=new GLUI_EditText(p1,"Description",cgm.desc,716,scb);
 gd->set_w(200);
 new GLUI_Column(p1,false); 
 
 new GLUI_Button(p1,"Host",714,scb);
 
 
 
 
 
 
  GLUI_Master.sync_live_all();
  
  *pui=ui;
  
 return ui;
}





GLUI *sergamelist(GLUI **pui)
{
 int i,j;
// char buf[1800];
 GLUI *ui;
 ui=*pui;
 
 ui->close();
 
 
 
 
   
 ui=GLUI_Master.create_glui("Game List",0,350,200);
 ui->set_main_gfx_window( main_win );
 
 ui->bkgd_color[0]=100;
 ui->bkgd_color[1]=200;
 ui->bkgd_color[2]=100;
 
 
 
 
 GLUI_Panel *p1 = new GLUI_Panel(ui,"Always refresh before joining",true);
 
 
 new GLUI_Button(p1,"Back",811,scb);
 new GLUI_Column(p1,false); 
 new GLUI_Button(p1,"Refresh",812,scb);
 new GLUI_Column(p1,false); 
 new GLUI_Button(p1,"Join Game",813,scb);
 new GLUI_Column(p1,false); 
 
 
 GLUI_Panel *p2 = new GLUI_Panel(ui,"Game List",true);
 
 new GLUI_StaticText(p2,"                  Name                 Order Players Description");
 glist = new GLUI_List(p2,true,822,scb);
 glist->set_w(500);
 prep_glist();


 myset(ui);
 
 *pui=ui;
 
 return ui;
}









GLUI *sergmpllist(GLUI **pui,GAME *gm)
{
 int i,j;
// char buf[180];
 GLUI *ui;
 ui=*pui;
 
 ui->close();
 
 
 
 
 
 ui=GLUI_Master.create_glui("Player List",0);
  ui->set_main_gfx_window( main_win );

 ui->bkgd_color[0]=100;
 ui->bkgd_color[1]=200;
 ui->bkgd_color[2]=100;

 
 
 GLUI_Panel *p0 = new GLUI_Panel(ui,"Player List",true);

 new GLUI_StaticText(p0,"  Pl.NO    Name                           Symbol");
 plist = new GLUI_List(p0,true,912,scb);
 plist->set_w(410);
 
 prep_plist(gm);
 
 
 
 

 
 
 
 
 
 
 
 
  GLUI_Panel *p1 = new GLUI_Panel(ui,IamHost?"Please refresh before start":"Please be patient",true);
  new GLUI_Button(p1,"Back",921,scb); 
  new GLUI_Column(p1,false);
  new GLUI_Button(p1,"Refresh",922,scb);
   
 if(IamHost)
 {
  new GLUI_Column(p1,false);
  new GLUI_Button(p1,"Kick",923,scb);
  new GLUI_Column(p1,false);
  new GLUI_Button(p1,"Start",924,scb);
 }
 
 
 *pui=ui;
 
 return ui;
}










GLUI *serpausewin(GLUI **pui)
{
 int i,j;
 char buf[180];
 GLUI *ui;
 ui=*pui;
 
 ui->close();
 
 
 
 
  
// ui=GLUI_Master.create_glui("Pause Menu",0);
 
  ui=GLUI_Master.create_glui_subwindow( main_win, GLUI_SUBWINDOW_RIGHT ); 
  
// ui->set_main_gfx_window( main_win );
 ui->bkgd_color[0]=100;
 ui->bkgd_color[1]=200;
 ui->bkgd_color[2]=100;

 
 
 new GLUI_Button(ui,"Resume",1011,scb);
 new GLUI_Button(ui,"Leave Game",1012,scb);
 new GLUI_Button(ui,"View Player List",1013,scb);
 new GLUI_Button(ui,"Exit",1014,scb);
 
 
 
 
 
 *pui=ui;
 
 return ui;
}

