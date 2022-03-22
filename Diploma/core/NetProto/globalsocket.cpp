#ifndef GLOBAL_SOCKET_CPP
#define GLOBAL_SOCKET_CPP

#include "globalsocket.hpp"

/*	int sock;
	char * buffer;
	int size;
 public:*/

#define TEMP_FBITS 16

void GlobalSocket::GenerateRSAKeys(void){
	BigInt P, Q, Fi, One(1);
	P.GenerateRandomSimple(TEMP_FBITS);
	Q.GenerateRandomSimple(TEMP_FBITS);
	MyN = P.Mul(Q);
	P = P.Sub(One);
	Q = Q.Sub(One);
	Fi = P.Mul(Q);
	do {
		MyD.GenerateRandomNumber(TEMP_FBITS);
	} while(Fi.Compare(MyD) < 1 || Fi.GCD(MyD).Compare(One) != 0);
	MyC = Fi.Euclid(MyD);
}

GlobalSocket::GlobalSocket(int descsock, int sizebuf){
	securemode = false;
	sock = descsock;
	size = sizebuf;
	//buffer = new char[size];
	buffer = new char[BigInt::GetCapacityBytes()+1];
}

GlobalSocket::~GlobalSocket(void){
	close(sock); // cross?
	delete [] buffer;	
}

int GlobalSocket::GetSock(void){
	return sock;
}

void GlobalSocket::SendData(int command, int length, const void *datablock){
	if(securemode) {
		SecSendData(command, length, datablock);
		return;
	}
	int header[2];
	//if read?
	header[0] = command;
	header[1] = length;
	send(sock, header, sizeof(int)*2, 0); // zero?
	send(sock, datablock, length, 0);
}

int GlobalSocket::RecvData(int &command, void *datablock){
	if(securemode) return SecRecvData(command, datablock);	
	int header[2], bytes;
	//if read?
	bytes = recv(sock, header, sizeof(int)*2, MSG_WAITALL);
	if(bytes < 1) return bytes;
	command = header[0];
	if(header[1] == 0) return bytes;
	return recv(sock, datablock, header[1], MSG_WAITALL) + sizeof(int)*2;
}

void GlobalSocket::SecSendData(int command, int length, const void *datablock){
	BigInt Tmp;
	char * databuf;
	int idx;
	Tmp = command;
	Tmp = Tmp.PowerAndMod(D, N);
	Tmp.PackToString(buffer); // return size
	send(sock, buffer, BigInt::GetCapacityBytes()+sizeof(unsigned int), 0); // over need ?
	Tmp = length;
	Tmp = Tmp.PowerAndMod(D, N);
	Tmp.PackToString(buffer); // return size
	send(sock, buffer, BigInt::GetCapacityBytes()+sizeof(unsigned int), 0); // over need ?
	if(length == 0) return;
	// code msg & send
	databuf = new char[length];
	memcpy(databuf, datablock, length);
	idx = 0;
	while(idx<length){
		Tmp.ConvertDataToBigInt(databuf, idx, length, &N);
		Tmp = Tmp.PowerAndMod(D, N);
		Tmp.PackToString(buffer); // return size
		send(sock, buffer, BigInt::GetCapacityBytes()+sizeof(unsigned int), 0); // over need ?
	}
	delete [] databuf;
}

int GlobalSocket::SecRecvData(int &command, void *datablock){
	BigInt Tmp;
	int length;
	char * databuf;
	int idx;
	recv(sock, buffer, BigInt::GetCapacityBytes()+sizeof(unsigned int), MSG_WAITALL); // over need ?
	Tmp.UnPackFromString(buffer); // where size ?
	Tmp = Tmp.PowerAndMod(MyC, MyN);
	command = Tmp.ToInt();
	recv(sock, buffer, BigInt::GetCapacityBytes()+sizeof(unsigned int), MSG_WAITALL); // over need ?
	Tmp.UnPackFromString(buffer); // where size ?
	Tmp = Tmp.PowerAndMod(MyC, MyN);
	length = Tmp.ToInt();
	if(length == 0) return sizeof(int)*2;
	// recv msg & decode
	databuf = new char[length];
	idx = 0;
	while(idx<length){
		recv(sock, buffer, BigInt::GetCapacityBytes()+sizeof(unsigned int), MSG_WAITALL); // over need ?
		Tmp.UnPackFromString(buffer); // return size
		Tmp = Tmp.PowerAndMod(MyC, MyN);
		Tmp.ConvertBigIntToData(databuf, idx, length);
	}
	memcpy(datablock, databuf, length);
	delete [] databuf;
	return idx + sizeof(int)*2;
}

void GlobalSocket::SetOpenKeys(const BigInt &nD, const BigInt &nN){
	D = nD;
	N = nN;
}

BigInt &GlobalSocket::GetMyKeyC(void){
	return MyC;
}

BigInt &GlobalSocket::GetMyKeyD(void){
	return MyD;
}

BigInt &GlobalSocket::GetMyKeyN(void){
	return MyN;
}

BigInt &GlobalSocket::GetKeyD(void){
	return D;
}

BigInt &GlobalSocket::GetKeyN(void){
	return N;
}

void GlobalSocket::SetMode(bool mode){
	securemode = mode;
}

bool GlobalSocket::GetMode(void){
	return securemode;
}

#endif
