#include "ftpSession.h"
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<queue>


using namespace std;



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

		int recv_sz = recv(cfd, cmd_buf, 1024, 0);
		if(recv_sz == 0)
		{
			return -1;
		}

		string cmd = parseCmd(cmd_buf);
		cout << cmd << "\n";
		//if();
	}
	return 0;
}

string Session::parseCmd(char c_b[])
{
	queue<char> cmdq;
	int cmd_l = strlen(c_b);
	for(int i = 0; i < cmd_l - 1; i++)
	{
		if(c_b[i] != ' ')
		{
			cmdq.push(c_b[i]);	
		} 
		else
		{
			break;
		}
	}

	cmd_l = cmdq.size();
	char cmd[cmd_l + 1];
	cmd[cmd_l] = '\n';
	for(int i = 0; i < cmd_l; i++)
	{
		cmd[i] = cmdq.front();
		cmdq.pop();
	}
	string ss = cmd;
	return ss;
}
