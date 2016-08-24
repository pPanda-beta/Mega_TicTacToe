#include <GL\glui.h>
 
 
 
 
 
 
typedef struct {
			     int gmid;
				 char name[25];
		    	 char desc[80];
			     int n;
			     int pln;
			     int maxpln;
			     int pst;
			     int cplno;
			     player *pllist;
			   } GAME ;


typedef struct {
				int userid;
				char email[32];
				char pass[16];
			   } USER  ;





extern char serroot[];
extern char *ua;



//extern int sn,spln;
extern int sgflg,cplno,mplno;
extern int IamHost,IamLoggedIn;
extern player me;
extern USER I,admin,guest;
extern GAME *gmlist;
extern GAME cgm;
extern GAME gmlist1[];
extern int totalgms;

extern char msg[80],msg2[80],servmsg[300];

extern GLUI_TextBox *tb;












void nscb(int ,void *c=NULL);

GLUI *serhostwin(GLUI **) ;
GLUI *sergamelist(GLUI **);
GLUI *sergmpllist(GLUI **pui,GAME *gm);
GLUI *serpausewin(GLUI **pui);

int postturn(int,int);
int getstate();
int hostgame();
int joingame(int);
int managegame(int);
int login();
int getinfo();
int kick(int tplno);

int sergetgamelist();
int sergetpllist(GAME *gm);
void sermain(int);
int doturn(int i,int j);
int gameplay();
void fullend(int gtype);

void myturn(int bt, int st,int x, int y);
void norm(int bt, int st,int x, int y);

void sertext(float x, float y, GLfloat scale, char* format, ...);
void sdis();
