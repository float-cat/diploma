#ifndef SCRIPTAPI_CPP
#define SCRIPTAPI_CPP

/*
Needs support returned by pointer for 32bits and 64bits!
Marked as N:PTR
*/

#include "scriptapi.hpp"

ScriptApi::ScriptApi(ClientProtoToClient *cp, void (*BackDoor)(int, void*)) : GameProc(cp, new Game(cp)) {
	/* ... */
	assoc_player = new int[cp->MaximumSlots()+1];
	player_assoc = new int[cp->MaximumSlots()+1];
	maxassocid = 0;
	associated = 0;
	backDoor = BackDoor;
}

ScriptApi::~ScriptApi(void){
	/* ... */
	delete [] assoc_player;
	delete [] player_assoc;
}

void ScriptApi::TokenCards(int *cards, int size){
	void *params[2];
	int playerid, listsize, i;
	params[0] = &size;
	params[1] = cards;
	backDoor(API_ADDCARDSONHAND, params);
	listsize = clientproto->PlayerList(); // normal ?
	for(i=0; i<listsize; i++){
		playerid = clientproto->GetPlayer(i);
		clientproto->OnHandSecret(playerid, size);
		//clientproto->Ok(0);
	}
}

void ScriptApi::TokenCards(int playerid, int size){
	void *params[2];
	params[0] = &playerid;
	params[1] = &size;
	backDoor(API_ADDSECRETCARDSONHAND, params);
}

void ScriptApi::OpenCards(int playerid, void *data){
	void *params[3];
	int size;
	memcpy(&size, data, sizeof(int));
	params[0] = &playerid;
	params[1] = &size;
	params[2] = (int*)data+1;
	backDoor(API_OPENCARDSONHAND, params);
}

void ScriptApi::AddToPCards(int playerid, void *data){
	void *params[3];
	int size;
	int tplayerid, listsize, i;
	memcpy(&size, data, sizeof(int));
	params[0] = &playerid;
	params[1] = &size;
	params[2] = (int*)data+1;
	backDoor(API_ADDTOPLAYERCARDS, params);
	listsize = clientproto->PlayerList(); // normal ?
	for(i=0; i<listsize; i++){
		tplayerid = clientproto->GetPlayer(i);
		clientproto->OnHandSecret(tplayerid, size);
		//clientproto->Ok(0);
	}
}

void ScriptApi::RemFromPCards(int playerid, void *data){
	int size;
	int tplayerid, listsize, i;
	/*memcpy(&size, data, sizeof(int));
	listsize = clientproto->PlayerList(); // normal ?
	for(i=0; i<listsize; i++){
		tplayerid = clientproto->GetPlayer(i);
		clientproto->OnHandSecret(tplayerid, size); // -(size)
		//clientproto->Ok(0);
	}*/
}

void ScriptApi::AddToGCards(void *data){
	void *params[2];
	int size, cgid;
	memcpy(&cgid, data, sizeof(int));
	memcpy(&size, (int*)data+1, sizeof(int));
	params[0] = &size;
	params[1] = (int*)data+2;
	memcpy((int*)data+2+size, &cgid, sizeof(int));
	size++;
	backDoor(API_ADDTOCARDSGROUP, params);
}

void ScriptApi::RemFromGCards(void *data){
	void *params[2];
	int size, cgid;
	memcpy(&cgid, data, sizeof(int));
	memcpy(&size, (int*)data+1, sizeof(int));
	params[0] = &size;
	params[1] = (int*)data+2;
	memcpy((int*)data+2+size, &cgid, sizeof(int));
	size++;
	backDoor(API_REMFROMCARDSGROUP, params);
}

void ScriptApi::OpenCards(int *sel, int size){
	int listsize, playerid, i;
	listsize = clientproto->PlayerList(); // normal ?
	for(i=0; i<listsize; i++){
		playerid = clientproto->GetPlayer(i);
		clientproto->OnHandOpen(playerid, sel, size);
		//clientproto->Ok(0);
	}
	//OnOpenCards
}

