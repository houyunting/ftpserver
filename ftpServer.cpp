#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
//#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>

#include<arpa/inet.h>
#include "ftpSession.h"
using namespace std;
int main()
{
	int lfd = socket(AF_INET, SOCK_STREAM, 0);



	struct sockaddr_in  sai;
	sai.sin_family = AF_INET;
	sai.sin_port = htons(6000);
	sai.sin_addr.s_addr = htonl(INADDR_ANY);
	cout << INADDR_ANY;

	if(bind(lfd, (struct sockaddr *) &sai, sizeof(sockaddr)) == -1)
	{
		cout << getpid() <<" Binding  Socket Error !!!\n";
	}
	else
	{
		cout <<getpid() << " Binding Socket Sucess !!!\n";
	}


	if(listen(lfd,10) == -1)
	{
		cout <<getpid() << " Listen Failture !!!\n";
	}
	else
	{
		cout <<getpid() << " Listen Sucess!!\n";
	}

	int cfd;
	while(1)
	{
		cfd = accept(lfd,NULL, NULL);
		if(cfd == -1)
		{
			cout << getpid() << " Failure in accept\n";
			return -1;
		}
		switch(fork())
		{
			case -1:
				cout << getpid() << " Create Communation Process Failure\n";
				close(cfd);
				break;
			case 0:
			{
				cout << getpid() << " Create Communation Process Sucess\n";
				close(lfd);
				Session sn(cfd);
				sn.HandleConnection();
				return 0;
				
				break;
			}
			default:
				close(cfd);
				break;

		}
	}

	return 0;

}
