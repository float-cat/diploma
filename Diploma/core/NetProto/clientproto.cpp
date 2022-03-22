#ifndef CLIENTPROTO_CPP
#define CLIENTPROTO_CPP

#include "clientproto.hpp"


ClientProtoToServer::ClientProtoToServer(void (*AskerDoor)(int, void*)) : ClientChannelToServer() {
	askerDoor = AskerDoor;
	fname = NULL;
}

ClientProtoToServer::~ClientProtoToServer(void){
	/**/
}

void ClientProtoToServer::ProcData(int cmd, void *databuf){
	switch(cmd){
		case CMD_GAMEDATA:
			askerDoor(API_GAMELISTITEM, databuf);
			break;
		case CMD_MODEDATA:
			askerDoor(API_MODELISTITEM, databuf);
			break;
		case CMD_MODETRANSFER:
			memcpy(&fsize, databuf, sizeof(int));
			fname = new char[strlen((char*)databuf+sizeof(int))];
			strcpy(fname, (char*)databuf+sizeof(int));
			pf = fopen(fname, "wb");
			break;
		case CMD_MODEPART:
			if(fsize < BUFFER_SIZE) fwrite(databuf, 1, fsize, pf);
			else fwrite(databuf, 1, BUFFER_SIZE, pf);
			break;
		case CMD_MODEFINISH:
			fclose(pf);
			askerDoor(API_MODEDOWNLOAD, NULL);
			delete [] fname;
			fname = NULL;
			break;
		case CMD_REGLOGANSW:
			askerDoor(API_ANSWER, databuf);
			break;
	}
}

void ClientProtoToServer::NewGame(GameData gamedata){ //CMD_NEWGAME
	memcpy(protobuf, &gamedata, sizeof(GameData));
	mysock->SendData(CMD_NEWGAME, sizeof(GameData), protobuf);
}

void ClientProtoToServer::Release(void){ //CMD_RELEASE
	mysock->SendData(CMD_RELEASE, 0, NULL);
}

void ClientProtoToServer::GameList(char *mode){ //CMD_GAMELIST
	mysock->SendData(CMD_GAMELIST, strlen(mode)+1, mode);
}

void ClientProtoToServer::ModeList(void){ //CMD_MODELIST // <Void>
	mysock->SendData(CMD_MODELIST, 0, NULL);
}

void ClientProtoToServer::GetMode(char *mode){ //CMD_GETMODE //NO <Name>
	mysock->SendData(CMD_GETMODE, strlen(mode)+1, mode);
}

void ClientProtoToServer::Register(RegData regdata){
	mysock->SendData(CMD_REGISTER, sizeof(RegData), &regdata);
}

void ClientProtoToServer::Login(RegData regdata){
	mysock->SendData(CMD_LOGIN, sizeof(RegData), &regdata);
}

//

ClientProtoToClient::ClientProtoToClient(void) : ClientChannelToClient() {
	slots = 5;
	strcpy(nick, "none");
	buffer = new char[BUFFER_SIZE];
	readylist = new int[slots];
	readynumber = 0;
	ishostage = true;
	//RSA S
	GlobalSocket::GenerateRSAKeys();
	//RSA F
}


ClientProtoToClient::~ClientProtoToClient(void){
	delete [] buffer;
	delete [] readylist;
}
//

//
int ClientProtoToClient::Connect(int port){
	if(ishostage) ishostage = false;
	int playerid = ClientChannelToClient::Connect(port);
	NewKeys(playerid);
	Hello(playerid, nick, 0, NULL);
	//Ready(playerid);
	return playerid;
}

//

void ClientProtoToClient::SecurityMode(int playerid){
	clients[playerid]->SendData(CMD_SECURITY_MODE, 0, NULL);
	clients[playerid]->SetMode(SECUREMODE);
}

void ClientProtoToClient::UnDefendedMode(int playerid){
	clients[playerid]->SendData(CMD_UNDEFENDED_MODE, 0, NULL);
	clients[playerid]->SetMode(UNDEFENDEDMODE);
}

void ClientProtoToClient::NewKeys(int playerid){ // ofiget ??
	GlobalSocket::GetMyKeyD().PackToString(buffer);
	GlobalSocket::GetMyKeyN().PackToString(buffer+(BigInt::GetCapacityBytes()+sizeof(unsigned int)));
	clients[playerid]->SendData(CMD_NEWKEYS, (BigInt::GetCapacityBytes()+sizeof(unsigned int))*2, buffer);
}

void ClientProtoToClient::MentalKey(int playerid, BigInt &Data){
	Data.PackToString(buffer);
	clients[playerid]->SendData(CMD_MENTAL_KEY, BigInt::GetCapacityBytes()+sizeof(unsigned int), buffer);
}

