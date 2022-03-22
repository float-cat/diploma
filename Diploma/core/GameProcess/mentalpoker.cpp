#ifndef MENTALPOKER_CPP
#define MENTALPOKER_CPP

#include "mentalpoker.hpp"

void MentalPoker::AddToMass(BigInt **Array, BigInt &card, int &size){
	if(size >= logsize) return; // it error!
	Array[size++] = new BigInt(card);
}

void MentalPoker::RemFromMass(BigInt **Array, int idx, int &size){
	if(idx>=logsize || Array[idx]==NULL) return; // it error!
	size--;
	if(size > 0 && size != idx) *Array[idx] = *Array[size];
	delete Array[size];
	Array[size] = NULL;
}

void MentalPoker::EncryptMass(BigInt **Array, int size){
	int i;
	for(i=0; i<size; i++)
		*Array[i] = Array[i]->PowerAndMod(Ck, Pk);
	isencrypted = true;
}

void MentalPoker::UnencryptMass(BigInt **Array, int size){
	int i;
	for(i=0; i<size; i++)
		*Array[i] = Array[i]->PowerAndMod(Dk, Pk);
	isencrypted = false;
}

void MentalPoker::MessMass(BigInt **Array, int size){
        int i,n1,n2;
	BigInt *Tmp;
        for(i=0;i<size;i++){
                n1 = rand()%size;
                n2 = rand()%size;
                Tmp = Array[n1];
                Array[n1] = Array[n2];
                Array[n2] = Tmp;
        }
}

void MentalPoker::ClearMass(BigInt **Array, int &size){
	int i;
	size = 0;
	for(i=0; i<logsize; i++)
		if(Array[i] != NULL){
			delete Array[i];
			Array[i] = NULL;
		}
}

int MentalPoker::SearchInMass(BigInt **Array, BigInt &card, int size){
	int i;
	for(i=0; i<size; i++)
		if(Array[i]->Compare(card)==0)
			return i;
	return -1;
}

MentalPoker::MentalPoker(int Logsize){
	int i;
	isencrypted = false;
	logplayerid = -1;
	decodeplayerid = -1;
	logsize = Logsize;
	modelpos = handsize = realsize = 0;
	Model = new BigInt*[logsize];
	for(i=0; i<logsize; i++)
		Model[i] = NULL;
	RealLog = new BigInt*[logsize];
	for(i=0; i<logsize; i++)
		RealLog[i] = NULL;
	onhand = new int[logsize];
	handsize = 0;
}

MentalPoker::MentalPoker(void){
	isencrypted = false;
	logplayerid = -1;
	decodeplayerid = -1;
	modelpos = handsize = realsize = 0;
	Model = NULL;
	RealLog = NULL;
	onhand = NULL;
}

void MentalPoker::Init(int Logsize){
	int i;
	logsize = Logsize;
	Model = new BigInt*[logsize];
	for(i=0; i<logsize; i++)
		Model[i] = NULL;
	RealLog = new BigInt*[logsize];
	for(i=0; i<logsize; i++)
		RealLog[i] = NULL;
	onhand = new int[logsize];
}

MentalPoker::~MentalPoker(void){
	int i;
	delete [] onhand;
	for(i=0; i<logsize; i++)
		if(RealLog[i] != NULL)
			delete RealLog[i];
	delete [] RealLog;
	for(i=0; i<logsize; i++)
		if(Model[i] != NULL)
			delete Model[i];
	delete [] Model;
}

void MentalPoker::Debug(void){
	int i;
	printf("Log: \n");
	for(i=0; i<realsize; i++)
		printf("%d: %s\n", i, ((RealLog[i]!=NULL)?RealLog[i]->Debug().c_str():"NULL"));
	printf("OnHand: ");
	for(i=0; i<handsize; i++)
		printf("%d ", onhand[i]);
	printf("\n");
	printf("Pk %s\n", Pk.Debug().c_str());
	printf("Dk %s\n", Dk.Debug().c_str());
	printf("Ck %s\n", Ck.Debug().c_str());
	printf("LogControl %d\n", GetLogPlayerid());
	printf("DecodeControl %d\n", GetDecodePlayerid());
}

bool MentalPoker::IsEncrypted(void){
	return isencrypted;
}

int MentalPoker::GetDecodePlayerid(void){
	return decodeplayerid;
}

void MentalPoker::SetDecodePlayerid(int playerid){
	decodeplayerid = playerid;
}

int MentalPoker::GetLogPlayerid(void){
	return logplayerid;
}

void MentalPoker::SetLogPlayerid(int playerid){
	logplayerid = playerid;
}

