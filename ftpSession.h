#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>


using namespace std;

class Session
{
public:
	Session(int sidt);
private:
	int sid;
	string rootdir;
	string currentdir;
	string uname;
	string upassword;
	HandleConnection(); 
};