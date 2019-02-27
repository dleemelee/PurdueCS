
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

int QueueLength = 5;
pthread_mutex_t mutex;
pthread_mutexattr_t mutex_attr;

void poolSlave( int socket);
void processRequest( int socket );
void processRequestThread( int socket );
int main(int argc, char * argv[])
{
   // Add your HTTP implementation here

  //take in input
  if(argc < 2 || argc > 3) {
    printf("ARGS NOT 2 or 3, %d\n", argc);
    exit(-1);
  }
  
  int conc = 0;
  int port = 0;
  if(argc == 3) {
    if( !strcmp(argv[1], "-f")){
      conc = 1;
    }
    else if( !strcmp(argv[1], "-t")){
      conc = 2;
    }
    else if( !strcmp(argv[1], "-p")){
      conc = 3;
    }
    port = atoi( argv[2] );
  } 
  else if( argc == 2 ) { 
    port = atoi( argv[1] );
  }

  if(port == 0 || port < 1024 || port > 65535) {
    port = 1111;
    printf("Invalid port number, default port set: %d\n", port);
  }

  struct sockaddr_in serverIPAddress;
  memset( &serverIPAddress, 0, sizeof(serverIPAddress));
  serverIPAddress.sin_family = AF_INET;
  serverIPAddress.sin_addr.s_addr = INADDR_ANY;
  serverIPAddress.sin_port = htons((u_short) port);

  int masterSocket = socket(PF_INET, SOCK_STREAM, 0);
  if(masterSocket < 0) {
    perror("socket");
    exit(-1);
  }

  int optval = 1;
  int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *) &optval, sizeof(int));
  
  int error = bind(masterSocket, (struct sockaddr *)&serverIPAddress, sizeof(serverIPAddress));

  if(error) {
    perror("bind");
    exit(-1);
  }
  
  error = listen(masterSocket, QueueLength);
  if(error) {
    perror("listen");
    exit(-1);
  }
  
  if(conc == 3) {
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutex_init(&mutex, &mutex_attr);

    pthread_t tid[5];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    for(int i = 0; i < 5; i++) {
      pthread_create(&tid[i], &attr, (void *(*)(void *))poolSlave, (void *)masterSocket);
    }
    pthread_join(tid[0], NULL);
  }
  else{
    while(1) {
      struct sockaddr_in clientIPAddress;
      int alen = sizeof(clientIPAddress);
      int slaveSocket = accept(masterSocket, (struct sockaddr *)&clientIPAddress, (socklen_t*)&alen);

      if(slaveSocket < 0) {
        perror("accept");
        exit(-1);
      }
      if(conc == 0) {
        processRequest(slaveSocket);
        close(slaveSocket);
      }
      else if(conc == 1) {
        pid_t slave = fork();
        if(slave == 0) {
          processRequest(slaveSocket);
          close(slaveSocket);
          exit(EXIT_SUCCESS);
        }
        close(slaveSocket);
      }
      else if(conc == 2) {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
        pthread_create(&tid, &attr, (void * (*)(void *))processRequestThread, (void *) slaveSocket);  
      }
    }
  }
}
void poolSlave( int socket ) {
  while(1) {
    
    struct sockaddr_in clientIPAddress;
    int alen = sizeof(clientIPAddress);
    int slaveSocket = accept(socket, (struct sockaddr *)&clientIPAddress, (socklen_t*)&alen);
    processRequest(slaveSocket);
    close(slaveSocket);
  }
}

void processRequestThread(int socket) {
  processRequest(socket);
  close(socket);
}

