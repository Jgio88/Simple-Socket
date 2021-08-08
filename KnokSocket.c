#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

/*
struct addrinfo {
   int              ai_flags;
   int              ai_family;
   int              ai_socktype;
   int              ai_protocol;
   socklen_t        ai_addrlen;
   struct sockaddr *ai_addr;
   char            *ai_canonname;
   struct addrinfo *ai_next;
};
*/


int sChck1(char* str,int connectionfd){
  char* tok;
  tok = strtok(str,"|");
  //DEBUG TOK -  printf("%s becomes %s\n",str,tok);
  if (strcmp(tok,"REG") == 0){
    tok = strtok(NULL,"|");
    if(strcmp(tok,"12")==0){
      tok = strtok(NULL,"|");
      if(strcmp(tok,"Who's there?")==0){
	printf("REG|12|Who's there?|\n");
      }else{
	printf("M1CT\n");
	write(connectionfd,"M1CT\n",5);
	exit(EXIT_FAILURE);
      }
    }else{
      printf("M1LN\n");
      write(connectionfd,"M1LN\n",5);
      exit(EXIT_FAILURE);
    }
  }else{
    printf("M1FT\n");
    write(connectionfd,"M1FT\n",5);
    exit(EXIT_FAILURE);
  } 
  return 1;
}

int sChck3(char* str, int connectionfd){
  char* tok;
  tok = strtok(str,"|");
  //DEBUG TOK -  printf("%s becomes %s\n",str,tok);
  if (strcmp(tok,"REG") == 0){
    tok = strtok(NULL,"|");
    if(strcmp(tok,"8")==0){
      tok = strtok(NULL,"|");
      if(strcmp(tok,"Boo who?")==0){
        printf("REG|8|Boo who?|\n");
      }else{
        printf("M3CT\n");
	write(connectionfd,"M3CT\n",5);
        exit(EXIT_FAILURE);
      }
    }else{
      printf("M3LN\n");
      write(connectionfd,"M3LN\n",5);
      exit(EXIT_FAILURE);
    }
  }else{
    printf("M3FT\n");
    write(connectionfd,"M3FT\n",5);
    exit(EXIT_FAILURE);
  }
  return 2;
}

int sChck5(char* str, int connectionfd){
  char* tok;
  tok = strtok(str,"|");
  //DEBUG TOK -  printf("%s becomes %s\n",str,tok);
  if (strcmp(tok,"REG") == 0){
    tok = strtok(NULL,"|");
    if(strcmp(tok,"7")==0){
      tok = strtok(NULL,"|");
      if(strcmp(tok,"...hah.")==0){
        printf("REG|7|...hah.|\n");
      }else{
        printf("M5CT\n");
	write(connectionfd,"M5CT\n",5);
        exit(EXIT_FAILURE);
      }
    }else{
      printf("M5LN\n");
      write(connectionfd,"M5LN\n",5);
      exit(EXIT_FAILURE);
    }
  }else{
    printf("M5FT\n");
    write(connectionfd,"M5FT\n",5);
    exit(EXIT_FAILURE);
  }
  return 3;
}




int main (int argc, char **argv){

  int error;
  int sfd;
  int i;


  if(argc<2){
    printf("Wrong amount of arguments. \n");
    exit(EXIT_FAILURE);
  }

  //Setting up hints struct
  struct addrinfo hints, *address_list, *addr;
  //zero all date for hints.
  memset(&hints, 0, sizeof(struct addrinfo));
  //accept IPv4 or IPv6
  hints.ai_family = AF_UNSPEC;
  //socket with r/w streams
  hints.ai_socktype = SOCK_STREAM;
  //socket flag setup
  hints.ai_flags = AI_PASSIVE;


  //Get port num
  
  int pNum;
  pNum = atoi(argv[1]);

  
  //ERROR - port #
  if (pNum > 64000 || pNum<5000) {
    printf("Port number not between 5,000-64,000.\n");
    exit(EXIT_FAILURE);
  }
  
  
  //SET - Addrinfo
  error = getaddrinfo(NULL, argv[1], &hints, &address_list);  
  //ERROR - Addrinfo list.
  if(error){
    fprintf(stderr, "%s\n", gai_strerror(error));
    exit(EXIT_FAILURE);
  }
  printf("Got ADDR\n");

  //SET - socket
  for (addr = address_list; addr != NULL; addr = addr->ai_next) {
        sfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
	if(sfd == -1){
	  continue;
	}

	if((bind(sfd, addr->ai_addr, addr->ai_addrlen) == 0) && (listen(sfd,5)==0)){
	  break;
	}

	close(sfd);
  }	
  //ERROR - socket
  if(sfd < 0){
    printf("Error getting socket.\n;");
    exit(EXIT_FAILURE);
  }
  printf("Got sock\n");

  //ERROR - bind
  if(bind<0){
    printf("Error binding.\n");
    exit(EXIT_FAILURE);
  }
  printf("Got bind\n");

  //ERROR - listen
  if(listen<0){
    printf("Error listening.\n;");
    exit(EXIT_FAILURE);
  }
  printf("Got listen\n");

  printf("[%s:%s] Bound and Listening.\n","java.cs.rutgers.edu",argv[1]);

  //Accept
  struct sockaddr_storage remote;
  socklen_t remote_len = sizeof(struct sockaddr_storage);
  //int connectionfd =  accept(sfd, (struct sockaddr *) &remote, &remote_len);

  char buf[100];
  int nread;
  int exitN = 0;
  int j = 0;
  //char* kk =  "Knock, knock.";

  

    int connectionfd = accept(sfd,(struct sockaddr *)&remote, &remote_len);

    if (connectionfd<0){
      printf("Error in accept.\n");
      exit (EXIT_FAILURE);
    }

    printf("REG|13|Knock, knock.|\n");
    write(connectionfd,"REG|13|Knock, knock.|\n",23);
    
    for(;;){
      

      nread = read(connectionfd,buf,sizeof(buf));
      buf[strcspn(buf,"\n")] = '\0';

      // printf("From Client: %d, %s\n",nread, buf);

      if(strlen(buf)>1 && j == 0){
	j = sChck1(buf,connectionfd);
      printf("REG|4|Boo.|\n");
      write(connectionfd,"REG|4|Boo.|\n",13);
      continue;
      }

      if(j == 1){
	/*
	nread = read(connectionfd,buf,sizeof(buf));
	buf[strcspn(buf,"\n")] = '\0';
	*/
	j = sChck3(buf,connectionfd);
	printf("REG|28|Don't cry. It's only a joke!|\n");
	write(connectionfd,"REG|28|Don't cry. It's only a joke!|\n",38);
	continue;

      }

      if(j == 2){
	//printf("REG|28|Don't cry. It's only a joke!|\n");
	/*
	nread = read(connectionfd,buf,sizeof(buf));
        buf[strcspn(buf,"\n")] = '\0';
	*/
	j = sChck5(buf,connectionfd);
      }
      
      if( j == 3){
	break;
      }
  }
   
  close(sfd);
  return EXIT_SUCCESS;
  
}
    
