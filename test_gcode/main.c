#include <stdio.h>
#include "unistd.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "stdlib.h"
#include "string.h"

#define MAX 128
int main (int argc, char *argv[])
{
	
	int sock_desc, conn_desc;
	int imode = 0; // blocking mode

	struct sockaddr_in serv_addr,client_addr;
	char buf[MAX];
		
	sock_desc = socket(AF_INET,SOCK_STREAM,0);	 
	if(sock_desc<0)
	{
		
		perror("socket descriptor failed\n");
		exit(0);
	}

	bzero((char*)&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(3000);

	if(bind(sock_desc,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0) 
	{
		printf("failed to bind\n");
	}

	listen(sock_desc,5);

	while(1)
	{
		conn_desc = accept(sock_desc,(struct sockaddr*)NULL,NULL);

		while(1)
		{
			recv(conn_desc,buf,sizeof(buf),0);

			gcode_parse(buf);

			sleep(1);
		}
		close(conn_desc);

		sleep(1);
	}

	return 0;
}

