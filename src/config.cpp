#include "all.h"

//#include <GL\glut.h>


int *ci;
char **si;

//int pln=3;

int plcfg=0;


void setcolori(int id )
{
 printf("setcolor called with id %d, ci[%d]=%d\n",id,id,ci[id]);
 
 memcpy(gmplr[id]->color,stdcolor[ci[id]].v, 3*sizeof(float));
 
 printf("Player %d: %.2f,%.2f,%.2f\n",id,
  gmplr[id]->color[0],gmplr[id]->color[1],gmplr[id]->color[2] );
 
 
  GLUI_Master.sync_live_all();
// display();
 glutPostRedisplay();
// for(i=0;i<pln;i++)
//  memcpy(gmplr[i]->color,stdcolor[ci[i]].v, 3*sizeof(float));
}



void setsymi(int id)
{
 printf("\nsetsym called with id %d, si[%d]=%c\n",id,id,*si[id]);
 
 int i,k=1;
 
 if(*si[id]=='?') k=0;
 
 for(i=0;i<pln &k;i++)
  {
   if(*si[id]==gmplr[i]->sym) k=0;    
  }
 
 if(k)
 {
  for(i=0;i<n*n;i++)
   {
    printf("s[%d]=%c,",i,s[i]);
    if(s[i]==gmplr[id]->sym) s[i]= *si[id];
   }
  gmplr[id]->sym=*si[id];
 }

 else *si[id]=gmplr[id]->sym;

 GLUI_Master.sync_live_all();
// display();
 glutPostRedisplay();
}




void myGlutReshape( int x, int y )
{
  int tx, ty, tw, th;
  GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
  glViewport( tx, ty, tw, th );

  wd=(float)tw ; ht=(float)th;
  asr=wd/ht;
//  initvars();
  initgvars();
  printf("Reshape is called\n");
  glutPostRedisplay();
}








int plrsetwin(GLUI *ui)
{
 int i,j   ;
 
// ui->set_main_gfx_window( main_win );

 GLUI_Listbox *ll[pln];
 free(ci);
 ci=(int *)malloc(pln*sizeof(int));
 free(si);
 si=(char **)malloc(pln*sizeof(char*));
 for(i=0;i<pln;i++)
  {
   si[i]=(char *)malloc(2*sizeof(char));
   
   *si[i]=gmplr[i]->sym ;
   *(si[i]+1)=0;
  }
  
//  for(i=0;i<pln;i++)printf("%s.\n",si[i]);
 char buf[100];

 GLUI_Panel *cfg_panel=ui->add_panel("") ;
 
 ui->add_button_to_panel(cfg_panel,"Back",plcfg?31:11,cb);
 ui->add_column_to_panel(cfg_panel,true);
 if(!plcfg)ui->add_button_to_panel(cfg_panel,"Start Game",22,cb);
 
 

 
 GLUI_Panel *plr_panel=ui->add_panel("") ;
 
 ui->add_statictext_to_panel(plr_panel,"Player No.#  Name");
 for(i=0;i<pln;i++)
 {
  sprintf(buf," %d.",i+1);
  if(plcfg)ui->add_edittext_to_panel( plr_panel,buf, GLUI_EDITTEXT_TEXT, gmplr[i]->name )->disable() ;
  else     ui->add_edittext_to_panel( plr_panel,buf, GLUI_EDITTEXT_TEXT, gmplr[i]->name );
 }
 
 
 
 ui->add_column_to_panel(plr_panel, true);
 ui->add_statictext_to_panel(plr_panel,"Symbol");
 for(i=0;i<pln;i++)
 {
  sprintf(buf,"",i+1);
  ui->add_edittext_to_panel( plr_panel,buf, GLUI_EDITTEXT_TEXT, si[i],i,setsymi ) ;
 }
 
 
 
 
 ui->add_column_to_panel(plr_panel, true);
 ui->add_statictext_to_panel(plr_panel,"Color");
 for(i=0;i<pln;i++)
 { 
  ll[i]=ui->add_listbox_to_panel(plr_panel,"s",&ci[i],i,setcolori );
   for(j=1;j<=totalclr;j++) ll[i]->add_item(j,stdcolor[j].n);
 }



}
 
 
 
 
 


 
 
 
 






