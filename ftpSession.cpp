#include "ftpSession.h"
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<queue>
#include<vector>
#include<arpa/inet.h>


using namespace std;

vector<string> split(string& str,const char* c)
{
    char *cstr, *p;
    vector<string> res;
    cstr = new char[str.size()+1];
    strcpy(cstr,str.c_str());
    p = strtok(cstr,c);
    while(p!=NULL)
    {
        res.push_back(p);
        p = strtok(NULL,c);
    }
    return res;
}

enum  CMD
{
	USER,
	PASS,
	RETR,
	TYPE,
	STOR,
	QUIT
};

Session::Session(int cfdt)
{
	cfd =cfdt;
}

int Session::HandleConnection()
{
	cout << getpid() << " in Connection Handler\n";
	//char buf[1024];
	//int recv_sz = recv(cfd, buf, 1024, 0);
	char sucess[] = "220 hello\r\n";
	int send_sz = send(cfd, sucess,strlen(sucess),0);
	

	while(1)
	{
		char cmd_buf[1024];
		memset(cmd_buf, 0, sizeof(cmd_buf));
		int recv_sz = recv(cfd, cmd_buf, 1024, 0);
		if(recv_sz == 0)
		{
			return -1;
		}

		string cmd = parseCmd(cmd_buf);
		string arg = parseArg(cmd_buf);
		cout << cmd_buf;
		cout << cmd << "\n";
		cout << arg << "\n";
		//cout << "compare " << cmd.compare("USER") << "\n";
		if(cmd.compare("USER") == 0)
			userHandle(cmd, cmd_buf);
		else if(cmd.compare("PASS") == 0)
			passHandle(cmd, cmd_buf);
		else if(cmd.compare("RETR") == 0)
			retrHandle(cmd, cmd_buf);
		else if(cmd.compare("PUT") == 0)
			putHandle(cmd, cmd_buf);
		else if(cmd.compare("PORT") == 0)
			portHandle(cmd, cmd_buf);
		else
			undefHandle(cmd, cmd_buf);
		//if();
		cout << "\n\n";
	}
	return 0;
}

string Session::parseCmd(char c_b[])
{
	queue<char> cmdq;
	int cmd_l = strlen(c_b);
	for(int i = 0; i < cmd_l; i++)
	{
		if((c_b[i] != ' ') && (c_b[i] != '\r') )
		{
			cmdq.push(c_b[i]);
			//cout << c_b[i] << endl;	
		} 
		else
		{
			break;
		}
	}

	cmd_l = cmdq.size();
	//cout << "cmd size " << cmd_l << "\n"; 
	char cmd[cmd_l+1];
	cmd[cmd_l] = '\0';
	for(int i = 0; i < cmd_l; i++)
	{
		cmd[i] = cmdq.front();
		cmdq.pop();
	}
	string ss(cmd);
	//cout << ss << endl;
	//cout << cmd;
	return ss;
}

string Session::parseArg(char c_b[])
{
	queue<char> cmdq;
	int cmd_l = strlen(c_b);
	int start_of_arg = 0;
	for(int i = 0; i < cmd_l; i++)
	{
		if((c_b[i] == ' ') && ( i + 1 < cmd_l) && (c_b[i+1]) != ' ')
		{
			start_of_arg = i + 1;	
		} 
	}


	for(int i = start_of_arg; i < cmd_l; i++)
	{
		if(c_b[i] != '\r')
		{
			cmdq.push(c_b[i]);
			//cout << c_b[i] << endl;	
		} 
		else
		{
			break;
		}
	}


	cmd_l = cmdq.size();
	//cout << "cmd size " << cmd_l << "\n"; 
	char cmd[cmd_l+1];
	cmd[cmd_l] = '\0';
	for(int i = 0; i < cmd_l; i++)
	{
		cmd[i] = cmdq.front();
		cmdq.pop();
	}
	string ss(cmd);
	//cout << ss << endl;
	//cout << cmd;
	return ss;
}
int Session::userHandle(string c, char c_b[])
{
	cout << "user Handle \n";
	char sucess[] = "331 password required\r\n";
	int send_sz = send(cfd, sucess,strlen(sucess),0);
	return 0;
}
int Session::passHandle(string c, char c_b[])
{
	cout << "pass Handle \n";
	char sucess[] = "230 login sucess\r\n";
	int send_sz = send(cfd, sucess,strlen(sucess),0);
	return 0;
}
int Session::retrHandle(string c, char c_b[])
{
	cout << "retr Handle \n";
	char sucess[] = "150 retr sucess\r\n";
	int send_sz = send(cfd, sucess,strlen(sucess),0);

	char data[] = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
	int send_dsz = send(dfd, data, sizeof(data), 0);
	cout << "data size " << send_dsz << endl;
	return 0;
}
int Session::putHandle(string c, char c_b[])
{
	cout << "put Handle \n";
	return 0;
}
int Session::portHandle(string c, char c_b[])
{
	cout << "port Handle \n";
	string cmd = parseCmd(c_b);
	string arg = parseArg(c_b);
	char pc = ',';
	vector<string> arg_vec = split(arg, &pc);
	for(auto i : arg_vec)
	{
		cout << i << "\n";
	}
	dfd = socket(AF_INET, SOCK_STREAM, 0);
	if(dfd == -1)
	{
		cout << "socket create error in port handle\n";
		return -1;
	}
	
	sai;
	sai.sin_family = AF_INET;
	sai.sin_port = htonl(atoi(arg_vec[4].c_str())*256 + atoi(arg_vec[5].c_str()));
	sai.sin_addr.s_addr = inet_addr((arg_vec[0] + '.' + arg_vec[1] + '.'+ arg_vec[2] + '.'+ arg_vec[3]).c_str());
	int rbd = bind(dfd, (struct sockaddr *)&sai, sizeof(sai));
	if(rbd == -1)
	{
		cout << "bind error in port handle\n";
		return -1;
	}

	if(connect(dfd, (struct sockaddr *) &sai, sizeof(sai)) == -1)
	{
		cout << "error in port handle \n";
		cout << strerror(errno);
		return -1;
	}
	
	
	char sucess[] = "200 port sucess\r\n";
	int send_sz = send(cfd, sucess,strlen(sucess),0);
	return 0;
}
int Session::undefHandle(string c, char c_b[])
{
	cout << "undef Handle \n";
	char sucess[] = "500 login sucess\r\n";
	int send_sz = send(cfd, sucess,strlen(sucess),0);
	return 0;
}