void ScriptApi::SetAssoc(int associd){
	printf("SetAssoc(%d)\n", associd); fflush(stdout);
	int listsize, playerid, i;
	if(maxassocid < associd) maxassocid = associd;
	associated++;
	assoc_player[associd] = 0xFF;
	player_assoc[clientproto->MaximumSlots()] = associd;
	listsize = clientproto->PlayerList(); // normal ?
	for(i=1; i<listsize; i++){
		playerid = clientproto->GetPlayer(i);
		clientproto->StepI(playerid, associd);
	}
	if(listsize < associated) this->OnAssociated();
}

void ScriptApi::SetAssoc(int playerid, int associd){
	printf("SetAssoc(%d, %d)\n", playerid, associd); fflush(stdout);
	associated++;
	if(maxassocid < associd) maxassocid = associd;
	assoc_player[associd] = playerid;
	player_assoc[playerid] = associd;
	if(clientproto->PlayerList() < associated) this->OnAssociated(); // clientproto->PlayerList(); O(n)
}

int ScriptApi::GetPlayer(int associd){
	printf("GetPlayer(%d)\n", associd); fflush(stdout);
	return assoc_player[associd];
}

int ScriptApi::GetAssoc(int playerid){
	printf("GetAssoc(%d)\n", playerid); fflush(stdout);
	return player_assoc[(playerid==0xFF)?clientproto->MaximumSlots():playerid];
}

int ScriptApi::GetMaxAssocid(void){
	return maxassocid;
}

//debug
int ScriptApi::Debug(void){
	MentalPoker::Debug();
}

//functions
int ScriptApi::SendMessageToAll(const char * msg){
	int size, playerid, i;
	if(msg == NULL || msg[0] == 0) return 0;
	size = clientproto->PlayerList(); // normal ?
	for(i=0; i<size; i++){
		playerid = clientproto->GetPlayer(i);
		clientproto->SendMsg(playerid, msg);
		//clientproto->Ok(0);
	}
	OnPlayerSendMessage(msg);
	return 1;
}

int ScriptApi::TogglePlayerSecureMode(int playerid, bool mode){
	if(mode) clientproto->SecurityMode(playerid);
	else clientproto->UnDefendedMode(playerid);
	return 1;
}

bool ScriptApi::IsPlayerSecureMode(int playerid){
	return clientproto->GetClientMode(playerid);
}

int ScriptApi::GetCardsFromLog(int number){
	int size, msize, playerid, i, j;
	BigInt Tmp;
	if(GetLogPlayerid()==NONE_PLAYERID){ // this first
		//gen Pk
		BigInt mentalP;
		mentalP.GenerateRandomSimple(TEMP_FBITS);
		mentalP.CheckSimple();
		GenerateKeys(mentalP);
		//pass Pk
		size = clientproto->PlayerList(); // normal ?
		for(i=0; i<size; i++){
			playerid = clientproto->GetPlayer(i);
			clientproto->MentalKey(playerid, mentalP);
		}
		//gen model
		GenerateModelCards();
		SetLogPlayerid(LOCAL_PLAYERID);
		for(i=0; i<size; i++){
			playerid = clientproto->GetPlayer(i);
			clientproto->LogControl(playerid); // ja kontroliryu log
		}
		msize = GetCountModelLog();
		for(i=0; i<size; i++){
			playerid = clientproto->GetPlayer(i);
			for(j=0; j<msize; j++)
				clientproto->SendIdxModel(playerid, GetModelCard(j));
		}
		//set real
		for(i=0; i<msize; i++)
			PutCardToLog(GetModelCard(i));
		//Encrypt & Mess
		EncryptLog(); //code
		//Decode y menya!!
		SetDecodePlayerid(LOCAL_PLAYERID);
		for(i=0; i<size; i++){
			playerid = clientproto->GetPlayer(i);
			clientproto->DecodeControl(playerid);
		}
		MessLog();
		//Send for selector
		playerid = clientproto->GetPlayer(rand()%size);
		msize = GetCountLog();
		for(i=0; i<msize; i++){
			Tmp = GetCardFromLogById(i);
			clientproto->SendIdxReal(playerid, Tmp);
		}
		ClearLog();
		//Ask back
		clientproto->MentalBack(playerid, number);
	}
	else if(GetDecodePlayerid()==LOCAL_PLAYERID){
		//Ask back
		playerid = GetLogPlayerid();
		clientproto->MentalBack(playerid, number);
	}
	else {
		// Take Real
		waitnumber = number;
		if(GetLogPlayerid()!=LOCAL_PLAYERID){
			clientproto->GetLog(GetLogPlayerid());
			size = clientproto->PlayerList(); // normal ?
			SetLogPlayerid(LOCAL_PLAYERID);
			for(i=0; i<size; i++){
				playerid = clientproto->GetPlayer(i);
				clientproto->LogControl(playerid); // ja kontroliryu log
			}
		}
		else ContinueGetCardsFromLog();
		//NextStage();
	}
	//Call back?
	return 1;
}

