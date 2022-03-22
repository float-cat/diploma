/*
Need Cross Platform Mode
*/

#ifndef GLOBAL_SOCKET_HPP
#define GLOBAL_SOCKET_HPP

#define POSIX_MODE // to makefile

/*
#ifndef POSIX_MODE
//WINDOWS
#else
//LINUX
#endif
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

#include "../BigInt/biginteger.hpp"

#define SECUREMODE      true
#define UNDEFENDEDMODE false

typedef short type_cell; // to global definition
typedef short* type_cell_p;
typedef long type_double_cell;

class GlobalSocket {
	int sock;
	char * buffer;
	int size;
	static BigInt MyC, MyD, MyN;
	//
	bool securemode;
	BigInt D, N;
	void SecSendData(int command, int length, const void *datablock);
	int SecRecvData(int &command, void *datablock);
 public:
	static void GenerateRSAKeys(void);
	GlobalSocket(int descsock, int sizebuf = 64);
	~GlobalSocket(void);
	int GetSock(void);
	void SendData(int command, int length, const void *datablock);
	int RecvData(int &command, void *datablock);
	void SetOpenKeys(const BigInt &nD, const BigInt &nN);
	static BigInt &GetMyKeyC(void);
	static BigInt &GetMyKeyD(void);
	static BigInt &GetMyKeyN(void);
	BigInt &GetKeyD(void);
	BigInt &GetKeyN(void);
	void SetMode(bool mode);
	bool GetMode(void);
};

#ifndef OBJ_FILE
BigInt GlobalSocket::MyC = BigInt();
BigInt GlobalSocket::MyD = BigInt();
BigInt GlobalSocket::MyN = BigInt();
#endif //OBJ_FILE

#endif
