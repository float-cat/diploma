#ifndef FORPAWN_CPP
#define FORPAWN_CPP

#include "forpawn.hpp"

ForPawn *ForPawn::pScript = NULL;
char *ForPawn::strbuffer = NULL;

ForPawn::ForPawn(ClientProtoToClient *cp, void (*BackDoor)(int, void*), char *script) : ScriptApi(cp, BackDoor){ // Here main prepare
	int err;
	pScript = this;
	strbuffer = new char[128];
	AMX_NATIVE_INFO bstring_Natives[] = {
		{ "CreateButton", n_CreateButton },
		{ "DebugFunc", n_DebugFunc },
		{ NULL, NULL }
	};
	cell ret = 0;
	strcpy(strbuffer, "modes/");
	strcat(strbuffer, script);
	strcat(strbuffer, ".amx");
	err = aux_LoadProgram(&amx, strbuffer, NULL);
	err = amx_Register(&amx, bstring_Natives, -1);
	/*err = amx_Exec(&amx, &ret, AMX_EXEC_MAIN);
	while (err == AMX_ERR_SLEEP)
		err = amx_Exec(&amx, &ret, AMX_EXEC_CONT);*/
	OnGameProcessStart();
}

ForPawn::~ForPawn(void){ // Destruct processes and objects
	OnGameProcessFinish();
	aux_FreeProgram(&amx);
	delete [] strbuffer;
}

cell AMX_NATIVE_CALL ForPawn::n_CreateButton(AMX* amx, const cell* params){
	int result;
	int err = amx_GetString(strbuffer, (cell*)params[5], 0, 128);
	result = pScript->CreateButton(params[1], params[2], params[3], params[4], strbuffer);
	return result;
}

cell AMX_NATIVE_CALL ForPawn::n_DebugFunc(AMX* amx, const cell* params){
	printf("DebugFunc()\n");
	fflush(stdout);
	return 1;
}

int ForPawn::OnGameProcessStart(){
	printf("call ForPawn::OnGameProcessStart()\n"); fflush(stdout);
	OpenDesk();
	InitLog(INIT_LOG_54); // into OnGameInit();
	Init(54);
	return 1;
}

int ForPawn::OnGameProcessFinish(){
	printf("call ForPawn::OnGameProcessFinish()\n"); fflush(stdout);
	return 1;
}

int ForPawn::OnGameStarted(void){
	printf("call ForPawn::OnGameStarted()\n"); fflush(stdout);
	int a; cell b;
	amx_FindPublic(&amx, "OnGameStarted", &a);
	amx_Exec(&amx, &b, a);
	return b;
}

int ForPawn::OnCtrlButtonClicked(int buttonid){
	printf("call ForPawn::OnCtrlButtonClicked(%d)\n", buttonid); fflush(stdout);
	/*if(buttonid == KeyStepFinish){
		if(step == 0){
			GetCardsFromLog(12);
		}
		else if(step == 1) {
			int *testsel;
			int testsize = SizeSelPlayerCards();
			testsel = new int[testsize];
			GetSelPlayerCards(testsel);
			RemFromPlayerCards(testsel, testsize);
			AddToCardsGroup(0, testsel, testsize);
			delete [] testsel;
		}
		else {
			int *testsel;
			int testsize = SizeSelCardsGroup(0);
			testsel = new int[testsize];
			GetSelCardsGroup(0, testsel);
			RemFromCardsGroup(0, testsel, testsize);
			AddToPlayerCards(testsel, testsize);
			delete [] testsel;
		}
		FinishStep();
		NextStep(nextplayer);
		step++;
	}*/
	return 1;
}

int ForPawn::OnPlayerConnected(int playerid){
	ScriptApi::OnPlayerConnected(playerid);
	printf("call ForPawn::OnPlayerConnected(%d)\n", playerid); fflush(stdout);
	backDoor(API_NEWPLAYER, GetPlayerName(playerid)); //v ScriptApi
	/*strcpy(output, GetPlayerName(playerid));
	strcat(output, " connected!");
	backDoor(API_NEWCHATLINE, output);*/
	return 1;
}

int ForPawn::OnPlayerRecvMessage(int playerid, const char *msg){
	ScriptApi::OnPlayerRecvMessage(playerid, msg);
	printf("call ForPawn::OnPlayerRecvMessage(%d,%s)\n", playerid, msg); fflush(stdout);
	strcpy(output, GetPlayerName(playerid));
	strcat(output, ": ");
	strcat(output, msg);
	backDoor(API_NEWCHATLINE, output); //v ScriptApi
	return 1;
}

int ForPawn::OnPlayerSendMessage(const char *msg){
	ScriptApi::OnPlayerSendMessage(msg);
	printf("call ForPawn::OnPlayerSendMessage(%s)\n", msg); fflush(stdout);
	strcpy(output, "You: ");
	strcat(output, msg);
	backDoor(API_NEWCHATLINE, output); //V ScriptApi
	return 1;
}

int ForPawn::OnPlayerCommand(const char *msg){
	ScriptApi::OnPlayerCommand(msg);
	printf("call ForPawn::OnPlayerCommand(%s)\n", msg); fflush(stdout);
	//int a = CreateCardGroup();
	//cout << a << endl;
	//DropCardGroup(a);
	return 1;
}

int ForPawn::OnPlayerReadyCheck(void){
	ScriptApi::OnPlayerReadyCheck();
	printf("call ForPawn::OnPlayerReadyCheck()\n"); fflush(stdout);
	return 1;
}

int ForPawn::OnOtherReadyCheck(int playerid){
	ScriptApi::OnOtherReadyCheck(playerid);
	printf("call ForPawn::OnOtherReadyCheck(%d)\n", playerid); fflush(stdout);
	return 1;
}

int ForPawn::OnPlayerStep(int playerid){
	ScriptApi::OnPlayerStep(playerid);
	printf("call ForPawn::OnPlayerStep(%d)\n", playerid); fflush(stdout);
	/*cout << "Step: " << step << endl;
	if(playerid == 0xFF){
		SetButtonText(KeyStepFinish, "Step!");
		SetButtonEnabled(KeyStepFinish, true);
	}*/
	return 1;
}

int ForPawn::OnStepFinish(void){ //child
	ScriptApi::OnStepFinish();
	printf("call ForPawn::OnStepFinish()\n"); fflush(stdout);
	/*SetButtonText(KeyStepFinish, "Wait!");
	SetButtonEnabled(KeyStepFinish, false);*/
	return 1;
}

int ForPawn::OnAssociated(void){
	/*int a;
	ScriptApi::OnAssociated();
	printf("call ForPawn::OnAssociated()" << endl;
	a = GetAssoc(0xFF) + 1;
	if(a > GetMaxAssocid()) a = 0;
	nextplayer = GetPlayer(a);*/
	return 1;
}

#endif //FORPAWN_HPP