void MentalPoker::GenerateKeys(BigInt &P){
	BigInt One(1); //!!
	Pk = P.Sub(One);
	do {
		Dk.GenerateRandomNumber(TEMP_FBITS);
	} while(Pk.Compare(Dk) < 1 || Pk.GCD(Dk).Compare(One) != 0);
	Ck = Pk.Euclid(Dk);
	Pk = P;
}

int MentalPoker::GetCountModelLog(void){
	return logsize;
}

void MentalPoker::GenerateModelCards(void){
	BigInt Tmp, Pt(1), Null;
	Pt = Pk.Sub(Pt);
	while(modelpos < logsize){
		Tmp.GenerateRandomNumber(TEMP_FBITS);
		if(Pt.Compare(Tmp) < 1 || Null.Compare(Tmp) == 0) continue;
		AddModelCard(Tmp);
	}
}

BigInt & MentalPoker::GetModelCard(int idx){
	return *Model[(idx > -1 && idx < logsize)?idx:0];
}

void MentalPoker::AddModelCard(BigInt &card){
	int i;
	for(i=0; i<modelpos; i++)
		if(card.Compare(*Model[i])==0) return;
	Model[modelpos++] = new BigInt(card);
}

int MentalPoker::GetCountLog(void){
	return realsize;
}

BigInt MentalPoker::GetRandomCardFromLog(void){
	BigInt card;
	if(realsize<1) return card;
	int gr = rand()%realsize;
	card = *RealLog[gr];
	RemFromMass(RealLog, gr, realsize);
	return card;
}

BigInt MentalPoker::GetCardFromLogById(int idx){
	BigInt card;
	if(idx < realsize)
		card = *RealLog[idx];
	return card;
}

void MentalPoker::PutCardToLog(BigInt &card){
	AddToMass(RealLog, card, realsize);
}

void MentalPoker::MessLog(void){
	MessMass(RealLog, realsize);
}

void MentalPoker::EncryptLog(void){
	EncryptMass(RealLog, realsize);
}

void MentalPoker::UnencryptLog(void){
	UnencryptMass(RealLog, realsize);
}

void MentalPoker::ClearLog(void){
	ClearMass(RealLog, realsize);
}

int MentalPoker::GetCountHand(void){
	return handsize;
}

int MentalPoker::GetCardFromHand(int idx){
	return onhand[idx];
}

void MentalPoker::PutCardToHand(BigInt &card){
	int idx;
	card = card.PowerAndMod(Dk, Pk); // Decode
	idx = SearchInMass(Model, card, logsize);
	if(idx >= 0)
		onhand[handsize++] = idx;
	//else Error!
}

int * MentalPoker::GetPlayerCardsOnHand(void){
	return onhand;
}

int MentalPoker::GetPlayerCountOnHand(void){
	return handsize;
}

void MentalPoker::ClearPlayerOnHand(void){
	handsize = 0;
}

void MentalPoker::ClearHand(void){
	handsize = 0;
}

/* SAVE IN OTHER FILE */
//#define deb(x) cout << x << endl; fflush(stdout)

/*int main(void){
	int size,i;
	MentalPoker A(10),B(10);
	BigInt mentalP;
	mentalP.GenerateRandomSimple(36);
	A.GenerateKeys(mentalP);
	A.GenerateModelCards();
	B.GenerateKeys(mentalP);
	size = A.GetCountModelLog();
	for(i=0; i<size; i++){
		cout << A.GetModelCard(i).Debug() << endl;
		B.AddModelCard(A.GetModelCard(i));
	}
	for(i=0; i<size; i++)
		A.PutCardToLog(A.GetModelCard(i));
	cout << "1" << endl;
	A.Debug();
	getchar();
	cout << "2" << endl;
	A.EncryptLog();
	A.Debug();
	getchar();
	cout << "3" << endl;
	for(i=0; i<size; i++){
		mentalP = A.GetCardFromLogById(i);
		B.PutCardToLog(mentalP);
	}
	A.ClearLog();
	B.Debug();
	getchar();
	cout << "4" << endl;
	B.EncryptLog();
	B.Debug();
	getchar();
	cout << "5" << endl;
	B.UnencryptLog();
	B.Debug();
	getchar();
	cout << "6" << endl;
	for(i=0; i<size; i++){
		mentalP = B.GetCardFromLogById(i);
		A.PutCardToLog(mentalP);
	}
	B.ClearLog();
	A.Debug();
	getchar();
	cout << "7" << endl;
	B.UnencryptLog();
	B.Debug();
	getchar();
	return 0;
}*/

#endif //MENTALPOKER_CPP
