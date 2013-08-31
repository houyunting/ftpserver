#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
//#include<netdb.h>
#include<netinet/in.h>
using namespace std;
int main()
{
	int sid = socket(AF_INET, SOCK_STREAM, 0);



	struct sockaddr_in  sai;
	sai.sin_family = AF_INET;
	sai.sin_port = htonl(6789);
	sai.sin_addr.s_addr = INADDR_ANY;

	if(bind(sid, (struct sockaddr *) &sai, sizeof(sockaddr)) == -1)
	{
		cout << "Binding  Socket Error !!!\n";
	}
	else
	{
		cout << "Binding Socket Sucess !!!\n";
	}

	while(1)
	{
		if(listen(sid,10) == -1)
		{
			cout << "Listen Failture !!!\n";
		}
	}

	return 0;

}