void cb(int id)
{
// printf("Called with id=%d\n",id);
 
 switch(id)
 {
  case 1: 
   		  glui[0]->hide();
   		  glui[1]->show();
  		  break;
  case 2:
  		  break;
  		  
  case 3:
  	      serhostwin(&sui);
  	      IamHost=1;
  	      glui[0]->disable();
  		  break;
  case 4:
  	      sergamelist(&sui);
  	      IamHost=0;
  	      glui[0]->disable();
  	      
  		  break;
  		  
  case 5: exit(0);
  		  break;





  case 11: glui[1]->hide();
   		   glui[0]->show();
   		   if(glui[2])glui[2]->close();
   		   gmflag=0;
  		   break;
  		   
  case 12: 
  		  if(pln>n-1)pln=n-1;
  		  break;
  		  // initvars();
  		  // neworder();
		  // break;
  case 13: 
  		   if(pln>n-1)pln=n-1;
  		   
		   //neworder();		   
  		  // break;
  case 14:
  		  plcfg=0;
  		  initvars();
  		  neworder();
  		  prepgame();
  		
  		  if(glui[2])glui[2]->close();
  		  glui[2]=GLUI_Master.create_glui_subwindow( main_win, GLUI_SUBWINDOW_BOTTOM ); 
		  plrsetwin(glui[2]);
  		  
  		  break;
  
  
  
  
  
  case 22: 
         
  	      // GLUI_Master.set_glutMouseFunc(mouse);
  	     //  glutMouseFunc(mouse);
           glui[2]->close();
  	       glui[0]->hide();
  	       glui[1]->hide();
  	       glui[3]->close();
  	       glui[3]=GLUI_Master.create_glui_subwindow( main_win, GLUI_SUBWINDOW_RIGHT ); 
           
  	       pausewin(glui[3]);
  	       glui[3]->hide();
  	       // stgame();
  	       gmflag=1;
  	       plcfg=1;
  	         glutSetWindow(main_win);
          // myGlutReshape(0,00);
           glutSetMenu(gmmenu);
  	       glutAttachMenu(GLUT_RIGHT_BUTTON);
  	       
  	       break;
  
  
  
  
  
  
  
  
  
  case 31:
  		  //glui[3]->hide();
          if(glui[2])glui[2]->close();
          keyboard(27,0,0);
  		  break;
  case 32:
  	      neworder();
  	      if(glui[2])glui[2]->close();
  	      glutPostRedisplay();
          glui[3]->hide();
  		  cb(1);
  		  break;
  		  
  		  
  case 33:
  		  glui[0]->hide();
  		  glui[1]->hide();
  		  if(glui[2])glui[2]->close();
  		  glui[2]=GLUI_Master.create_glui_subwindow( main_win, GLUI_SUBWINDOW_BOTTOM ); 
  		  plrsetwin(glui[2]);
  		  break;
  		  
  case 34:
  		  break;
  case 35:
          if(glui[2])glui[2]->close();
          glui[3]->close();
          
          glutSetWindow(main_win);
          // myGlutReshape(0,00);
          glutSetMenu(mainmenu);
  	      glutAttachMenu(GLUT_RIGHT_BUTTON);
          
           sprintf(ttl,"Mega TicTacToe by PD");
		   glutSetWindowTitle(ttl);
          
  		  glui[0]->show();
  		  glui[0]->enable();
 		  //glui[0]->hide();
 		  glutSetWindow(glui[0]->get_glut_window_id());
 		  glui[0]->show();
 		  
 		  glui[0]->refresh();
  		  
  		  gmflag=0;
  		  plcfg=0;
  		  break;
  		  
  case 36: exit(0);
  		  break;

  
  
  
 }
 
 GLUI_Master.sync_live_all();
 //glutSetWindow(main_win);
// glutPostRedisplay();
// myGlutReshape(0,0);
  display();
 
 
}
 

 
 
 
int pausewin(GLUI *ui)
{

 
 ui->bkgd_color[0]=155;
 ui->bkgd_color[1]=150;
 ui->bkgd_color[2]=250;
 
 //ui->set_main_gfx_window( main_win );
 
 ui->add_button("Resume",31,cb);
 ui->add_button("Restart",32,cb);
 ui->add_button("Change Player Config",33,cb);
 ui->add_button("Save",34,cb);
 ui->add_button("Quit to menu",35,cb);
 ui->add_button("Exit",36,cb);
 
}
 

int gmsetwin(GLUI *ui)
{
 
 ui->bkgd_color[0]=155;
 ui->bkgd_color[1]=150;
 ui->bkgd_color[2]=250;
 
 ui->set_main_gfx_window( main_win );
 
  
 ui->add_button("Back",11,cb);

 ui->add_column();
 GLUI_Spinner *order=ui->add_spinner("Order ",GLUI_SPINNER_INT,&n,12,cb);
 order->set_int_limits(2,100);
 order->set_speed(.009);
 
 ui->add_column();
 GLUI_Spinner *plno=ui->add_spinner("Player No ",GLUI_SPINNER_INT,&pln,13,cb);
 plno->set_int_limits(2,99);
 plno->set_speed(.005);
 
 ui->add_column();
 ui->add_button("Next",14,cb);

}




int startwin(GLUI *ui)
{
 
 ui->bkgd_color[0]=155;
 ui->bkgd_color[1]=150;
 ui->bkgd_color[2]=250;

 ui->set_main_gfx_window( main_win );
 
 
 ui->add_button("New Game",1,cb);
 ui->add_button("Load Game",2,cb);
 ui->add_column();
 ui->add_button("Host on Server",3,cb);
 ui->add_button("Join game on server",4,cb);
 ui->add_column();
 ui->add_button("Exit",5,cb);
 
 
}









 
GLUI_Panel *prep_Panel(GLUI *ui)
{
 GLUI_Panel *p1 = ui->add_panel("" );

 ui->bkgd_color[0]=155;
 ui->bkgd_color[1]=150;
 ui->bkgd_color[2]=250;

 
// p2->deactivate();
 
 // glui->close();
 return p1;
}




