#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

//#include <GL\gl.h>
//#include <GL\glut.h>

#include "GL\glut.h"
#include <GL\glui.h>



int umain(void);
void logodis(void);
void stidle(void);
void stgame(void);

void ginit(void);
void initmenu();

void text(float x, float y, GLfloat scale, char* format, ...);
void boldline(float x1, float y1,float x2, float y2,float pt);
void rect(float x,float y,float w,float h);
void grid(int m,int n,float x,float y,float w,float h,float b);
void table(int m,int n,float x,float y,float sc,float sx,float sy);


void display(void);

void myGlutReshape( int,int );



void keyboard(unsigned char key, int x, int y);
void mouse(int , int ,int , int );
void menu(int );
void gamemenu(int key);
void sergamemenu(int key);

int turn(int ,int );


void makeconsole(void);


void reset();
void initvars();
void initgvars();
void neworder();
void prepgame();


void gmain();
void gmain_org(int *pstp,int nn);
int check_org(char *p,int nn);


GLUI_Panel *prep_Panel(GLUI *);

int startwin(GLUI *);
int gmsetwin(GLUI *);
int plrsetwin(GLUI *);
int pausewin(GLUI *);
void cb(int);

void music(int );
//WINBASEAPI BOOL WINAPI Beep(DWORD,DWORD);
//#include <winbase.h>

//BOOL WINAPI FreeConsole(void);

//I am 5








extern int main_win;
extern int mainmenu,gmmenu,sermenu;
extern GLUI *glui[4] ;
extern GLUI *sui;
extern GLUI serui;
extern int gmflag;
extern int n,pln,pltrn;

extern float wd,ht,asr;
extern float gx,gy,bd ;
extern float cw,ch;
extern float px,py;
extern int pst,vi1,vi2,vj1,vj2;
extern char *s;
extern char ttl[85];

extern char **plr;



 
typedef  struct {
				 char name[35] ;
				 char sym	  ;
				 float color[3];
				} 					player;
extern player **gmplr ; 

struct lscolor 
{
 char *n  ;
 float v[3];
} ;

extern int totalclr;
extern int totalsym;
extern struct lscolor stdcolor[];
extern char stdsyms[];

//extern char plr[][25];









#include "serverall.h"
