#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
//#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>

#include<arpa/inet.h>


using namespace std;
int main()
{
	int lfd = socket(AF_INET, SOCK_STREAM, 0);



	struct sockaddr_in  sai;
	sai.sin_family = AF_INET;
	sai.sin_port = htons(5000);
	sai.sin_addr.s_addr = htonl(INADDR_ANY);
	cout << INADDR_ANY;

	if(bind(lfd, (struct sockaddr *) &sai, sizeof(sockaddr)) == -1)
	{
		cout << "Binding  Socket Error !!!\n";
	}
	else
	{
		cout << "Binding Socket Sucess !!!\n";
	}


	if(listen(lfd,10) == -1)
	{
		cout << "Listen Failture !!!\n";
	}
	else
	{
		cout << "Listen Sucess!!\n";
	}

	int cfd;
	while(1)
	{
		cfd = accept(lfd,NULL, NULL);
		switch(fork())
		{
			case -1:
				cout << "Create Communation Process Failure\n";
				break;
			case 0:
				cout << "Create Communation Process Sucess\n";
				close(lfd);
				Session sn(cfd);
				sn.HandleConnection();
				break;

			default:
				break;

		}
	}

	return 0;

}