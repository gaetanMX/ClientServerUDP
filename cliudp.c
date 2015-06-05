#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(){

  int res,res2,fin,toleng,aux,res_bind;
  int fromleng;
  const char* adr = "192.168.200.163";
 
  char* message = "!! ola !! quetal ?? \n";
  char reception[100];

  int ma_socket;

  struct sockaddr_in to ;
  struct sockaddr_in from ;
 
  memset(&to,0,sizeof(to));
  memset(&from,0,sizeof(from));
	 from.sin_port = htons(54000);
 	 to.sin_family = AF_INET;
 	 to.sin_port = htons(54015);
 	 aux = inet_aton(adr,&(to.sin_addr)) ;
	 if(aux == 0){
		perror("echec inet_aton");
		exit(5);
	}
 
 	 fromleng = sizeof(from) ;
 	 toleng = sizeof(to) ;

//fromleng = sizeof( struct sockaddr_in) ;

	  //creation point de communication
	   ma_socket = socket(AF_INET,SOCK_DGRAM,0);
	   if(ma_socket == -1){
  	
  		perror("echec creation socket");
		exit(1);
	  }

	//bind
	res_bind = bind(ma_socket,(struct sockaddr*)&from,fromleng);
	if(res_bind == -1) {
		perror(" echec nommage point de communication !!!!! (bind)  \n");
		exit(2);
	}
	
 
	//return  number of characters  sent, error -1
	  res = sendto (ma_socket,message,strlen(message),0,(struct sockaddr*)&to,toleng);
	  if(res == -1) {
		perror(" echec envoi!  (sendto)");
		exit(2);
	}
	printf("message envoyé:  : %s\n",message);
	// return number of bytes received, or -1 if error 
   	res2 = recvfrom(ma_socket,&reception,strlen(reception),0,(struct sockaddr*)&from,(socklen_t*)&fromleng);
 	if(res2 == -1) {
		perror(" echec reception!   (recvfrom)");
		exit(3);
	}
       printf("message reçu:  : %s\n",reception);
	//returns  zero on success.  On error, -1 is returned
   	fin = close(ma_socket);
 	if(fin == -1) {
		perror(" echec fermeture!  (close)");
		exit(4);
	}
	return 0;

}