void ScriptApi::InitAssoc(void){
	int playerid, size, i, associd = 0;
	if(clientproto->IsHostage()){
		size = clientproto->PlayerList(); // normal ?
		assoc_player[0] = 0xFF;
		player_assoc[clientproto->MaximumSlots()] = 0;
		for(i=0; i<size; i++){
			associd++;
			playerid = clientproto->GetPlayer(i);
			assoc_player[associd]=playerid;
			player_assoc[playerid]=associd;
			clientproto->StepI(playerid, 0);
			clientproto->StepYourId(playerid, associd);
		}
		maxassocid = associd;
		this->OnAssociated();
	}
}

void ScriptApi::NextStep(int playerid){
	int size, tplayerid, i; 
	size = clientproto->PlayerList(); // normal ?
	for(i=0; i<size; i++){
		tplayerid = clientproto->GetPlayer(i);
		clientproto->StepNow(tplayerid, GetAssoc(playerid));
	}
	this->OnPlayerStep(playerid);
}

void ScriptApi::FinishStep(void){
	int size, playerid, i; 
	size = clientproto->PlayerList(); // normal ?
	for(i=0; i<size; i++){
		playerid = clientproto->GetPlayer(i);
		clientproto->StepFinish(playerid);
	}
	this->OnStepFinish();
}

bool ScriptApi::IsOwner(void){
	return clientproto->IsHostage();
}

int ScriptApi::CreateButton(int x, int y, int w, int h, char *text){ // N:PTR
	int *t, result;
	t = &result;
	int size;
	char *optr = output;
	size = sizeof(int)*4+sizeof(int*)+strlen(text)+1;
	PUSHVAR(optr, &size, sizeof(int));
	PUSHVAR(optr, &t, sizeof(int*));
	PUSHVAR(optr, &x, sizeof(int));
	PUSHVAR(optr, &y, sizeof(int));
	PUSHVAR(optr, &w, sizeof(int));
	PUSHVAR(optr, &h, sizeof(int));
	PUSHVAR(optr, text, strlen(text)+1);
	//ASSERT(size == p-output);
	backDoor(API_CREATEBUTTON, output);
	return result;
}

void ScriptApi::SetButtonText(int buttonid, char *text){ //D
	int size = sizeof(int)+strlen(text)+1;
	memcpy(output, &size, sizeof(int));
	memcpy(output+sizeof(int), &buttonid, sizeof(int));
	memcpy(output+sizeof(int)*2, text, strlen(text)+1);
	backDoor(API_SETBUTTONTEXT, output);
}

