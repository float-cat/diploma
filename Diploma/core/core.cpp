#ifndef CORE_CPP
#define CORE_CPP

#include "core.hpp"

void * Core::ClientProcess(void * params){
	Core *core = (Core*)params;
	if(core->port > 0){
		int a = core->ClientConnection->Connect(core->port);
		core->ClientConnection->Ready(a);
	}
	sem_post(&(core->starter));
	core->ClientConnection->MainProcess();
	return NULL;
}

void * Core::ServerProcess(void * params){
	Core *core = (Core*)params;
	core->ServerConnection->MainProcess();
	return NULL;
}

void * Core::ApiProcess(void * params){
	Core *core = (Core*)params;
	sem_post(&(core->starter));
	core->GameApi->MainProcess();
	return NULL;
}

Core::Core(void (*BackDoor)(int, void*), void (*AskerDoor)(int, void*)){
	port = 0;
	playernick = NULL;
	BigInt::InitClass();
	askerDoor = AskerDoor;
	backDoor = BackDoor;
	ServerConnection = NULL;
	ClientConnection = NULL;
	GameApi = NULL;
}

Core::~Core(void){
	if(ServerConnection!=NULL) delete ServerConnection;
	if(GameApi!=NULL) delete GameApi;
	if(ClientConnection!=NULL) delete ClientConnection;
	if(playernick!=NULL) delete [] playernick;
}

void Core::Init(int mode, char *script){ // params?
	if(mode == INIT_GAMEPROC){
		ClientConnection = new ClientProtoToClient;
		if(playernick!=NULL)
			ClientConnection->SetNick(playernick);
		GameApi = new ForPawn(ClientConnection, backDoor, script);
		pthread_t pclientproc;
		pthread_t pgameproces;
		sem_init(&starter, 0, 0);
		pthread_create(&pgameproces, 0, ApiProcess, this);
		sem_wait(&starter);
		pthread_create(&pclientproc, 0, ClientProcess, this);
	}
	else if(mode == INIT_ASKER){
		ServerConnection = new ClientProtoToServer(askerDoor);
		pthread_t paskerproc;
		pthread_create(&paskerproc, 0, ServerProcess, this);
	}
}

void Core::Port(unsigned short Port){
	port = Port;
}

unsigned short Core::ClientInPort(void){
	return GameApi->ClientInPort();
}


void Core::SendToChat(const char *msg){
	GameApi->OnPlayerCommand(msg);
}

void Core::ConfirmOfReady(void){
	GameApi->OnPlayerReadyCheck();
}

void Core::SetPlayerNick(const char *nick){
	if(playernick!=NULL) delete [] playernick;
	playernick = new char[strlen(nick)+1];
	strcpy(playernick, nick);
}

void Core::OpenHandCards(int *sel, int size){
	GameApi->OpenCards(sel, size);
}

void Core::StartGame(void){
	GameApi->OnGameStarted();
}

void Core::CtrlButtonClick(int buttonid){
	GameApi->OnCtrlButtonClicked(buttonid);
}

void Core::GetGameList(char *mode){
	ServerConnection->GameList(mode);
}

void Core::RegisterGame(GameData gamedata){
	ServerConnection->NewGame(gamedata);
}

void Core::UnregisterGame(void){
	ServerConnection->Release();
}

void Core::GetModeList(void){
	ServerConnection->ModeList();
}

void Core::GetMode(char *mode){
	ServerConnection->GetMode(mode);
}

void Core::RegLog(RegData regdata, int mode){
	if(mode==1) ServerConnection->Register(regdata);
	else ServerConnection->Login(regdata);
}

//void _init(){
	/* PRINT START */
	//printf("_init()\n");
	//fflush(stdout);
	/* PRINT  END  */
//}


//void _fini(){
	/* PRINT START */
	//printf("_fini()\n");
	//fflush(stdout);
	/* PRINT  END  */
//}

void CoreInit(void (*BackDoor)(int, void*), void (*AskerDoor)(int, void*)){
	if(coreptr==NULL)
		coreptr = new Core(BackDoor, AskerDoor);
}

void CoreStart(int mode, char *script){
	coreptr->Init(mode, script);
}

void CoreSetPort(int port){
	coreptr->Port(port);
}

void CoreRelease(void){
	delete coreptr;
	coreptr = NULL;
}

unsigned short CoreClientInPort(void){
	return coreptr->ClientInPort();
}

void CoreSendToChat(const char * msg){
	coreptr->SendToChat(msg);
}

void CoreSetPlayerNick(const char * nick){
	coreptr->SetPlayerNick(nick);
}

void CoreConfirmOfReady(void){
	coreptr->ConfirmOfReady();
}

void CoreOpenHandCards(int *sel, int size){
	coreptr->OpenHandCards(sel, size);
}

void CoreStartGame(void){
	coreptr->StartGame();
}

void CoreCtrlButtonClick(int buttonid){
	coreptr->CtrlButtonClick(buttonid);
}

void CoreGetGameList(char *mode){
	coreptr->GetGameList(mode);
}

void CoreRegisterGame(GameData gamedata){
	coreptr->RegisterGame(gamedata);
}

void CoreUnregisterGame(void){
	coreptr->UnregisterGame();
}

void CoreGetModeList(void){
	coreptr->GetModeList();
}

void CoreGetMode(char *mode){
	coreptr->GetMode(mode);
}

void CoreRegLog(RegData regdata, int mode){
	coreptr->RegLog(regdata, mode);
}

#endif //CORE_CPP
