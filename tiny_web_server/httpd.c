#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>

//macros
#define ROOT getenv("PWD")
#define CONNMAX 1000
#define SERVER_STRING "Server: Fan's server\r\n"


/* char webPage[] = */
/* "HTTP/1.1 200 OK\r\n" */
/* "Content-Type: text/html; charset=UTF-8\r\n\r\n" */
/* "<!DOCTYPE html>\r\n" */
/* "<html>\r\n" */
/* "<head><title>Hello World</title></head>\r\n" */
/* "<body><center><h1>Hello My World</h1><br><img src=\"happytimes.jpg\"></center></body>\r\n" */
/* "</html>\r\n"; */

int listenfd, client[CONNMAX];
unsigned short PORT = 10000;
void not_found(int);

void not_found(int client)
{
  char buf[1024];

  sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
  send(client, buf, strlen(buf), 0);
  sprintf(buf, SERVER_STRING);
  send(client, buf, strlen(buf), 0);
  sprintf(buf, "Content-Type: text/html\r\n");
  send(client, buf, strlen(buf), 0);
  sprintf(buf, "\r\n");
  send(client, buf, strlen(buf), 0);
  sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
  send(client, buf, strlen(buf), 0);
  sprintf(buf, "<BODY><P>The server could not fulfill\r\n");
  send(client, buf, strlen(buf), 0);
  sprintf(buf, "your request because the resource specified\r\n");
  send(client, buf, strlen(buf), 0);
  sprintf(buf, "is unavailable or nonexistent.\r\n");
  send(client, buf, strlen(buf), 0);
  sprintf(buf, "</BODY></HTML>\r\n");
  send(client, buf, strlen(buf), 0);
}

int main(int argc, char *argsv[])
{
  printf("Server started at port no. %s%hu%s with root directory as %s%s%s\n","\033[36m", PORT,"\033[0m","\033[36m",ROOT,"\033[0m");


  struct sockaddr_in server_addr, client_addr;
  socklen_t sin_len = sizeof(client_addr);
  int fd_server, fd_client;
  char buf[2048];
  int fdImg;
  int on = 1;
  int bytes_read;
  char data_to_send[1024];

  fd_server = socket(AF_INET, SOCK_STREAM, 0);
  if(fd_server < 0)
  {
    perror("socket");
    exit(1);
  }

  setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  /* inet_aton("127.0.0.1", &server_addr.sin_addr); */
  server_addr.sin_port = htons(PORT);

  //bind
  if(bind(fd_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1)
  {
    perror("bind");
    close(fd_server);
    exit(1);
  }


  if(listen(fd_server, 10) == -1)
  {
    perror("listen");
    close(fd_server);
    exit(1);
  }

  while(1)
  {
    fd_client = accept(fd_server, (struct sockaddr *) &client_addr, &sin_len);
    if(fd_client == -1)
    {
      perror("Can't connect to client\n");
      continue;
    }


    if(!fork())
    {
      char *reqline[3], path[99999];
      /*chlid process dosen't need it */
      close(fd_server);
      memset(buf, 0, 2048);
      read(fd_client, buf, 2047);
      int fd;

      reqline[0] = strtok (buf, " \t\n");

      if(!strncmp(reqline[0], "GET\0", 4))
      {
        reqline[1] = strtok (NULL, " \t");
        reqline[2] = strtok (NULL, " \t\n");
        if ( strncmp( reqline[2], "HTTP/1.0", 8)!=0 && strncmp( reqline[2], "HTTP/1.1", 8)!=0 )
        {
          write(fd_client, "HTTP/1.0 400 Bad Request\n", 25);
        }
        else
        {
          if ( strncmp(reqline[1], "/\0", 2)==0 )
            reqline[1] = "/index.html";        //Because if no file is specified, index.html will be opened by default (like it happens in APACHE...
          strcpy(path, ROOT);
          strcpy(&path[strlen(ROOT)], reqline[1]);

          if ((fd = open(path, O_RDONLY)) != -1)    //FILE FOUND
          {
            send(fd_client, "HTTP/1.0 200 OK\n\n", 17, 0);
            while ( (bytes_read = read(fd, data_to_send, 1024)) > 0 )
                write (fd_client, data_to_send, bytes_read);
          }
          else
          {
            //File not found
            not_found(fd_client);
          }
        }
          close(fdImg);
      }

      close(fd_client);
      exit(0);

    }
    /*parent process */
    close(fd_client);
  }









  return 0;
}
