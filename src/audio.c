#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>



char *aulist[]=
{ "01.wav","02" };







void music(int ano)
{
 char fnm[255];

 sprintf(fnm,"audio/%02d.wav",ano);
 puts(fnm);
 PlaySound(fnm,NULL,SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT );

}