void ScriptApi::SetButtonEnabled(int buttonid, bool mode){
	int size = sizeof(int)+sizeof(bool);
	memcpy(output, &size, sizeof(int));
	memcpy(output+sizeof(int), &buttonid, sizeof(int));
	memcpy(output+sizeof(int)*2, &mode, sizeof(bool));
	backDoor(API_SETBUTTONENABLED, output);
}

void ScriptApi::DropButton(int buttonid){
	int size = sizeof(int);
	memcpy(output, &size, sizeof(int));
	memcpy(output+sizeof(int), &buttonid, sizeof(int));
	backDoor(API_DROPBUTTON, output);
}

int ScriptApi::CreateGardsGroup(int x, int y, char *text){
	int *t, result;
	t = &result;
	int size = sizeof(int)*2+sizeof(int*)+strlen(text)+1;
	memcpy(output, &size, sizeof(int));
	memcpy(output+sizeof(int), &t, sizeof(int)); // Error! why size int* as size int ?
	memcpy(output+sizeof(int)*2, &x, sizeof(int));
	memcpy(output+sizeof(int)*3, &y, sizeof(int));
	memcpy(output+sizeof(int)*4, text, strlen(text)+1);
	backDoor(API_CREATECARDSGROUP, output);
	return result;
}

void ScriptApi::SetCardsGroupText(int cgid, char *text){
	int size = sizeof(int)+strlen(text)+1;
	memcpy(output, &size, sizeof(int));
	memcpy(output+sizeof(int), &cgid, sizeof(int));
	memcpy(output+sizeof(int)*2, text, strlen(text)+1);
	backDoor(API_SETCARDSGROUPTEXT, output);
}

void ScriptApi::SetCardsGroupXY(int cgid, int x, int y){
	int size = sizeof(int)*3;
	memcpy(output, &size, sizeof(int));
	memcpy(output+sizeof(int), &cgid, sizeof(int));
	memcpy(output+sizeof(int), &x, sizeof(int));
	memcpy(output+sizeof(int), &y, sizeof(int));
	backDoor(API_SETCARDSGROUPXY, output);
}

void ScriptApi::SetCardsGroupVertical(int cgid, bool mode){
	int size = sizeof(int)+sizeof(bool);
	memcpy(output, &size, sizeof(int));
	memcpy(output+sizeof(int), &cgid, sizeof(int));
	memcpy(output+sizeof(int)*2, &mode, sizeof(bool));
	backDoor(API_SETCARDSGROUPVERTICAL, output);
}

void ScriptApi::SetCardsGroupControl(int cgid, bool mode){
	int size = sizeof(int)+sizeof(bool);
	memcpy(output, &size, sizeof(int));
	memcpy(output+sizeof(int), &cgid, sizeof(int));
	memcpy(output+sizeof(int)*2, &mode, sizeof(bool));
	backDoor(API_SETCARDSGROUPCONTROL, output);
}

void ScriptApi::SetCardsGroupEnabled(int cgid, bool mode){ // ne tak vse!!!!
	int size = sizeof(int)+sizeof(bool);
	memcpy(output, &size, sizeof(int));
	memcpy(output+sizeof(int), &cgid, sizeof(int));
	memcpy(output+sizeof(int)*2, &mode, sizeof(bool));
	backDoor(API_SETCARDSGROUPENABLED, output);
}

void ScriptApi::DropCardsGroup(int cgid){
	int size = sizeof(int);
	memcpy(output, &size, sizeof(int));
	memcpy(output+sizeof(int), &cgid, sizeof(int));
	backDoor(API_DROPCARDSGROUP, output);
}

void ScriptApi::SetPlayerCardsXY(int playerid, int x, int y){
	int size = 2, pos[2];
	void *params[3];
	pos[0] = x; pos[1] = y;
	params[0] = &playerid;
	params[1] = &size;
	params[2] = pos;
	backDoor(API_SETPLAYERCARDSXY, params);
}

