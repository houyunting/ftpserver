#include "ftpSession.h"
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>


using namespace std;

Session::Session(int sidt)
{
	sid =sidt;
}

Session::Session()
{
	
	return 0;
}
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
	int HandleConnection(); 
};