void processRequest(int socket) {
  const int MaxName = 1024;
  char name[MaxName + 1];
  int nameLength = 0;
  int n;
  int gotGet = 0;
  int gotFilename = 0;
  int getCounter = 0;
  char file[MaxName+1];
  int filen = 0;
  unsigned char newChar;
  unsigned char oldChar = 0;
  int flag = 0; 
  while( (n = read(socket, &newChar, sizeof(newChar))) ) {
    nameLength++;
    if(newChar == ' ') {
      if(gotGet == 0) {
        if(name[nameLength-4] == 'G' && name[nameLength-3] == 'E' && name[nameLength-2] == 'T') {
          gotGet = 1;
        }
      }
      else if(gotFilename == 0) {
        gotFilename = 1;
        file[filen] = '\0'; 
      }
      flag = 0;
    }
    else if( newChar == '\n' && oldChar == '\r' ) {
      if(flag) {
        break;
      }
      flag = 1;
    }
    else{
      if(newChar != '\r') {
        flag = 0;
      }
      if(gotGet && !gotFilename) {
        file[filen++] = newChar;
      }
      oldChar = newChar;
      name[nameLength-1] = newChar;
    }
  }
  char cwd[256] = {0};
  getcwd(cwd,256);
  if(!strncmp(file, "/icons", 6) || !strncmp(file, "/htdocs", 7) || !strncmp(file, "/cgi-bin", 8))   {
    strcat(cwd, "/http-root-dir/");
    strcat(cwd, file);
  }
  else {
    strcat(cwd, "/http-root-dir/htdocs/");
    if(!strcmp(file, "/")) {
      strcat(cwd, "index.html");
    }
    else {
      strcat(cwd, file);
    }
  }
  int i;
  int countDot = 0;
  int countSlash = 0;
  for(i = 0; file[i] != '\0' ||i < 1025 ; i++) {
    if(file[i] == '/') {
      countSlash++;
    }
    else if(file[i] == '.' && file[i-1] == '.' && i != 0) {
      countDot++;
    }
  }
  countSlash -= countDot;
  if( countDot > countSlash ) {
    perror("realpath");
    exit(-1);
  }

  char contentType[MaxName+1] = {0};
  if(strstr(cwd, ".html")!=0) {
    strcpy(contentType, "text/html");
  }
  else if(strstr(cwd, ".gif")!=0) {
    strcpy(contentType, "image/gif");
  }
  else {
    strcpy(contentType, "text/plain");
  }
  const char* serverType = "CS 252 lab 5";
  const char* protocol = "HTTP/1.1";
  //write(socket, file, strlen(file));
  //write(socket, "\r\n", 2);
  //write(socket, cwd, strlen(cwd));
  //write(socket, "\r\n", 2);
  FILE * open = fopen(cwd, "r");
  if(open != NULL) {
    write(socket, protocol, strlen(protocol));
    write(socket, " ", 1);
    write(socket, "200", 3);
    write(socket, " ", 1);
    write(socket, "Document", 8);
    write(socket, " ", 1);
    write(socket, "follows", 7);
    write(socket, "\r\n", 2);
    write(socket, "Server:", 7);
    write(socket, " ", 1);
    write(socket, serverType, strlen(serverType));
    write(socket, "\r\n", 2);
    write(socket, "Content-type:", 13);
    write(socket, " ", 1);
    write(socket, contentType, strlen(contentType));
    write(socket, "\r\n", 2);
    write(socket, "\r\n", 2);

    int count = 0;
    char c;
    while(count = read(fileno(open), &c, sizeof(c)) != 0){
      if(write(socket, &c, sizeof(c)) != count){
        perror("write");
      }
    } 
    fclose(open); 
  }
  else {

    const char *notFound = "File not Found";
    write(socket, protocol, strlen(protocol));
    write(socket, " ", 1);
    write(socket, "404", 3);
    write(socket, " ", 1);
    write(socket, "File", 4);
    write(socket, "Not", 3);
    write(socket, "Found", 5);
    write(socket, "\r\n", 2);
    write(socket, "Server:", 7);
    write(socket, " ", 1);
    write(socket, serverType, strlen(serverType));
    write(socket, "\r\n", 2);
    write(socket, "Content-type:", 13);
    write(socket, " ", 1);
    write(socket, contentType, strlen(contentType));
    write(socket, "\r\n", 2);
    write(socket, "\r\n", 2);
    write(socket, notFound, strlen(notFound));  

  }
  
}