void ScriptApi::SetPlayerCardsVertical(int playerid, bool mode){
	int size = 1, Mode[1];
	void *params[3];
	memcpy(Mode, &mode, sizeof(bool));
	params[0] = &playerid;
	params[1] = &size;
	params[2] = Mode;
	backDoor(API_SETPLAYERCARDSVERTICAL, params);
}

void ScriptApi::SetPlayerCardsControl(int playerid, bool mode){
	int size = 1, Mode[1];
	void *params[3];
	memcpy(Mode, &mode, sizeof(bool));
	params[0] = &playerid;
	params[1] = &size;
	params[2] = Mode;
	backDoor(API_SETPLAYERCARDSCONTROL, params);
}

void ScriptApi::SetPlayerCardsEnabled(int playerid, bool mode){
	int size = 1, Mode[1];
	void *params[3];
	memcpy(Mode, &mode, sizeof(bool));
	params[0] = &playerid;
	params[1] = &size;
	params[2] = Mode;
	backDoor(API_SETPLAYERCARDSENABLED, params);
}

int ScriptApi::SizeSelPlayerCards(void){
	int *t, result;
	t = &result;
	memcpy(output, &t, sizeof(int*));
	backDoor(API_SIZESELPLAYERCARDS, output);
	return result;
}

void ScriptApi::GetSelPlayerCards(int *selcards){ //ptr
	memcpy(output, &selcards, sizeof(int*));
	backDoor(API_GETSELPLAYERCARDS, output);
}

int ScriptApi::SizeAllPlayerCards(void){
	int *t, result;
	t = &result;
	memcpy(output, &t, sizeof(int*));
	backDoor(API_SIZEALLPLAYERCARDS, output);
	return result;
}

void ScriptApi::GetAllPlayerCards(int *selcards){ //ptr
	memcpy(output, &selcards, sizeof(int*));
	backDoor(API_GETALLPLAYERCARDS, output);
}

void ScriptApi::OpenPlayerCards(int *selcards, int size){
	memcpy(output, &size, sizeof(int));
	memcpy(output+sizeof(int), selcards, sizeof(int)*size);
	backDoor(API_OPENPLAYERCARDS, output);	
}

void ScriptApi::AddToPlayerCards(int *selcards, int size){
	int listsize, playerid, i;
	void *params[2];
	/*listsize = clientproto->PlayerList(); // normal ?
	for(i=0; i<listsize; i++){
		playerid = clientproto->GetPlayer(i);
		clientproto->OnHandSecret(playerid, size);
		//clientproto->Ok(0);
	}*/
	params[0] = &size;
	params[1] = selcards;
	backDoor(API_ADDTOPLAYERCARDS, params);
}

void ScriptApi::RemFromPlayerCards(int *selcards, int size){ // MYA!!!!!!!!!!!!!!!!!!
	int listsize, playerid, i;
	void *params[2];
	/*listsize = clientproto->PlayerList(); // normal ?
	for(i=0; i<listsize; i++){
		playerid = clientproto->GetPlayer(i);
		clientproto->OnHandSecret(playerid, -size);
		//clientproto->Ok(0);
	}*/
	params[0] = &size;
	params[1] = selcards;
	backDoor(API_REMFROMPLAYERCARDS, params);
}

int ScriptApi::SizeSelCardsGroup(int cgid){
	int *t, result;
	t = &result;
	memcpy(output, &t, sizeof(int*));
	memcpy(output+sizeof(int*), &cgid, sizeof(int));
	backDoor(API_SIZESELCARDSGROUP, output);
	return *t;
}

void ScriptApi::GetSelCardsGroup(int cgid, int *selcards){
	memcpy(output, &cgid, sizeof(int));
	memcpy(output+sizeof(int), &selcards, sizeof(int*));
	backDoor(API_GETSELCARDSGROUP, output);
}

