#ifndef FORPAWN_CPP
#define FORPAWN_CPP

#include "forpawn.hpp"

ForPawn::ForPawn(ClientProtoToClient *cp, void (*BackDoor)(int, void*)) : ScriptApi(cp, BackDoor){ // Here main prepare
	OnGameProcessStart();
}

ForPawn::~ForPawn(void){ // Destruct processes and objects
	OnGameProcessFinish();
}

int ForPawn::OnGameProcessStart(){
	cout << "call ForPawn::OnGameProcessStart()" << endl;
	OpenDesk();
	InitLog(INIT_LOG_54); // into OnGameInit();
	Init(54);
	strcpy(testtext, "test!");
	return 1;
}

int ForPawn::OnGameProcessFinish(){
	cout << "call ForPawn::OnGameProcessFinish()" << endl;
	return 1;
}

int ForPawn::OnGameStarted(void){
	cout << "call ForPawn::OnGameStated()" << endl;
	fflush(stdout);
	int i;
	InitAssoc();
	score = 0;
	step = 0;
	SetPlayerCardsXY(0, 350, 370);
	SetPlayerCardsXY(1, 350, 20);
	//SetPlayerCardsXY(2, 10, 240);
	//SetPlayerCardsVertical(2, true);
	//SetPlayerCardsXY(3, 650, 240);
	//SetPlayerCardsVertical(3, true);
	/*KeyGetCards = CreateButton(200, 200, 100, 40, "GetCards");
	KeyOpenCards = CreateButton(300, 200, 100, 40, "OpenCards");
	KeyAddScore = CreateButton(200, 240, 100, 40, "AddScore");*/
	KeyStepFinish = CreateButton(300, 240, 100, 40, "Wait!");
	CreateGardsGroup(300, 200, "---");
	//SetCardsGroupVertical(0, true);
	SetCardsGroupControl(0, true);
	SetButtonEnabled(KeyStepFinish, false);
	SetPlayerScore(0);
	if(IsOwner())
		NextStep(0xFF);
	return 1;
}

int ForPawn::OnCtrlButtonClicked(int buttonid){
	cout << "call ForPawn::OnCtrlButtonClicked(" << buttonid << ")" << endl;
	/*if(buttonid == KeyGetCards){
		GetCardsFromLog(6);
		SetButtonText(buttonid, "Good!");
		SetButtonEnabled(buttonid, false);
	}
	else if(buttonid == KeyOpenCards){
		DropButton(KeyGetCards);
		int *testsel;
		int testsize = SizeSelPlayerCards();
		testsel = new int[testsize];
		GetSelPlayerCards(testsel);
		OpenCards(testsel, testsize);
		delete [] testsel;
	}
	else if(buttonid == KeyAddScore){
		score++;
		SetPlayerScore(score);
		int a = CreateGardsGroup(rand()%400, rand()%300, "---");
		SetCardsGroupVertical(a, true);
	}
	else */if(buttonid == KeyStepFinish){
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
	}
	return 1;
}

int ForPawn::OnPlayerConnected(int playerid){
	ScriptApi::OnPlayerConnected(playerid);
	cout << "call ForPawn::OnPlayerConnected(" << playerid << ")" << endl;
	backDoor(API_NEWPLAYER, GetPlayerName(playerid));
	//strcpy(output, GetPlayerName(playerid));
	//strcat(output, " connected!");
	//backDoor(API_NEWCHATLINE, output);
	return 1;
}

int ForPawn::OnPlayerRecvMessage(int playerid, const char *msg){
	ScriptApi::OnPlayerRecvMessage(playerid, msg);
	cout << "call ForPawn::OnPlayerRecvMessage(" << playerid << "," << msg << ")" << endl;
	strcpy(output, GetPlayerName(playerid));
	strcat(output, ": ");
	strcat(output, msg);
	backDoor(API_NEWCHATLINE, output);
	return 1;
}

int ForPawn::OnPlayerSendMessage(const char *msg){
	ScriptApi::OnPlayerSendMessage(msg);
	cout << "call ForPawn::OnPlayerSendMessage(" << msg << ")" << endl;
	strcpy(output, "You: ");
	strcat(output, msg);
	backDoor(API_NEWCHATLINE, output);
	return 1;
}

int ForPawn::OnPlayerCommand(const char *msg){
	ScriptApi::OnPlayerCommand(msg);
	cout << "call ForPawn::OnPlayerCommand(" << msg << ")" << endl;
	//int a = CreateCardGroup();
	//cout << a << endl;
	//DropCardGroup(a);
	return 1;
}

int ForPawn::OnPlayerReadyCheck(void){
	ScriptApi::OnPlayerReadyCheck();
	cout << "call ForPawn::OnPlayerReadyCheck()" << endl;
	return 1;
}

int ForPawn::OnOtherReadyCheck(int playerid){
	ScriptApi::OnOtherReadyCheck(playerid);
	cout << "call ForPawn::OnOtherReadyCheck(" << playerid << ")" << endl;
	return 1;
}

int ForPawn::OnPlayerStep(int playerid){
	ScriptApi::OnPlayerStep(playerid);
	cout << "call ForPawn::OnPlayerStep(" << playerid << ")" << endl;
	cout << "Step: " << step << endl;
	if(playerid == 0xFF){
		SetButtonText(KeyStepFinish, "Step!");
		SetButtonEnabled(KeyStepFinish, true);
	}
	return 1;
}

int ForPawn::OnStepFinish(void){ //child
	ScriptApi::OnStepFinish();
	cout << "call ForPawn::OnStepFinish()" << endl;
	SetButtonText(KeyStepFinish, "Wait!");
	SetButtonEnabled(KeyStepFinish, false);
	return 1;
}

int ForPawn::OnAssociated(void){
	int a;
	ScriptApi::OnAssociated();
	cout << "call ForPawn::OnAssociated()" << endl;
	a = GetAssoc(0xFF) + 1;
	if(a > GetMaxAssocid()) a = 0;
	nextplayer = GetPlayer(a);
	return 1;
}

#endif //FORPAWN_HPP
