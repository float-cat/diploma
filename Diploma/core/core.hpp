#ifndef CORE_HPP
#define CORE_HPP

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "GameProcess/forpawn.hpp"
#include <semaphore.h>

#include "libcore.hpp"

class Core {
	void (*backDoor)(int, void*);
	void (*askerDoor)(int, void*);
	int port;
	char *playernick;
	ClientProtoToClient *ClientConnection;
	ClientProtoToServer *ServerConnection;
	ForPawn *GameApi;
	sem_t starter;
	static void * ClientProcess(void * params);
	static void * ServerProcess(void * params);
	static void * ApiProcess(void * params);
 public:
	Core(void (*BackDoor)(int, void*), void (*AskerDoor)(int, void*));
	~Core(void);
	void Init(int mode, char *script); // params?
	void Port(unsigned short Port);
	unsigned short ClientInPort(void);
	void SendToChat(const char *msg);
	void SetPlayerNick(const char *nick);
	void ConfirmOfReady(void);
	void OpenHandCards(int *sel, int size); //not need!
	void StartGame(void);
	void CtrlButtonClick(int buttonid);
	void GetGameList(char *mode);
	void RegisterGame(GameData gamedata);
	void UnregisterGame(void);
	void GetModeList(void);
	void GetMode(char *mode);
	void RegLog(RegData regdata, int mode);
};

Core *coreptr = NULL;

#endif //CORE_HPP
