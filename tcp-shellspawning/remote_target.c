#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8180

int main(int argc, char *argv[]) {
  int   flag=0;
  char  buf[256]={0};
  char  buf_addr[128];
  sprintf(buf_addr, "%p\n", &buf);
  const int on=1;
  
  // socket variables
  struct sockaddr_in server_addr, client_addr;
  int                server_socket, client_socket;
  socklen_t          addr_len;
  char *recieve_buf=malloc(512);
  // initialize socket
  if ((server_socket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))<0) {
    perror("server:socket");
    exit(1);
  }
  server_addr.sin_family      = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port        = htons(PORT);
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));

  // bind
  if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr))<0) {
    perror("server:bind");
    exit(1);
  }
  // listen
  if (listen(server_socket, 1)<0) {
    perror("server:listen");
    close(server_socket);
    exit(1);
  }
  // loop wait
  /* while (1) { */
    // accept connection
    fprintf(stdout, "Waiting for a client...\n");
    addr_len = sizeof(client_addr);
    if ((client_socket=accept(server_socket, (struct sockaddr *)&client_addr, &addr_len))<0) {
      perror("server:accept");
      exit(1);
    }
    fprintf(stdout, "Accepted a connection from [%s, %d]\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
    // send buf address
    write(client_socket, buf_addr, 15);
    // recieve data
    recieve_buf[0] = '\0';
    read(client_socket, recieve_buf, 512);
    // check password
    strcpy(buf, recieve_buf);
    if (strcmp(buf, "p@ssw0rd!")==0) {
      flag = 1;
    }
    if (flag) {
      /* strcpy(recieve_buf, "correct!\n"); */
      /* write(client_socket, recieve_buf, 9); */
      write(client_socket, "correct!\n", 9);
    } else {
      /* strcpy(recieve_buf, "wrong!\n"); */
      /* write(client_socket, recieve_buf, 7); */
      write(client_socket, "wrong!\n", 7);
    }
    /* recieve_buf[0] = '\0'; */
    
    // close clinet socket
    close(client_socket);
  /* } */
  // close server socket
  close(server_socket);

  return (0);
}
