#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<string>
#include<vector>


using namespace std;

class Session
{
public:
	Session(int cfdt);
private:
	int cfd;
	int dfd;
	struct sockaddr_in sai;
	string rootdir;
	string currentdir;
	string uname;
	string upassword;
	vector<string> arg_vec;
public:
	int HandleConnection();
	string parseCmd(char []);
	string parseArg(char []);
	int userHandle(string c, char c_b[]);
	int passHandle(string c, char c_b[]);
	int retrHandle(string c, char c_b[]);
	int putHandle(string c, char c_b[]);
	int portHandle(string c, char c_b[]);
int pasvHandle(string c, char c_b[]);
	int undefHandle(string c, char c_b[]);
};
