
#include "all.h"
FILE *fetchurl(char *url,char *agent);
char *geturl(char *url,char *agent);


#define FAILCODE 420




char *failcause(int causeno)
{
 switch(causeno)
 {
  case 451: return "players are joining" ;
  case 452: return "very few players" ;
  case 453: return "only host is in the game" ;
  case 454: return "too much players" ;
  case 471: return "you are banned" ;
  case 475: return "you are already playing" ;
  case 477: return "you have already joined" ;
  case 4201:return "you are not a player of this game";
  case 4202:return "Game is stopped";
  default : return "Unknown" ;
 }
 
}







char *filter(char *x)
{
 char *out=(char *)calloc(300,sizeof(char));
// memset(out,0,300*sizeof(char));
 char *y=out;
 
 while(*x)
 {
  if(!isalnum(*x)) {  y+=sprintf(y,"%%%x",*x);   }
  else 			   { *y=*x; y++;  }
  x++;
 }
 
 *y=0;
 return out;
}




int login()
{
 char url[300];
 
 sprintf(url,"%s/login.php?email=%s&pass=%s",serroot,filter(I.email),filter(I.pass));
 
 // puts(url);
 
 FILE *ufp;
 int id;

 
 //ufp=fetchurl("file:///G:/Server/login","libcurl-agent/1.0");
 ufp=fetchurl(url,ua);
 fscanf(ufp,"%d ",&id);
 
 if(id==1024)
  {
   fscanf(ufp,"%d ",&I.userid);
   printf("Logged in with %d\n",I.userid);
   //fscanf(ufp," %[^\n]\n ",ttl);
  // sprintf(ttl,"Mega TicTacToe by PD");
   //glutSetWindowTitle(ttl);
   
   servmsg[fread(servmsg,300,1,ufp)];
   fwrite(servmsg,300,1,stdout);
   puts(servmsg);
   tb->set_text(servmsg);
   
   IamLoggedIn=1;
  }
 else printf("Failed login::username or password is incorrect.\n");
 
 fclose(ufp);
 
}




int getinfo()
{
	if(cgm.pst>1)return -5;
 static int oldst;
 char url[300];
 
 sprintf(url,"%s/gamehost.php?userid=%d&opid=getinfo&gameid=%d",serroot,I.userid,cgm.gmid);
 
 // puts(url); 
 
 
 int op,tmplno,cause,id,state;
 
 
 FILE *ufp; //fetchurl("file:///G:/Server/info","libcurl-agent/1.0");
 ufp=fetchurl(url,ua);
 
 if(fscanf(ufp," %d ",&id)<0 ) return -1;
 if(id==1024)
  {
   if(fscanf(ufp," %d ",&tmplno)<0 ) return -1;
   if(fscanf(ufp," %d ",&op)<0 ) return -1;
   if(fscanf(ufp," %d ",&state)<0 ) return -1;
   printf("Your curr plno=%d,op=%d,state=%d\n",tmplno,op,state);
   
   mplno=tmplno;
   if(op)
   {
    //glutSetWindow(main_win);
	//serpausewin(&glui[3]);
    glui[0]->enable();
    glui[0]->hide();
    glui[1]->hide();
    sui->close();
	sermain(3);
   }
   if(state!=oldst) { oldst=state;  return 5; }
   
   return 1;
  }
 if(id==420)
  { 
   if(fscanf(ufp," %d ",&cause)<0 ) return -1;
   printf("Error occured: %s\n.",failcause(cause));
   return 7;
  }
 
 return -5;
}








int managegame(int opid)
{
 char url[300];
 
 sprintf(url,"%s/gamehost.php?userid=%d&opid=",serroot,I.userid);
 

 
 switch(opid)
 {
  case 101:
            sprintf(url,"%sstart&gameid=%d",url,cgm.gmid);
            break;
  
  
  case 105:
            sprintf(url,"%sstop&gameid=%d",url,cgm.gmid);
            break;
  
  
  case 110:
            sprintf(url,"%sleave&gameid=%d",url,cgm.gmid);
            break;

 }
 
 // puts(url); 
 
 
 FILE *ufp;
 int id;
 
 //ufp=fetchurl("file:///G:/Server/manage","libcurl-agent/1.0");
 ufp=fetchurl(url,ua);
 
 if(id!=FAILCODE)
  {
   printf("%d\n",id);
  }
 else printf("Failed ::\n");
 
 fclose(ufp);
 if(id == 420) return -1;
 else return 5;
}



int hostgame()
{
 char url[300];
 
 sprintf(url,"%s/gamehost.php?userid=%d\
&opid=host\
&n=%d&pln=%d\
&gamename=%s\
&gamedesc=%s\
&nick=%s\
&symbol=%s\
&rgb=%.3f_%.3f_%.3f",
			         serroot,
					 I.userid,
					 cgm.n,
					 cgm.maxpln,
					 filter(cgm.name),
					 filter(cgm.desc),
					 filter(me.name),
					 filter(&me.sym),
					 me.color[0],me.color[1],me.color[2]);
 
 // puts(url); 
 
 
 FILE *ufp;
 int id;


 
 //ufp=fetchurl("file:///G:/Server/host","libcurl-agent/1.0");
 ufp=fetchurl(url,ua);
 
 fscanf(ufp,"%d ",&id);
 
 if(id!=FAILCODE)
  {
   printf("%d\n",id);
   fscanf(ufp,"%d ",&cgm.gmid);
   
  }
 else { printf("Failed hosting game::\n"); fclose(ufp); return -1; }
 
 fclose(ufp);
 
 return 1;
}




