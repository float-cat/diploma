/*
	BigInt Cap
	-- work!
*/

#ifndef	BIGINTEGER_HPP
#define BIGINTEGER_HPP

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <string>

using namespace std;

#define COUNT_ACTIVE_DIGIT          3
#define COUNT_ACTIVE_BITS          12
#define OVER_CELL              0x1000
#define MASK_CELL               0xFFF
#define ITERATION_COUNT_FERMA     200

class BigInt {
 private:
	signed int pow_mod(signed int a, signed int grade, signed int mod); // not exist in original!
 public:
	static unsigned int capacity;
	signed int value;
	void parseString(string x);
 public:
	unsigned int PhysLength(void); // -
	unsigned int PhysBitsCount(void); // -
 public:
	static void InitClass(void); // to support
    	static void SetCapacity(unsigned int bits); // to support
	static unsigned int GetCapacity(void); // to support
	static unsigned int GetCapacityBytes(void); // to support
	static unsigned int GetCapacityCells(void); // to support
	BigInt(void);
	BigInt(string x);
	BigInt(int x); // as BigInt(type_double_cell x); to support
	BigInt(const BigInt &x);
	~BigInt(void);

	void operator=(const BigInt &x);
	int UsesCellsCount(void);

	void Clear(void);
	signed int Compare(BigInt x);
	BigInt Not(void);
	BigInt Add(BigInt x);
	BigInt Sub(BigInt x);
	BigInt Mul(BigInt x);
	BigInt Div(BigInt x);
	BigInt Mod(BigInt x);
	BigInt ShiftLeft(unsigned int shift);
	BigInt ShiftRight(unsigned int shift);
	BigInt And(BigInt x);
	BigInt Or(BigInt x);
	BigInt PowerAndMod(BigInt grade, BigInt mod);
	BigInt GCD(BigInt x);
	BigInt Euclid(BigInt x);
	bool At(unsigned int position);

	int PackToString(char * buffer);
	void UnPackFromString(char * buffer);

	string Debug(void); //debug
	void SetString(string x);
	void GenerateRandomNumber(unsigned int bits);
	void GenerateRandomSimple(unsigned int bits);
	void CheckSimple(void); //debug

	void ConvertDataToBigInt(char * data, int &len, int size, BigInt *Key = NULL); // it is correct? // need optimal solution! // 0x1 - error!
	void ConvertBigIntToData(char * data, int &len, int size); // it is correct? // need optimal solution!
	
	//
	int ToInt(void);
};

#ifndef OBJ_FILE
unsigned int BigInt::capacity = 64;
#endif

#endif
