#ifndef COREInterface_CPP
#define COREInterface_CPP

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "coreinterface.hpp"

CoreInterface::CoreInterface(void (*BackDoor)(int, void*), void (*AskerDoor)(int, void*)){
	lib_handle = dlopen("lib/libcore.so", RTLD_LAZY);
	/*if(lib_handle == NULL) {
		cout << "Error!" << endl;
		fflush(stdout);
	}*/
	CoreInit = (void (*)(void (*)(int, void*), void (*)(int, void*)))dlsym(lib_handle, "CoreInit");
	/*if(CoreInit == NULL) {
		cout << "Error!" << endl;
		fflush(stdout);
	}*/
	CoreStart = (void (*)(int, char*))dlsym(lib_handle, "CoreStart");
	CoreSetPort = (void (*)(int))dlsym(lib_handle, "CoreSetPort");
	CoreRelease = (void (*)(void))dlsym(lib_handle, "CoreRelease");
	CoreClientInPort = (unsigned short (*)(void))dlsym(lib_handle, "CoreClientInPort");
	CoreSendToChat = (void (*)(const char *))dlsym(lib_handle, "CoreSendToChat");
	CoreSetPlayerNick = (void (*)(const char *))dlsym(lib_handle, "CoreSetPlayerNick");
	CoreConfirmOfReady = (void (*)(void))dlsym(lib_handle, "CoreConfirmOfReady");
	CoreOpenHandCards = (void (*)(int *, int))dlsym(lib_handle, "CoreOpenHandCards");
	CoreStartGame = (void (*)(void))dlsym(lib_handle, "CoreStartGame");
	CoreCtrlButtonClick = (void (*)(int))dlsym(lib_handle, "CoreCtrlButtonClick");
	CoreGetGameList = (void (*)(char *))dlsym(lib_handle, "CoreGetGameList");
	CoreRegisterGame = (void (*)(GameData))dlsym(lib_handle, "CoreRegisterGame");
	CoreUnregisterGame = (void (*)(void))dlsym(lib_handle, "CoreUnregisterGame");
	CoreGetModeList = (void (*)(void))dlsym(lib_handle, "CoreGetModeList");
	CoreGetMode = (void (*)(char *))dlsym(lib_handle, "CoreGetMode");
	CoreRegLog = (void (*)(RegData, int))dlsym(lib_handle, "CoreRegLog");
	(*CoreInit)(BackDoor, AskerDoor);
}

CoreInterface::~CoreInterface(void){
	(*CoreRelease)();
	dlclose(lib_handle);
}

void CoreInterface::Init(int mode, char *script){ // params?
	(*CoreStart)(mode, script);
}

void CoreInterface::Port(unsigned short Port){
	(*CoreSetPort)(Port);
}

unsigned short CoreInterface::ClientInPort(void){
	return (*CoreClientInPort)();
}

void CoreInterface::SendToChat(const char * msg){
	return (*CoreSendToChat)(msg);
}

void CoreInterface::SetPlayerNick(const char *nick){
	(*CoreSetPlayerNick)(nick);
}

void CoreInterface::ConfirmOfReady(void){
	(*CoreConfirmOfReady)();
}

void CoreInterface::OpenHandCards(int *cards, int size){
	(*CoreOpenHandCards)(cards, size);
}

void CoreInterface::StartGame(void){
	(*CoreStartGame)();
}

void CoreInterface::CtrlButtonClick(int buttonid){
	(*CoreCtrlButtonClick)(buttonid);
}

void CoreInterface::GetGameList(char *mode){
	(*CoreGetGameList)(mode);
}

void CoreInterface::RegisterGame(GameData gamedata){
	(*CoreRegisterGame)(gamedata);
}

void CoreInterface::UnregisterGame(void){
	(*CoreUnregisterGame)();
}

void CoreInterface::GetModeList(void){
	printf("(1)\n");
	fflush(stdout);
	(*CoreGetModeList)();
}

void CoreInterface::GetMode(char *mode){
	(*CoreGetMode)(mode);
}

void CoreInterface::RegLog(RegData regdata, int mode){
	(*CoreRegLog)(regdata, mode);
}

#endif //COREInterface_CPP
