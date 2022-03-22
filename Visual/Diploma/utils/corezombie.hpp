#ifndef COREZOMBIE_HPP
#define COREZOMBIE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <iostream>
#include "apilist.hpp"

using namespace std;

class CoreZombie {
	void *lib_handle;
	void (*CoreInit)(void (*)(int, void*), void (*)(int, void*));
	void (*CoreStart)(int, char*);
	void (*CoreSetPort)(int);
	void (*CoreRelease)(void);
	unsigned short (*CoreClientInPort)(void);
	void (*CoreSendToChat)(const char *);
	void (*CoreSetPlayerNick)(const char *);
	void (*CoreConfirmOfReady)(void);
	void (*CoreOpenHandCards)(int *sel, int size);
	void (*CoreStartGame)(void);
	void (*CoreCtrlButtonClick)(int buttonid);
	//Callbacks for cards changes ?
	void (*CoreGetGameList)(char *mode);
	void (*CoreRegisterGame)(GameData gamedata);
	void (*CoreUnregisterGame)(void);
	void (*CoreGetModeList)(void);
	void (*CoreGetMode)(char *mode);
	void (*CoreRegLog)(RegData regdata, int mode);
 public:
	CoreZombie(void (*)(int, void*), void (*)(int, void*));
	~CoreZombie(void);
	void Init(int mode, char *script = NULL); // params?
	void Port(unsigned short Port);
	unsigned short ClientInPort(void);
	void SendToChat(const char * msg);
	void SetPlayerNick(const char *nick);
	void ConfirmOfReady(void);
	void OpenHandCards(int *sel, int size);
	void StartGame(void);
	void CtrlButtonClick(int buttonid);
	void GetGameList(char *mode);
	void RegisterGame(GameData gamedata);
	void UnregisterGame(void);
	void GetModeList(void);
	void GetMode(char *mode);
	void RegLog(RegData regdata, int mode);
};

extern CoreZombie *core1;

#endif //COREZOMBIE_HPP