int joingame(int gmid)
{
 
 char url[300];
 
 sprintf(url,"%s/gamehost.php?userid=%d\
&opid=join\
&gameid=%d\
&nick=%s\
&symbol=%s\
&rgb=%.3f_%.3f_%.3f",
					serroot,
					I.userid,
					cgm.gmid,
					filter(me.name),
					filter(&me.sym),
					me.color[0],me.color[1],me.color[2]);
 
 // puts(url); 
 
 
 
 
 FILE *ufp;
 int opid,tmplno,cause;
 I.userid;
 
 
 //ufp=fetchurl("file:///G:/Server/join","libcurl-agent/1.0");
 ufp=fetchurl(url,ua);
 
 fscanf(ufp,"%d ",&opid);
 
 switch(opid)
 {
  case 1024:
  			fscanf(ufp,"%d ",&tmplno);
  			printf("Your Player no is : %d .\n",tmplno);
  			mplno=tmplno;
  			fclose(ufp);
  			return 1;
  			break;
  case 420:
  			fscanf(ufp,"%d ",&cause);
  			printf("Failed as : %s.\n",failcause(cause));
  			break;
 
  default : 
           printf("connection problem");
          
           break;
  
  
 }
 
 
 fclose(ufp);
 return -1;
}


int kick(int tplno)
{
 if(!tplno) return 0;
 char url[300];
 
 sprintf(url,"%s/gamehost.php?userid=%d&opid=kick&gameid=%d&playerno=%d",serroot,I.userid,cgm.gmid,tplno+1);
 // puts(url); 
 
 
 FILE *ufp;
 int id;
 
 //ufp=fetchurl("file:///G:/Server/kick","libcurl-agent/1.0");
 ufp=fetchurl(url,ua);
 
 if(id!=FAILCODE)
  {
   printf("%d\n",id);
  }
 else printf("Failed ::\n");
 
 fclose(ufp);
 
 
}








int sergetgamelist()
{
 char url[300];
 
 sprintf(url,"%s/gamehost.php?userid=%d&opid=getgamelist",serroot,I.userid);
 
 // puts(url); 
 
 
 FILE *ufp;
 int opid,tmplno,cause,i,M,gmid;
 I.userid;
 
 
 //ufp=fetchurl("file:///G:/Server/gmlist","libcurl-agent/1.0");
 ufp=fetchurl(url,ua);
 
 
 fscanf(ufp,"%d ",&opid);
 
 if(opid==771)
 {
  fscanf(ufp,"%d ",&M);
  totalgms=M;
  free(gmlist);
  gmlist=(GAME *)calloc(M,sizeof(GAME));
  

  
  for(i=0;i<M && !feof(ufp);i++)
  {
   fscanf(ufp," %d ",&gmlist[i].gmid);
  // fread(gmlist[i].name,1,25,ufp);
   fscanf(ufp," %[^\n]\n",gmlist[i].name);
   gmlist[i].name[24]=0;
  
   if(fscanf(ufp,"%d %d %d ",&gmlist[i].n,&gmlist[i].maxpln,&gmlist[i].pln)<0 || feof(ufp));
   
  // puts(ufp->_ptr);
   fscanf(ufp," %[^\n]s ",gmlist[i].desc);
   
   printf("%d %s %d %d %d %s\n",gmlist[i].gmid,gmlist[i].name,gmlist[i].n,gmlist[i].maxpln,gmlist[i].pln,gmlist[i].desc);
   
   
  }
  
  printf("\ti=%d,M=%d\n",i,M);
  if(i!=M)
  { totalgms=i; memset(&gmlist[i],0,sizeof(GAME)); }
 }
 
 
 fclose(ufp);
}








int sergetpllist(GAME *gm)
{
 char url[300];
 
 sprintf(url,"%s/gamehost.php?userid=%d&opid=getplayerlist&gameid=%d",serroot,I.userid,gm->gmid);
 
 // puts(url); 
 
 FILE *ufp;
 int opid,tmplno,cause,i,M,plno;
 I.userid;
 
 
 //ufp=fetchurl("file:///G:/Server/pllist","libcurl-agent/1.0");
 ufp=fetchurl(url,ua);
 
 
 fscanf(ufp,"%d ",&opid);
 
 if(opid==771)
 {
  fscanf(ufp,"%d ",&M);
  
  free(gm->pllist);
  gm->pln=M;
  gm->pllist=(player *)calloc(M,sizeof(player));
  
  
  
  while(M && !feof(ufp))
  {
   fscanf(ufp," %d ",&plno);
   //cgm.pllist[plno].name[fread(cgm.pllist[plno].name,1,25,ufp)]=0;
   fscanf(ufp," %[^\n]\n ",gm->pllist[plno].name);
   //gm->pllist[plno].name[strlen(gm->pllist[plno].name)-1]=0;
   gm->pllist[plno].name[24]=0;
   
   if(fscanf(ufp," %c %f %f %f ",&gm->pllist[plno].sym,&gm->pllist[plno].color[0],&gm->pllist[plno].color[1],&gm->pllist[plno].color[2])<0)break;
   printf("%d %25s %c %.3f %.3f %.3f\n",plno,gm->pllist[plno].name,gm->pllist[plno].sym,gm->pllist[plno].color[0],gm->pllist[plno].color[1],gm->pllist[plno].color[2]);
 //  puts(ufp->_ptr);
   M--;
  }
  
  printf("\tM=%d\n",M);
  if(M)
  {  gm->pln-=M;/* memset(&gm->pllist[plno],0,sizeof(player));*/ }
 }
 
 
 fclose(ufp);
}




