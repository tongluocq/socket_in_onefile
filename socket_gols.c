#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int socket_fd=-1, new_socket, valread;
struct sockaddr_in address;



char buffer[1024] = {0};
char * hello_head = "Hello:  "; //Server!";
int cltconnect_mode = 0;
char * addmessage(char * header, const char * adds){
	
	char * newmessage = (char *)malloc(strlen(header));
	strcpy(newmessage, header);
	
	newmessage = (char *)realloc(newmessage, strlen(header)+ strlen(adds));
	strcat(newmessage, adds);
	return newmessage;
	
}

//char command[10];
//getLine("client> ", command, 1);
//luot: this can read a string command
//luot: https://stackoverflow.com/questions/13479760/c-socket-recv-and-send-all-data
void getLine(char *message, char *buf, int maxLen)
{
    printf("%s", message);
    fgets(buf, maxLen, stdin);
    buf[strlen(buf) - 1] = 0;
}

void getCommand(char *message, char *buf)
{
    printf("%s", message);
	while (( *buf= getchar()) != '\n' &&  *buf!= EOF) { ;}
    //*buf = getchar();
	//printf(" input command %c\n ", *buf);
}

void getcommand_scanf(char *message, char *buf)
{
		//char str[80]; 
      
	    // scan input from user -  
	    // GeeksforGeeks for example 
	    printf("%s", message);
		int c;
		c=scanf("%s", buf); 

		
	    // flushes the standard input 
	    // (clears the input buffer) 
	    int cc = 0;
		while (( cc=getchar()) != '\n')
			{
				printf("dd");
			}
		
		printf("\n");
		

      
	    // scan character from user -  
	    // 'a' for example 
	    // *buf = getchar(); 
      
}
void getcommand(char *message, char *buf)
{
		//char str[80]; 
      
	    // scan input from user -  
	    // GeeksforGeeks for example 
	    printf("%s", message);
		
		
		fgets(buf, 100, stdin);
		if (strcmp(buf, "q")==0) exit(1);
		
		printf("\n");
		

      
	    // scan character from user -  
	    // 'a' for example 
	    // *buf = getchar(); 
      
}

void CreateSocket(){
	//luot: 1st
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd == -1){
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}


}

void SetsockOpt(){
	int opt = 1;
	//luot: 2nd
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
	{
		perror("setsockopt is failed");
		exit(EXIT_FAILURE);
	}
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt is failed 2");
		exit(EXIT_FAILURE);
	}
}

void FillAddress(){
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	
}

int ConvertAddress(){
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	}
	return 0;
}

void  Bind(){	
	//luot: 3rd
	if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
}

