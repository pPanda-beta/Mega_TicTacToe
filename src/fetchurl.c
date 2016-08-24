


/*****************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * $Id: getinmemory.c,v 1.9 2005/02/04 23:53:12 bagder Exp $
 *
 * Example source code to show how the callback function can be used to
 * download data into a chunk of memory instead of storing it in a file.
 *
 * This exact source code has not been verified to work.
 */

#include <stdio.h>

#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>






FILE *fetchurl(char *url,char *agent)
{
  CURL *curl_handle;
  FILE *fp=tmpfile();
 
  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* specify URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, url);

  /* send all data to this function  */
 curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, fwrite);

  /* we pass our fp struct * to the callback function */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)fp);

  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, agent);

  /* get it! */
  if(curl_easy_perform(curl_handle) != CURLE_OK)
      { fclose(fp); fp=NULL ; return fp;}

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);

//printf("Complete\a\n");
//  fputc(EOF,fp);
 
  
  FILE *log=fopen("MT3_curl.log","a+");
//  fprintf(log,"User Agent : %s\nURL: %s\nreturned:\n%s\n",agent,url,fp->_base);
    fprintf(log,"URL: %s\nreturned:\n%s\n",url,fp->_base);
    
  fclose(log);
  
  
  
  rewind(fp);
  return fp;
}
