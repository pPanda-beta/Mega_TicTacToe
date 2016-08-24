#include <stdio.h>


#include "all.h"

FILE *fetchurl(char *url,char *agent);


char *endcause(int causeno)
{
 switch(causeno)
 {
  case 50211: return "Host stopped the game." ;
  case 50212: return "Host kicked you." ;
  case 50213: return "Host kicked everyone." ;
  case 50214: return "Host disconnected." ;
  case 50215: return "Someone won the game." ;
  case 50217: return "You have won the game." ;
  case 50221: return "Everyone left the game." ;
  default   : return "Game ended due to unknown cause." ;
 }
}






int postturn(int i,int j)
{
 char url[300];
 
 sprintf(url,"%s/gameplay.php?userid=%d&gameid=%d&opid=move&playerno=%d&i=%d&j=%d",serroot,I.userid,cgm.gmid,mplno+1,i,j);
 
 // puts(url);
 
 FILE *ufp;
 int id;
 
 
 //ufp=fetchurl("file:///G:/Server/turn","libcurl-agent/1.0");
 ufp=fetchurl(url,ua);
 
 
 fscanf(ufp,"%d ",&id);
 
 if(id==1024)
  {
   
   printf("Succesful___\n");
  
  }
 else printf("Failed ::__\n");
 
 fclose(ufp);
}



int getstate()
{
 char url[300];
 
 sprintf(url,"%s/gameplay.php?userid=%d&opid=getstate&playerno=%d&gameid=%d&pst=%d",serroot,I.userid,mplno+1,cgm.gmid,cgm.pst-1);
 
 // puts(url); 
 
 
 int i,j,k,op,tpst,tcplno,cause;
 char s[80],ch;
 
 FILE *ufp; //fetchurl("file:///G:/Server/state","libcurl-agent/1.0");
 ufp=fetchurl(url,ua);
// ufp=stdin;


 
 while(ufp && !feof(ufp))
 {
  if(fscanf(ufp,"%d ",&op)<0)break;
//   fscanf(ufp,"%d ",&op);
  //  putchar(fgetc(ufp));
//  if(feof(ufp))break;
  printf("Got op=%d::%d\n",op,feof(ufp));
  
  //getchar();
  
  
  switch(op)
  {
   case 1:
   	      break;
   	      
   	      
   case 5001: 
              if(fscanf(ufp,"%d %d %d ",&tcplno,&i,&j)<0)break;
              
              
			  if(tcplno==cplno)doturn(i,j);
              else break; //fclose(ufp);
              printf("gs__Player %d gave turn at %d,%d.\n",tcplno,i,j);
    	      break;
    	      
   case 5005:
   			  if(fscanf(ufp,"%d ",&tcplno)<0)break;
   			  printf("Waiting for player %d's turn...\n",tcplno);
   			  
    	      break;
   
   
   
   case 5010:
   	 		  if(fscanf(ufp,"%d ",&tpst)<0)break;
   			  printf("Currently pst=%d...\n",tpst);
   			  
    	      break;
   
   
   
   case 5015:
   	 		  
   			  printf("Hurry up others are waiting...\n");
   			  
    	      break;
   
   
   
   case 5017:
   	 		  printf("Something Changed need to be updated...\n");
   			  sergetpllist(&cgm);
    	      break;
   
   
   
   case 5021:
   	 		  if(fscanf(ufp,"%d ",&cause)<0)break;
   			  printf("Game ended due to cause:%d...\n",cause);
   			   sgflg=0;
   			 //  printf("\a\a\a>>>>>%d\n",sgflg);
   			  puts(endcause(cause));
   			  gmain_org(&cgm.pst,cgm.n); 
   			  sprintf(msg,"Sorry, Game ended");
   			  sprintf(msg2,"%s",endcause(cause));
   			 
			  GLUI_Master.set_glutMouseFunc(norm);
			  
    	      break;
   
   
   
   case 5025:
   	 		  if(fscanf(ufp,"%d ",&tcplno)<0)break;
   			  printf("Player %d won th game...\n",tcplno);
   			  
    	      break;
   
   default:
   	      break;
   
  }
  
  

 }
 
 glutPostRedisplay();
}






