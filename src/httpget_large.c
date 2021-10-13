
//***************************************************************************
// File name:		httpget_large
// Author:			Cayden Wagner
// Date:				October 5 2021
// Class:				CS 360
// Assignment:	Lab HTTP2
// Purpose:			Practice writing a Large HTTP Request
//***************************************************************************

#define _GNU_SOURCE

#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

const char CONTENT_LENGTH_HEADER[16] = "Content-Length: ";

int getContentLength(char[]);
int getHeaderLength(char[]);

/****************************************************************************
 Function:		main
 
 Description:	make a single HTTP request. Display the request and response
 
 Parameters:	int argc: number of command line arguments
							char **argv: the command line arguments
 
 Returned:		EXIT_SUCCESS
****************************************************************************/
int main(int argc, char **argv)
{
  const int MAX_SIZE = 4096, HTTP_PORT = 80;

  char szGetRequest[MAX_SIZE];
  char szGetResponse[MAX_SIZE];
  
  int connSocket, contentLength, bytesRead = 0;

  struct sockaddr_in sConnAddr;

  connSocket = socket(AF_INET, SOCK_STREAM, 0);
  sConnAddr.sin_family = AF_INET;
  sConnAddr.sin_port = htons(HTTP_PORT);
  inet_aton(argv[1], &sConnAddr.sin_addr);
  if (-1 == connSocket)
  {
     perror("socket failed!\n");
     return -1;
  }
  
  connect(connSocket, (struct sockaddr *) &sConnAddr, sizeof(sConnAddr));

  for(int i = 2; i < argc; i++)
  {
    memset(szGetRequest, '\0', sizeof(szGetRequest));
    memset(szGetResponse, '\0', sizeof(szGetResponse));
    bytesRead = 0;

    strncat(szGetRequest, "GET ", (MAX_SIZE - strlen(szGetRequest)) - 1 );
    strncat(szGetRequest, argv[i], (MAX_SIZE - strlen(szGetRequest)) - 1 );
    strncat(szGetRequest, " HTTP/1.1\r\nHost: ", (MAX_SIZE - strlen(szGetRequest)) - 1 );
    strncat(szGetRequest, argv[1], (MAX_SIZE - strlen(szGetRequest)) - 1 );
    strncat(szGetRequest, "\r\nConnection: Keep-Alive\r\n\r\n", (MAX_SIZE - strlen(szGetRequest)) - 1 );

    printf(">|%s<|\n\n", szGetRequest);

    send(connSocket, szGetRequest, strlen(szGetRequest), 0);

    if ((bytesRead = recv(connSocket, &szGetResponse, sizeof(szGetResponse), 0)) < 0)
    {
      perror("recieve failed!\n");
      return -1;
    }

    contentLength = getContentLength(szGetResponse);
    contentLength += getHeaderLength(szGetResponse);

    printf("recv()\n");

    while (bytesRead < contentLength)
    {
      memset(szGetRequest, '\0', sizeof(szGetResponse));
      bytesRead += recv(connSocket, &szGetResponse, sizeof(szGetResponse), 0);

      printf("recv()\n");
    }

    printf("\nTotal Bytes Read: %d\n\n", bytesRead);
  }
  close(connSocket);

  return EXIT_SUCCESS; // aspirational
}
/****************************************************************************
 Function:		
 
 Description:	
 
 Parameters:	
 
 Returned:		
****************************************************************************/
int getContentLength(char response[])
{
  char *pStr = '\0', *pEnd = '\0', tempChar;
  int contentLength;

  pStr = strstr(response, "Content-Length: ");

  if ( NULL == pStr )
  {
    printf("Error, Content Length Not Found\n\n");
    return EXIT_FAILURE;
  }

  while ( !isdigit(*pStr))
  {
    ++pStr;
  }

  pEnd = pStr;

  while ( isdigit(*pEnd))
  {
    ++pEnd;
  }

  tempChar = *pEnd;
  *pEnd = '\0';
  contentLength = atoi(pStr);
  *pEnd = tempChar;

  return contentLength;
}
/****************************************************************************
 Function:		
 
 Description:	
 
 Parameters:	
 
 Returned:		
****************************************************************************/
int getHeaderLength(char response[])
{
  char* pStr, *tempPtr;
  int count = 0;
  pStr = strstr(response, "\r\n\r\n");

  tempPtr = &response[0];

  while(tempPtr != pStr)
  {
    tempPtr++;
    count++;
  }

  return count;
}