int ScriptApi::SizeAllCardsGroup(int cgid){
	int *t, result;
	t = &result;
	memcpy(output, &t, sizeof(int*));
	memcpy(output+sizeof(int*), &cgid, sizeof(int));
	backDoor(API_SIZEALLCARDSGROUP, output);
	return *t;
}

void ScriptApi::GetAllCardsGroup(int cgid, int *selcards){
	memcpy(output, &cgid, sizeof(int));
	memcpy(output+sizeof(int), &selcards, sizeof(int*));
	backDoor(API_GETALLCARDSGROUP, output);
}

void ScriptApi::AddToCardsGroup(int cgid, int *selcards, int size){
	int listsize, playerid, i;
	void *params[2];
	listsize = clientproto->PlayerList(); // normal ?
	for(i=0; i<listsize; i++){
		playerid = clientproto->GetPlayer(i);
		clientproto->AddToCardsGroup(playerid, cgid, selcards, size);
		//clientproto->Ok(0);
	}
	memcpy(output, selcards, sizeof(int)*size);
	memcpy(output+(sizeof(int)*size), &cgid, sizeof(int));
	size++;
	params[0] = &size;
	params[1] = output;
	backDoor(API_ADDTOCARDSGROUP, params);
}

void ScriptApi::RemFromCardsGroup(int cgid, int *selcards, int size){
	int listsize, playerid, i;
	void *params[2];
	listsize = clientproto->PlayerList(); // normal ?
	for(i=0; i<listsize; i++){
		playerid = clientproto->GetPlayer(i);
		clientproto->RemFromCardsGroup(playerid, cgid, selcards, size);
		//clientproto->Ok(0);
	}
	memcpy(output, selcards, sizeof(int)*size);
	memcpy(output+sizeof(int)*size, &cgid, sizeof(int));
	size++;
	params[0] = &size;
	params[1] = output;
	backDoor(API_REMFROMCARDSGROUP, params);
}

void ScriptApi::SetPlayerScore(int score){
	int size = sizeof(int);
	memcpy(output, &size, sizeof(int));
	memcpy(output+sizeof(int), &score, sizeof(int));
	backDoor(API_SETPLAYERSCORE, output);
}

//callbacks
int ScriptApi::OnPlayerConnected(int playerid){
	return 1;
}

int ScriptApi::OnPlayerRecvMessage(int playerid, const char *msg){
	return 1;
}

int ScriptApi::OnPlayerSendMessage(const char *msg){
	printf("ScriptApi::OnPlayerSendMessage(%s)\n", msg); fflush(stdout);
	return 1;
}

int ScriptApi::OnPlayerCommand(const char *msg){
	int i,size,playerid;
	if(strcmp(msg, "getcards")==0){
		GetCardsFromLog(3);
	}
	else if(strcmp(msg, "debug")==0){
		Debug();
	}
	else if(strcmp(msg, "ready")==0){
		this->OnPlayerReadyCheck();
	}
	else if(strcmp(msg, "changemode")==0){
		size = clientproto->PlayerList(); // normal ?
		for(i=0; i<size; i++){
			playerid = clientproto->GetPlayer(i); //?
			TogglePlayerSecureMode(playerid, !IsPlayerSecureMode(playerid));
		}
	}
	else {
		SendMessageToAll(msg);
	}
	return 0;
}

int ScriptApi::OnPlayerReadyCheck(void){
	int i,size,playerid;
	size = clientproto->PlayerList(); // normal ?
	for(i=0; i<size; i++){
		playerid = clientproto->GetPlayer(i); //?
		clientproto->ConfirmOfReady(playerid);
	}
	return 0;
}

int ScriptApi::OnOtherReadyCheck(int playerid){
	backDoor(API_READYCHECK, &playerid);
	return 0;
}

int ScriptApi::OnPlayerStep(int playerid){ //child
	return 0;
}

int ScriptApi::OnStepFinish(void){ //child
	return 0;
}

int ScriptApi::OnAssociated(void){
	return 0;
}

#endif //SCRIPTAPI_CPP
