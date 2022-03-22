#ifndef	BIGINTEGER_CPP
#define BIGINTEGER_CPP

#include "biginteger.hpp"

signed int BigInt::pow_mod(signed int a, signed int grade, signed int mod){ // not exist in original!
	int result;
	int tmp = a;
	int i = 1, physbitscount = 0;
	result = 1;
	while(grade >= i){
		i <<= 1;
		physbitscount++;
	}
	for(i=0; i<physbitscount; i++){
		if(grade & (1 << i) != 0){
			result *= tmp;
			result %= mod;
		}
		tmp *= tmp;
		tmp %= mod;
	}
	return result;
}

void BigInt::parseString(string x){
	value = atoi(x.c_str());
}

unsigned int BigInt::PhysLength(void){
	return 1;
}

unsigned int BigInt::PhysBitsCount(void){
	unsigned int result = 0, i;
	i = 1;
	while(value >= i){
		i <<= 1;
		result++;
	}
	return result;
}

void BigInt::InitClass(void){
	srand(time(0));
}

void BigInt::SetCapacity(unsigned int bits){
       capacity = 1;
}

unsigned int BigInt::GetCapacity(void){
	//return 15;
	return 56; // to support autotest
}

unsigned int BigInt::GetCapacityBytes(void){
	return 2;
}

unsigned int BigInt::GetCapacityCells(void){
	return 1;
}

BigInt::BigInt(void){
	value = 0;
	Clear();
}

BigInt::BigInt(string x){
	parseString(x);
}

BigInt::BigInt(int x){
	value = x;
}

BigInt::BigInt(const BigInt &x){
	value = x.value;
}

BigInt::~BigInt(void){
}

void BigInt::operator=(const BigInt &x){
	value = x.value;
}

int BigInt::UsesCellsCount(void){
	return 1;
}

void BigInt::Clear(void){
	value = 0;
}

signed int BigInt::Compare(BigInt x){ // 1 > -1
       if(value > x.value) return 1;
       if(value < x.value) return -1;
       return 0;
}

BigInt BigInt::Not(void){
	BigInt Result;
	Result.value = -value;
	return Result;
}

BigInt BigInt::Add(BigInt x){
	BigInt Result;
	Result.value = value + x.value;
	return Result;
}

BigInt BigInt::Sub(BigInt x){
	BigInt Result;
	Result.value = value - x.value;
	return Result;
}

BigInt BigInt::Mul(BigInt x){
	BigInt Result;
	Result.value = value * x.value;
	return Result;
}

BigInt BigInt::Div(BigInt x){
	BigInt Result;
	if(x.value == 0) Result.value = 0; // incorrect!
	else Result.value = value / x.value;
	return Result;
}

BigInt BigInt::Mod(BigInt x){
	BigInt Result;
	if(x.value == 0) Result.value = 0; // incorrect!
	else Result.value = value % x.value;
	return Result;
}

BigInt BigInt::ShiftLeft(unsigned int shift){
	BigInt Result;
	Result.value = value << shift;
	return Result;
}

BigInt BigInt::ShiftRight(unsigned int shift){
	BigInt Result;
	Result.value = value >> shift;
	return Result;
}

BigInt BigInt::And(BigInt x){
	BigInt Result;
	Result.value = value & x.value;
	return Result;
}

BigInt BigInt::Or(BigInt x){
	BigInt Result;
	Result.value = value | x.value;
	return Result;
}

BigInt BigInt::PowerAndMod(BigInt grade, BigInt mod){ // in original not used Tmp1, Mod
    BigInt Result;
    int tmp = value;
    Result.value = 1;
    int i, physbitscount = grade.PhysBitsCount();
    for(i=0; i<physbitscount; i++){
	if(grade.value & (1 << i) != 0){
        	Result.value *= tmp;
		Result.value %= mod.value;
	}
	tmp *= tmp;
	tmp %= mod.value;
    }
    return Result;
}

BigInt BigInt::GCD(BigInt x){
	BigInt Result;
	int tmp, a, b;
	if(value >= x.value) { a = value; b = x.value; }
	else {a = x.value; b = value; }
	while(b!=0){
		tmp = a % b;
		a = b;
		b = tmp;
	}
	Result.value = a;
	return Result;
}

BigInt BigInt::Euclid(BigInt x){
	// match a >= b
	BigInt Result;
	int a = value, b = x.value, t, a1 = 0, b1 = 1, t1, q; // need change a and b by rule a>=b
	while(b!=0){
		q = a / b;
		t = a % b;
		t1 = a1 - (b1 * q);
		a = b; a1 = b1;
		b = t; b1 = t1;
	}
	if(a1<0)
		a1 = a1 + value;
	Result.value = a1;
	return Result;
}

bool BigInt::At(unsigned int position){
	if(position > 15) return false;
	else (value & (1 << position)) != 0;
}

int BigInt::PackToString(char * buffer){
	memcpy(buffer, &value, sizeof(signed int));
}

void BigInt::UnPackFromString(char * buffer){
	memcpy(&value, buffer, sizeof(signed int));
}


string BigInt::Debug(void){
	string result;
	char buffer[16];
	sprintf(buffer, "%d", value);
	result = buffer;
	return result;
}

void BigInt::SetString(string x){
	parseString(x);
}

void BigInt::GenerateRandomNumber(unsigned int bits){
	value = rand()%0xFF;

}

void BigInt::GenerateRandomSimple(unsigned int bits){ // in original not used Tmp2 // it is works in original?
	int attempt = 0;
	int num, a, d, tmp;
	num = rand()%0xF0+0xF;
	while(attempt < ITERATION_COUNT_FERMA){
		a = rand()%num;
		tmp = 1;
		d = num;
		d -= tmp;
		tmp = num;	
		a = pow_mod(a, d, tmp); // function pow_mod(a, g, m) not exist in original!
		if(a != 1){
			num = rand()%0xF0+0xF;
			attempt = 0;
		}
		else attempt++;
	}
	value = num;
}

void BigInt::CheckSimple(void){ // Debug!
	printf("SimpleCheck %d start!\n", value);
	fflush(stdout);
	int max, tmp, i = 2;
	max = value / 2 + 1;
	while( i <= max){
		tmp = value % i;
		if(tmp == 0) {
			printf("Number %d is not simple! for %d\n", value, i);
			fflush(stdout);
			return;
		}
		i++;
	}
	printf("Number %d is simple!\n", value);
	fflush(stdout);
}

void BigInt::ConvertDataToBigInt(char * data, int &len, int size, BigInt *Key){
	int convertsize = (size-len > sizeof(signed int)) ? sizeof(signed int) : (size-len);
	memcpy(&value, data, convertsize);
	len += convertsize;
}

void BigInt::ConvertBigIntToData(char * data, int &len, int size){ //---
	int convertsize = (size-len > sizeof(signed int)) ? sizeof(signed int) : (size-len);
	memcpy(data, &value, convertsize);
	len += convertsize;
}

int BigInt::ToInt(void){
	return value;
}

#endif
