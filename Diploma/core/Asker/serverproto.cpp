#ifndef SERVERPROTO_CPP
#define SERVERPROTO_CPP

#include "serverproto.hpp"

ServerProto::ServerProto(int port, int slotlimit) : ServerChannel(port, slotlimit){
	FILE *pf; int i;
	char readbuf[128], *second;
	ModeDataItem *p;
	root = NULL;
	modes = NULL;
	//
	pf = fopen("modes/modelist", "rt"); // v class?
	readbuf[0]=0;
	while(!feof(pf)){
		fgets(readbuf, 128, pf);
		printf("[%d]", strlen(readbuf));
		if(strlen(readbuf)>0) readbuf[strlen(readbuf)-1] = 0; // 1 in Windows?
		if(strlen(readbuf)==0) break;
		for(i=0; i<strlen(readbuf); i++)
			if(readbuf[i] == '='){
				readbuf[i]=0;
				second = &readbuf[i+1];
			}
		p = modes;
		modes = new ModeDataItem;
		strcpy(modes->data.fname, readbuf);
		strcpy(modes->data.title, second);
		modes->next = p;
		readbuf[0] = 0;
	}
	fclose(pf);
}

ServerProto::~ServerProto(void){
}

void ServerProto::ProcData(int clientid, int cmd, void *data){
	/*MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL *connection, mysql;*/
	int state;
	char sqlcmd[256];
	GameDataItem *p;
	ModeDataItem *m;
	RegData *rg;
	char *fname, *mode;
	FILE *pf;
	int fsize, bytes;
	cout << "Get cmd = " << cmd << endl;
	switch(cmd){
		case CMD_NEWGAME:
			p = root;
			root = new GameDataItem;
			memcpy(&root->data, data, sizeof(GameData));
			cout << "new game: " << root->data.title << endl;
			root->idx = clientid;
			root->next = p;
			break;
		case CMD_GAMELIST:
			mode = (char*)data;
			p = root;
			while(p!=NULL){
				if(strcmp(p->data.mode, mode)==0)
					GameInfo(clientid, p->data);
				p = p->next;
			}
			break;
		case CMD_MODELIST:
			m = modes;
			while(m!=NULL){
				cout << m->data.title << endl;
				fflush(stdout);
				ModeInfo(clientid, m->data);
				m = m->next;
			}
			break;
		case CMD_GETMODE: // v otdelnyu nitky?
			mode = (char*)data;
			fname = new char[64];
			sprintf(fname, "modes/%s.amx",mode);
			pf = fopen(fname, "rb");
			fseek(pf, 0, SEEK_END);
			fsize = ftell(pf);
			fseek(pf, 0, SEEK_SET);
			ModeTransfer(clientid, fsize, fname);
			while((bytes = fread(output, 1, BUFFER_SIZE, pf))>0)
				ModePart(clientid, bytes, output);
			ModeFinish(clientid);
			delete [] fname;
			break;
		/*case CMD_REGISTER: //mysql support!
			rg = (RegData*)data;
			cout << rg->nick << endl;
			strcpy(sqlcmd, "INSERT INTO Users (cnick, firstname, secname, chashcode) VALUES ('");
			strcat(sqlcmd, rg->nick);
			strcat(sqlcmd, "', '");
			strcat(sqlcmd, rg->fname);
			strcat(sqlcmd, "', '");
			strcat(sqlcmd, rg->sname);
			strcat(sqlcmd, "', '");
			strcat(sqlcmd, rg->hash);
			strcat(sqlcmd, "')");
			cout << sqlcmd << endl;
			mysql_init(&mysql);
			connection = mysql_real_connect(&mysql, "localhost", "root", "rb,jhub", "GamePlatform", 0, 0, 0);
			if(connection == NULL) cout << "Error!" << endl;
			state = mysql_query(connection, sqlcmd);
			mysql_close(connection);
			AnswerRegLog(clientid, REG_OK);
			break;
		case CMD_LOGIN:
			rg = (RegData*)data;
			cout << rg->nick << endl;
			strcpy(sqlcmd, "SELECT chashcode FROM Users WHERE cnick = '");
			strcat(sqlcmd, rg->nick);
			strcat(sqlcmd, "'");
			mysql_init(&mysql);
			connection = mysql_real_connect(&mysql, "localhost", "root", "rb,jhub", "GamePlatform", 0, 0, 0);
			state = mysql_query(connection, sqlcmd);
			result = mysql_store_result(connection);
			if((row = mysql_fetch_row(result)) != NULL)
			{
				if(strcmp(row[0], rg->hash)==0)
					AnswerRegLog(clientid, LOG_OK);
			}
			mysql_free_result(result);
			mysql_close(connection);
			//AnswerRegLog(clientid, LOG_FAIL);
			break;*/
	}
}

void ServerProto::GameInfo(int clientid, GameData gamedata){
	clients[clientid]->SendData(CMD_GAMEDATA, sizeof(GameData), &gamedata);
}

void ServerProto::ModeInfo(int clientid, ModeData modedata){
	clients[clientid]->SendData(CMD_MODEDATA, sizeof(ModeData), &modedata);
}

void ServerProto::ModeTransfer(int clientid, int fsize, char *fname){
	memcpy(output, &fsize, sizeof(int));
	memcpy(output+sizeof(int), fname, strlen(fname)+1);
	clients[clientid]->SendData(CMD_MODETRANSFER, sizeof(int)+strlen(fname)+1, output);
}

void ServerProto::ModePart(int clientid, int dsize, char *data){
	clients[clientid]->SendData(CMD_MODEPART, dsize, data);
}

void ServerProto::ModeFinish(int clientid){
	clients[clientid]->SendData(CMD_MODEFINISH, 0, NULL);
}

void ServerProto::AnswerRegLog(int clientid, int status){
	clients[clientid]->SendData(CMD_REGLOGANSW, sizeof(int), &status);
}

#endif
