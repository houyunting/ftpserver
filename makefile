ftpserver: ftpServer.cpp ftpSession.cpp ftpSession.h
	g++ -std=c++11 -o ftpServer ftpServer.cpp ftpSession.cpp
