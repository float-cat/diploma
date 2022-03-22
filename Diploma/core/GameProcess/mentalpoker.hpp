#ifndef MENTALPOKER_HPP
#define MENTALPOKER_HPP

#include "../BigInt/biginteger.hpp"

#define TEMP_FBITS 16 //DOUBLE 36

#define LOCAL_PLAYERID -2
#define NONE_PLAYERID -1

/*
Zadachi:
+1. Nyzhno ymet' tasovat massiv BigInt
   Vinimat' iz nego elementi
   Syvat' v nego elementi
+2. Nyzhno peredat' kazhdomy ychastniky kluch P
+3. Nyzhno peredat' kazhdomy ychastniky etalonnyu kolody
+4. Crypto & Encrypto funkcii
-5. nyzhno soedenit' mentalpoker s clientproto interfejsom
*/

class MentalPoker {
	BigInt Pk, Ck, Dk, **Model, **RealLog;
	int logsize, realsize, handsize, modelpos, *onhand;
	int decodeplayerid, logplayerid;
	bool isencrypted;
	// with mass
	void AddToMass(BigInt **Array, BigInt &card, int &size);
	void RemFromMass(BigInt **Array, int idx, int &size);
	void EncryptMass(BigInt **Array, int size);
	void UnencryptMass(BigInt **Array, int size);
	void MessMass(BigInt **Array, int size);
	void ClearMass(BigInt **Array, int &size);
	int SearchInMass(BigInt **Array, BigInt &card, int size);
 public:
	MentalPoker(int Logsize);
	MentalPoker(void);
	~MentalPoker(void);
	//
	void Debug(void);
	//
	void Init(int Logsize);
	bool IsEncrypted(void); //??
	int GetDecodePlayerid(void);
	void SetDecodePlayerid(int playerid);
	int GetLogPlayerid(void);
	void SetLogPlayerid(int playerid);
	void GenerateKeys(BigInt &P);   //(.)
	int GetCountModelLog(void);
	void GenerateModelCards(void);
	BigInt & GetModelCard(int idx);
	void AddModelCard(BigInt &card);
	int GetCountLog(void);
	BigInt GetRandomCardFromLog(void);  //(.)
	BigInt GetCardFromLogById(int idx);
	void PutCardToLog(BigInt &card);
	void MessLog(void);
	void EncryptLog(void);  //(.)
	void UnencryptLog(void); //(.)
	void ClearLog(void);
	int GetCountHand(void);
	int GetCardFromHand(int idx);
	void PutCardToHand(BigInt &card);  //(.)
	int * GetPlayerCardsOnHand(void);   //(.)
	int GetPlayerCountOnHand(void);     //(.)
	void ClearPlayerOnHand(void);	//(.)
	void ClearHand(void); // doublicat!! (.)
};

#endif //MENTALPOKER_HPP
