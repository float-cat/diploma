#ifndef GAMEPROC_CPP
#define GAMEPROC_CPP

#include "gameproc.hpp"

GameProc::GameProc(ClientProtoToClient *cp, Game *mygame) : DataManipulator(cp->MaximumSlots(), mygame) {
	clientproto = cp;
	waitnumber = 0;
}

GameProc::~GameProc(void){
}

int GameProc::MainProcess(void){ // parallel?
	int i,size,playerid, command;
	char databuf[1024]; // poka zdesya
	//1 reaction
	while(true){
		size = clientproto->ReadyList();
		for(i=0; i<size; i++){
			playerid = clientproto->ReadyPlayer(i);
			command = clientproto->Catch(playerid, databuf);
			ProcData(playerid, command, databuf); // valid name?
		}
	}
	//2 generate ?
}

void GameProc::ProcData(int playerid, int cmd, void * data){ //reactions
	switch(cmd){
		case ERR_LOST_CONNECTION:
					clientproto->ReleaseConnection(playerid);
					break;
		case CMD_SECURITY_MODE:	
					clientproto->SetClientMode(playerid, SECUREMODE);
					break;
		case CMD_UNDEFENDED_MODE:
					clientproto->SetClientMode(playerid, UNDEFENDEDMODE);
					break;
		case CMD_NEWKEYS: 	
					SetProtoKeys(playerid, data);
					break;

		case CMD_MENTAL_KEY:
					GenerateKeys(CatchBigInt(data));
					break;
		case CMD_CONFIRM_OF_READY:
					this->OnOtherReadyCheck(playerid);
					break;
		case CMD_LOGCONTROL:
					SetLogPlayerid(playerid);
					break;
		case CMD_DECODECONTROL:
					SetDecodePlayerid(playerid);
					break;
		case CMD_SEND_IDX_MODEL:
					AddModelCard(CatchBigInt(data));
					break;
		case CMD_SEND_IDX_REAL:
					PutCardToLog(CatchBigInt(data));
					break;
		case CMD_SEND_IDX_ONHAND:
					PutCardToHand(CatchBigInt(data));
					break;
		case CMD_ON_HAND_UPDATE:
					this->TokenCards(GetPlayerCardsOnHand(), GetPlayerCountOnHand());
					ClearPlayerOnHand();
					break;
		case CMD_ON_HAND_SECRET:
					this->TokenCards(playerid, *(int*)data);
					break;
		case CMD_ON_HAND_OPEN:
					this->OpenCards(playerid, data);
					break;
		case CMD_MENTAL_BACK:
					MentalAnswer(playerid, data);
					break;
		case CMD_GET_LOG:
					SendLog(playerid);
					break;
		case CMD_END_LOG:	
					ContinueGetCardsFromLog();
					break;
		case CMD_SEND_MSG:	
					this->OnPlayerRecvMessage(playerid, ((char*)data)); //API CB
					break;
		case CMD_OK: 		
					//OK!
					break;
		case CMD_CONNECT:
					MainConnect(playerid, data);
					break;
		case CMD_HELLO:		
					MainHello(playerid, data);
					break;
		case CMD_READY:
					MainReady(playerid, data);
					break;
		case CMD_STEP_YOUR_ID:	
					this->SetAssoc(*(int*)data);
					printf("CMD_STEP_YOUR_ID!\n"); fflush(stdout);
					break;
		case CMD_STEP_I:	
					this->SetAssoc(playerid, *(int*)data);
					break;
		case CMD_STEP_NOW:	
					this->OnPlayerStep(GetPlayer(*(int*)data));
					break;
		case CMD_STEP_FINISH:
					this->OnStepFinish();
					break;
		case CMD_ADDTOPLAYER:
					this->AddToPCards(playerid, data);
					break;
		case CMD_REMFROMPLAYER:
					this->RemFromPCards(playerid, data);
					break;
		case CMD_ADDTOGROUP:
					this->AddToGCards(data);
					break;
		case CMD_REMFROMGROUP:
					this->RemFromGCards(data);
					break;
	}
}

