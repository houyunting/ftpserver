#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<string>


using namespace std;

class Session
{
public:
	Session(int cfdt);
private:
	int cfd;
	string rootdir;
	string currentdir;
	string uname;
	string upassword;
public:
	int HandleConnection();
	string parseCmd(char []); 
};
