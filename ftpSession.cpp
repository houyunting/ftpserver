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