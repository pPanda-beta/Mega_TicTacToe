#include <windows.h>
#include <stdio.h>
#include <fcntl.h>





void redirectst(FILE *fp,DWORD hnd)
{ *fp=*fdopen(_open_osfhandle((intptr_t)hnd, _O_TEXT),"wb+"); }




void getconsole()
{
 AllocConsole();
 redirectst(stdin,STD_INPUT_HANDLE);
 redirectst(stdout,STD_OUTPUT_HANDLE);
 redirectst(stderr,STD_ERROR_HANDLE); 
}


void makeconsole()
{
 AllocConsole( );   
 freopen("CONIN$","wb+",stdin);   
 freopen("CONOUT$","wb+",stdout); 
 freopen("CONOUT$","wb+",stderr);
}



#define mywmain()  \
int APIENTRY WinMain(\
HINSTANCE hInstance,\
HINSTANCE hPrevInstance,\
LPSTR lpCmdLine,\
int nCmdShow)