void Connect(){
	if (connect(socket_fd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		printf("\nConnection Failed \n"); 
		exit(1);
		//return -1;
	}
	//return 0;
}


void Listen(){

	//luot: 4th
	if (listen(socket_fd , 128 )<0)
	{
		perror(" listen failed");
		exit(EXIT_FAILURE);
	}
	printf(" I am listening.\n");
}

void Accept(){
	int addrlen = sizeof(address);
	//luot: 5th
	printf("start accept\n");
	if ( (new_socket = accept(socket_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen) ) < 0 )
	{
		perror(" accept failed");
		exit(EXIT_FAILURE);
	}
	printf("%d\n", new_socket);
	
}

void srvExcute(){
	//luot: 6th
	//valread = read(new_socket, buffer, 1024);
	valread = recv(new_socket, buffer, 1024, 0);
	printf(">%s\n", buffer);
	//luot: 6th
	char * hello = addmessage(hello_head, "(from Server). ");
	send(new_socket, hello, strlen(hello), 0);
	printf(">server's Hello message sent\n");
	//free(hello);
}




static void server(){
	
	CreateSocket();
	SetsockOpt();
	FillAddress();
	Bind();
	//luot: communication now.
	Listen();
	Accept();
	///*
	while (1){
		
		srvExcute();
	}
	//*/
	/*
	    int temp_sock_desc;
		int len=sizeof(address);//VERY IMPORTANT
	    temp_sock_desc=accept(socket_fd,(struct sockaddr*)&address, (socklen_t *)&len);
	    if(temp_sock_desc==-1)
	    {
	        printf("Error in temporary socket creation");
	        exit(1);
	    }
		int k;
		char buf[100];
	    while(1)
	    {
	        k=recv(temp_sock_desc,buffer, 1024, 0);
	        if(k==-1)
	        {
	            printf("Error in receiving");
	            exit(1);
	        }

	        printf("Message got from client is : %s",buffer);
	        
	        fgets(buf,100,stdin);
	        if(strncmp(buf,"end",3)==0)
	            break;

	        k=send(temp_sock_desc,"hello from server", strlen("hello from server"), 0);
	        if(k==-1)
	        {
	            printf("Error in sending");
	            exit(1);
	        }
	    }
	    close(temp_sock_desc);
	*/
		
}

void cltExcute(char * command){
		printf("%s\n", command);
		char * hello = addmessage(hello_head, "(from Client). ");
		char * hello_2 = addmessage(hello, command);
		int k;
		k = send(socket_fd, hello_2, strlen(hello_2), 0);
		if(k==-1) {
			printf("Error in sending \n");
		} else {
			printf("$>message sent from client. %s\n", hello_2);
		}
		char buffer2[1024] = {0};
		//valread = read(socket_fd, buffer2, 1024);
		valread = recv(socket_fd, buffer2, 1024, 0);
		if (valread == -1){
			printf("Error in receiving\n");
		} else {
			printf("$>%s\n", buffer2);
		}

		free(hello);
}

static void client(){

	    char c[1];
	    char *command=c;

		
		CreateSocket();
		FillAddress();
		ConvertAddress();
		Connect();
		///*
		while (1){
			//luot: both command, command_scanf are good
			//getCommand(">>>", command);
			//printf("Use command\n");
			getcommand_scanf(">>>", command);
			//printf("Use command_scanf\n");
			if (strcmp(command, "q") == 0) break;
			cltExcute(command);
			//getLine("client> ", command, 1);
			//printf("\n");

		}
		//*/
		
		/*
		int k;
		while(1)
		    {
		        printf("\nEnter data to be send to server: ");
				char buf[100];
		        fgets(buf,100,stdin);
		        if(strncmp(buf,"end",3)==0)
		            break;

		        k=send(socket_fd,buf,100,0);
		        if(k==-1)
		        {
		            printf("Error in sending");
		            exit(1);
		        }

		        k=recv(socket_fd,buf,100,0);
		        if(k==-1)
		        {
		            printf("Error in receiving");
		            exit(1);
		        }

		        printf("Message got from server is : %s",buf);
		    }
			*/
}

int main(int argc, char const * argv[]){

	if (argc>1) printf(" enter mode of only one command;\n");
	printf("%s\n", argv[0]);
	memset(&address, 0, sizeof(address));
	if (strcmp(argv[0], "./golserver")==0){
		//printf(" this is server\n");
		server();
		
	} else {
		if (argc>=2) cltconnect_mode = atoi(argv[1]);
		
		client();
	}

	return 0;

} //main is over

//gcc   -o golclient  -std=c99 -Wall  -Wextra -pedantic-errors socket_gols.c &&  gcc   -o golserver  -std=c99 -Wall  -Wextra -pedantic-errors socket_gols.c 

//http://www.cs.tau.ac.il/~eddiea/samples/Non-Blocking/tcp-nonblocking-server.c.html
//https://pubs.opengroup.org/onlinepubs/009695399/functions/send.html

/*
how to use the two programm in one file socket communication toolbox:

run server in one terminal, it will wait client sending msg

Tongs-MacBook-Pro:Downloads tongluo$ ./golserver
./golserver
 I am listening.
start accept

4
>Hello:  (from Client). 
>server Hello message sent
>Hello:  (from Client). 
>server Hello message sent
>Hello:  (from Client). 
>server Hello message sent
>Hello:  (from Client). 
>server Hello message sent
>Hello:  (from Client). 
>server Hello message sent
>Hello:  (from Client). 
>server Hello message sent
>Hello:  (from Client). 

*/

/*

run client in other terminal, then type msg, waiting server's reply


Tongs-MacBook-Pro:Downloads tongluo$ ./golclient 0 hhh
 only one command;
./golclient
>>>hu

Use command_scanf
$>message sent from client. Hello:  (from Client). 
$>Hello:  (from Server). 
>>>糯米 糕
dddddddd
Use command_scanf
$>message sent from client. Hello:  (from Client). 
$>Hello:  (from Server). 
>>>^C

*/

