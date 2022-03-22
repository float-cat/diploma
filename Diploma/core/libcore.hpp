#ifndef LIBCORE_HPP
#define LIBCORE_HPP

#ifdef __cplusplus
extern "C" {
#endif
/*
void _init(void);
void _fini(void);
*/
void CoreInit(void (*)(int, void*), void (*)(int, void*));
void CoreStart(int, char *);
void CoreSetPort(int port);
void CoreRelease(void);
unsigned short CoreClientInPort(void);
void CoreSendToChat(const char *msg);
void CoreSetPlayerNick(const char *nick);
void CoreConfirmOfReady(void);
void CoreOpenHandCards(int *sel, int size); // ydalit'!
void CoreStartGame(void);
void CoreCtrlButtonClick(int buttonid);
//
void CoreGetGameList(char *mode);
void CoreRegisterGame(GameData gamedata);
void CoreUnregisterGame(void); //no
//
void CoreGetModeList(void);
void CoreGetMode(char *mode);
//
void CoreRegLog(RegData regdata, int mode);


#ifdef __cplusplus
}
#endif

#endif
