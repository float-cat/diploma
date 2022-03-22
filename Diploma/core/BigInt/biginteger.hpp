/*
	BigInt v1.1 object / current
	-- err none
	-- how overloading =
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

typedef short type_cell; // to global definition
typedef short* type_cell_p;
typedef long type_double_cell;

#define COUNT_ACTIVE_DIGIT          3
#define COUNT_ACTIVE_BITS          12
#define OVER_CELL              0x1000
#define MASK_CELL               0xFFF
#define ITERATION_COUNT_FERMA     200

class BigInt {
 public:
	static unsigned int capacity;
	type_cell_p value;
	unsigned int length;
	bool negative;
	void parseString(string x);
	void PoweredCell(unsigned int x);
	void CellPlus(type_cell x);
 public:
	unsigned int PhysLength(void);
	unsigned int PhysBitsCount(void);
	BigInt Mul(type_double_cell x);//uni?
 public:
	static void InitClass(void);
    	static void SetCapacity(unsigned int bits);
	static unsigned int GetCapacity(void);
	static unsigned int GetCapacityBytes(void);
	static unsigned int GetCapacityCells(void);
	BigInt(void);
	BigInt(string x);
	BigInt(type_double_cell x);
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

	//void PackToString(type_cell * buffer);
	//void UnPackFromString(type_cell * buffer);
	int PackToString(char * buffer);
	void UnPackFromString(/*int len, */char * buffer);

	string Debug(void);
	void SetString(string x);
	void GenerateRandomNumber(unsigned int bits);
	void GenerateRandomSimple(unsigned int bits);
	void CheckSimple(void); //debug

	void ConvertDataToBigInt(char * data, int &len, int size, BigInt *Key = NULL);
	void ConvertBigIntToData(char * data, int &len, int size);
	
	//
	int ToInt(void);
};

#ifndef OBJ_FILE
unsigned int BigInt::capacity = 64;
#endif

#endif