void ClientProtoToClient::ConfirmOfReady(int playerid){
	clients[playerid]->SendData(CMD_CONFIRM_OF_READY, 0, NULL);
}

void ClientProtoToClient::LogControl(int playerid){
	clients[playerid]->SendData(CMD_LOGCONTROL, 0, NULL);
}

void ClientProtoToClient::DecodeControl(int playerid){
	clients[playerid]->SendData(CMD_DECODECONTROL, 0, NULL);
}

void ClientProtoToClient::SendIdxModel(int playerid, BigInt &Data){
	Data.PackToString(buffer);
	clients[playerid]->SendData(CMD_SEND_IDX_MODEL, BigInt::GetCapacityBytes()+sizeof(unsigned int), buffer);
}

void ClientProtoToClient::SendIdxReal(int playerid, BigInt &Data){
	Data.PackToString(buffer);
	clients[playerid]->SendData(CMD_SEND_IDX_REAL, BigInt::GetCapacityBytes()+sizeof(unsigned int), buffer);
}

void ClientProtoToClient::SendIdxOnHand(int playerid, BigInt &Data){
	Data.PackToString(buffer);
	clients[playerid]->SendData(CMD_SEND_IDX_ONHAND, BigInt::GetCapacityBytes()+sizeof(unsigned int), buffer);
}

void ClientProtoToClient::OnHandUpdate(int playerid){
	clients[playerid]->SendData(CMD_ON_HAND_UPDATE, 0, NULL);
}

void ClientProtoToClient::OnHandSecret(int playerid, int size){
	clients[playerid]->SendData(CMD_ON_HAND_SECRET, sizeof(int), &size);
}

void ClientProtoToClient::OnHandOpen(int playerid, int *data, int size){
	memcpy(buffer, &size, sizeof(int));
	memcpy(buffer+sizeof(int), data, size*sizeof(int));
	clients[playerid]->SendData(CMD_ON_HAND_OPEN, sizeof(int)*(size+1), buffer);
}

void ClientProtoToClient::MentalBack(int playerid, int number){
	memcpy(buffer, &number, sizeof(int));
	clients[playerid]->SendData(CMD_MENTAL_BACK, sizeof(int), buffer);
}

void ClientProtoToClient::GetLog(int playerid){
	clients[playerid]->SendData(CMD_GET_LOG, 0, NULL);
}

void ClientProtoToClient::EndLog(int playerid){
	clients[playerid]->SendData(CMD_END_LOG, 0, NULL);
}

void ClientProtoToClient::PassCardPhys(int playerid, BigInt &Data){
	Data.PackToString(buffer);
	clients[playerid]->SendData(CMD_PASS_CARD_PHYS, BigInt::GetCapacityBytes()+sizeof(unsigned int), buffer);
}

void ClientProtoToClient::PassCardVis(int playerid, int number){
	memcpy(buffer, &number, sizeof(int));
	clients[playerid]->SendData(CMD_PASS_CARD_VIS, sizeof(int), buffer);
}

void ClientProtoToClient::SendMsg(int playerid, const char * msg){
	int len = strlen(msg);
	clients[playerid]->SendData(CMD_SEND_MSG, len+1, msg);
}

void ClientProtoToClient::Connect(int playerid, char * ipa, unsigned short port){
	int len = strlen(ipa)+1;
	strcpy(buffer, ipa);
	memcpy(buffer+len, &port, sizeof(unsigned short));
	len += sizeof(unsigned short);
	clients[playerid]->SendData(CMD_CONNECT, len, buffer);
}

void ClientProtoToClient::Hello(int playerid, char * name, int datasize, char * data){
	int len;
	strcpy(buffer, name);
	len = strlen(buffer)+1;
	memcpy(buffer+len, data, datasize);
	len += datasize;
	clients[playerid]->SendData(CMD_HELLO, len, buffer);
}

void ClientProtoToClient::Ready(int playerid){
	memcpy(buffer, &in_port, sizeof(unsigned short));
	clients[playerid]->SendData(CMD_READY, sizeof(unsigned short), buffer);
}

void ClientProtoToClient::Check(int playerid/*, md5*/){
	//??
}

void ClientProtoToClient::Ok(int playerid){
	clients[playerid]->SendData(CMD_OK, 0, NULL);
}

void ClientProtoToClient::Cancel(int playerid){
	clients[playerid]->SendData(CMD_CANCEL, 0, NULL);
}

void ClientProtoToClient::Error(int playerid, int errcode){
	memcpy(buffer, &errcode, sizeof(int));
	clients[playerid]->SendData(CMD_ERROR, sizeof(int), buffer);

}