BigInt &GameProc::CatchBigInt(void * data){ // not safe in threads?
	Conv.UnPackFromString((char *)data);
	return Conv;
}

void GameProc::SetProtoKeys(int playerid, void * data){ // need func?
	clientproto->SetKeys(playerid, (char*)data);
}

//public
void GameProc::MainConnect(int playerid, void * data){
	char IP[16]; int len;
	unsigned short PORT; // ??
	strcpy(IP, (const char *)data);
	len = strlen(IP)+1;
	memcpy(&PORT, ((const char *)data)+len, sizeof(unsigned short));
	clientproto->Connect(PORT);
}

void GameProc::MainHello(int playerid, void * data){
	char *buffer = (char *)data;
	/*int virtualid = */AppendNewPlayer(playerid, new Player(buffer, clientproto->SlotIPA(playerid)));
	this->OnPlayerConnected(/*p->VirtualId()*/playerid); //API CB
	// clientproto->Ok(playerid);
}

void GameProc::MainReady(int playerid, void * data){
	unsigned short port;
	int i;
	memcpy(&port, data, sizeof(unsigned short));
	SetPlayerPort(playerid, port);
	for(i=0; i<GetMaxSlot(); i++)
		if(playerid != i && IsPlayerConnected(i))
			clientproto->Connect(playerid, GetPlayerIP(i), GetPlayerPort(i));
}

void GameProc::MentalAnswer(int playerid, void * data){
	int i,number,size;
	BigInt Tmp;
	memcpy(&number, data, sizeof(int));
	//Decode
	if(GetLogPlayerid() != LOCAL_PLAYERID){ //?
		if(IsEncrypted())
			UnencryptLog(); // Unecrypt
	} //?
	//Select number cards
	if(number>GetCountLog()) number = GetCountLog();
	for(i=0; i<number; i++){
		Tmp = GetRandomCardFromLog();
		clientproto->SendIdxOnHand(playerid, Tmp);
	}
	clientproto->OnHandUpdate(playerid);
	// ja kontroliryu log!!!
	if(GetLogPlayerid() != LOCAL_PLAYERID){ //?
		size = clientproto->PlayerList(); // normal ?
		SetLogPlayerid(LOCAL_PLAYERID);
		for(i=0; i<size; i++){
			playerid = clientproto->GetPlayer(i);
			clientproto->LogControl(playerid);
		}
	}
}

void GameProc::SendLog(int playerid){
	BigInt Tmp;
	int i, size = GetCountLog();
	for(i=0; i<size; i++){
		Tmp = GetCardFromLogById(i);
		clientproto->SendIdxReal(playerid, Tmp);
	}
	ClearLog();
	clientproto->EndLog(playerid);
}

void GameProc::ContinueGetCardsFromLog(void){
		BigInt Tmp;
		int dcdplayerid,playerid,i,msize,size;
		//Encrypt & Mess
		if(!IsEncrypted())
			EncryptLog(); //code
		//Decode y menya!!
		dcdplayerid = GetDecodePlayerid();
		SetDecodePlayerid(LOCAL_PLAYERID);
		size = clientproto->PlayerList(); // normal ?
		for(i=0; i<size; i++){
			playerid = clientproto->GetPlayer(i);
			clientproto->DecodeControl(playerid);
		}
		MessLog();
		//Send for selector
		msize = GetCountLog();
		for(i=0; i<msize; i++){
			Tmp = GetCardFromLogById(i);
			clientproto->SendIdxReal(dcdplayerid, Tmp);
		}
		ClearLog();
		//Ask back
		clientproto->MentalBack(dcdplayerid, waitnumber); // transfer across net
		waitnumber = 0;
}

unsigned short GameProc::ClientInPort(void){
	return clientproto->GetInPort();
}

#endif