void ClientProtoToClient::Noop(int playerid){
	clients[playerid]->SendData(CMD_NOOP, 0, NULL);
}

void ClientProtoToClient::StepYourId(int playerid, int associd){ //CMD_STEP_YOUR_ID
	clients[playerid]->SendData(CMD_STEP_YOUR_ID, sizeof(int), &associd);
}

void ClientProtoToClient::StepI(int playerid, int associd){ //CMD_STEP_I
	clients[playerid]->SendData(CMD_STEP_I, sizeof(int), &associd);
}

void ClientProtoToClient::StepNow(int playerid, int associd){ //CMD_STEP_NOW
	clients[playerid]->SendData(CMD_STEP_NOW, sizeof(int), &associd);
}

void ClientProtoToClient::StepFinish(int playerid){ //CMD_STEP_FINISH
	clients[playerid]->SendData(CMD_STEP_FINISH, 0, NULL);
}

void ClientProtoToClient::AddToPlayerCards(int playerid, int *selcards, int size){ //CMD_ADDTOPLAYER
	memcpy(buffer, &size, sizeof(int));
	memcpy(buffer+sizeof(int), selcards, size*sizeof(int));
	clients[playerid]->SendData(CMD_ADDTOPLAYER, sizeof(int)*(size+1), buffer);
}

void ClientProtoToClient::RemFromPlayerCards(int playerid, int *selcards, int size){ //CMD_REMFROMPLAYER
	memcpy(buffer, &size, sizeof(int));
	memcpy(buffer+sizeof(int), selcards, size*sizeof(int));
	clients[playerid]->SendData(CMD_REMFROMPLAYER, sizeof(int)*(size+1), buffer);
}

void ClientProtoToClient::AddToCardsGroup(int playerid, int cgid, int *selcards, int size){ //CMD_ADDTOGROUP
	memcpy(buffer, &cgid, sizeof(int));
	memcpy(buffer+sizeof(int), &size, sizeof(int));
	memcpy(buffer+sizeof(int)*2, selcards, size*sizeof(int));
	clients[playerid]->SendData(CMD_ADDTOGROUP, sizeof(int)*(size+2), buffer);
}

void ClientProtoToClient::RemFromCardsGroup(int playerid, int cgid, int *selcards, int size){ //CMD_REMFROMGROUP
	memcpy(buffer, &cgid, sizeof(int));
	memcpy(buffer+sizeof(int), &size, sizeof(int));
	memcpy(buffer+sizeof(int)*2, selcards, size*sizeof(int));
	clients[playerid]->SendData(CMD_REMFROMGROUP, sizeof(int)*(size+2), buffer);
}

int ClientProtoToClient::PlayerList(void){
	return AllPlayer(readylist);
}

int ClientProtoToClient::GetPlayer(int idx){ // hz ?
	return readylist[idx];
}

int ClientProtoToClient::ReadyList(void){
	return AskReady(readylist);
}

int ClientProtoToClient::ReadyPlayer(int idx){
	return readylist[idx];
}

int ClientProtoToClient::Catch(int playerid, void * data){
	int result, bytes;
	bytes = clients[playerid]->RecvData(result, data);
	if(bytes < 1) return ERR_LOST_CONNECTION;
	return result;
}

int ClientProtoToClient::SetKeys(int playerid, char * data){
	clients[playerid]->GetKeyD().UnPackFromString(data);
	clients[playerid]->GetKeyN().UnPackFromString(data+(BigInt::GetCapacityBytes()+sizeof(unsigned int)));
	//printf("Keys : D = %s, N = %s\n", clients[playerid]->GetKeyD().Debug().c_str(), clients[playerid]->GetKeyN().Debug());
	//fflush(stdout);
}

int ClientProtoToClient::SetClientMode(int playerid, bool mode){
	clients[playerid]->SetMode(mode);
}

bool ClientProtoToClient::GetClientMode(int playerid){
	return clients[playerid]->GetMode();
}

int ClientProtoToClient::MaximumSlots(void){
	return slots;
}

char *ClientProtoToClient::GetNick(void){
	return nick;
}

void ClientProtoToClient::SetNick(const char *Nick){
	strcpy(nick, Nick);
}

bool ClientProtoToClient::IsHostage(void){
	return ishostage;
}

// cb
void ClientProtoToClient::Connected(int playerid){
	//printf("callback Connected(%d)\n", playerid);
	NewKeys(playerid);
	//SecurityMode(playerid);
	Hello(playerid, nick, 0, NULL);
}

//

int ClientProtoToClient::GetPlayerSock(int playerid){
	return clients[playerid]->GetSock();
}

#endif
