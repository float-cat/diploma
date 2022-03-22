#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "biginteger.hpp" // translation *.o

#define TESTCOUNT 1000

bool AddSubCheck(void);
bool MulDivCheck(void);
bool ModCheck(void);
bool ShiftCheck(void);
bool OrAndCheck(void);
bool GCDCheck(void);
bool SimpleCheck(BigInt &);

int main(void){
	int i;
	BigInt::InitClass();
	BigInt A;
	for(i=0; i<TESTCOUNT && !AddSubCheck(); i++);
	cout << "Complete \"Add\" " << ((i*100)/TESTCOUNT) << "\%" << endl;
	for(i=0; i<TESTCOUNT && !MulDivCheck(); i++);
	cout << "Complete \"Mul\" " << ((i*100)/TESTCOUNT) << "\%" << endl;
	for(i=0; i<TESTCOUNT && !ModCheck(); i++);
	cout << "Complete \"Mod\" " << ((i*100)/TESTCOUNT) << "\%" << endl;
	for(i=0; i<TESTCOUNT && !ShiftCheck(); i++);
	cout << "Complete \"Shift\" " << ((i*100)/TESTCOUNT) << "\%" << endl;
	for(i=0; i<TESTCOUNT && !OrAndCheck(); i++);
	cout << "Complete \"OrAnd\" " << ((i*100)/TESTCOUNT) << "\%" << endl;
	for(i=0; i<TESTCOUNT && !GCDCheck(); i++);
	cout << "Complete \"GCD\" " << ((i*100)/TESTCOUNT) << "\%" << endl;
	i = 0;
	while(true){
		A.GenerateRandomSimple(24);
		cout << "Simple ? " << A.Debug() << endl; fflush(stdout);
		if(SimpleCheck(A)){
			cout << "Simple = " << A.Debug() << endl;
			break;
		}
		else {
			cout << i++ << " number is fail " << endl;
			fflush(stdout);
		}
	}
	return 0;
}

//Add:
bool AddSubCheck(void){
	bool testerror = false;
	int c;
	BigInt A, B, C, Null;
	A.GenerateRandomNumber((unsigned int)BigInt::GetCapacity()/2);
	B.GenerateRandomNumber((unsigned int)BigInt::GetCapacity()/2);
	C = A.Add(B);
	C = C.Sub(B);
	if((c = C.Compare(A)) == 0) {
		C = C.Sub(A);
		if(C.Compare(Null) != 0) testerror = true;
	} 
	else testerror = true;
	if(testerror){
		cout << "Detect \"Add\" Error " << endl;
		cout << "\t A: " <<  A.Debug() << " " << endl;
		cout << "\t B: " <<  B.Debug() << " " << endl;
	}
	return testerror; 
}

bool MulDivCheck(void){
	bool testerror = false;
	BigInt A, B, C, One(1), Null;
	A.GenerateRandomNumber(BigInt::GetCapacity()/2-12);
	B.GenerateRandomNumber(BigInt::GetCapacity()/2-12);
	if(A.Compare(Null) == 0) A = One;
	if(B.Compare(Null) == 0) B = One;
	C = A.Mul(B);
	C = C.Div(B);
	if(C.Compare(A) == 0) {
		C = C.Div(A);
		if(C.Compare(One) != 0) testerror = true;
	} 
	else testerror = true;
	if(testerror){
		cout << "Detect \"Mul\" Error " << endl;
		cout << "\t A: " <<  A.Debug() << " " << endl;
		cout << "\t B: " <<  B.Debug() << " " << endl;
	}
	return testerror; 
}

bool ModCheck(void){
	bool testerror = false;
	int c;
	BigInt A, B, C, M, One(1), Null;
	A.GenerateRandomNumber(BigInt::GetCapacity()/2-12);
	B.GenerateRandomNumber(BigInt::GetCapacity()/2-12);
	if(A.Compare(Null) == 0) A = One;
	if(B.Compare(Null) == 0) B = One;
	C = A.Div(B);
	C = C.Mul(B);
	M = A.Mod(B);
	B = C.Add(M);
	if((c = A.Compare(B)) == 0) return testerror;
	else testerror = true;
	if(testerror){
		cout << "Detect \"Mod\" Error " << endl;
		cout << "\t A: " <<  A.Debug() << " " << endl;
		cout << "\t B: " <<  B.Debug() << " " << endl;
	}
	return testerror; 
}

bool ShiftCheck(void){
	bool testerror = false;
	int c;
	BigInt A, Atest;
	A.GenerateRandomNumber(BigInt::GetCapacity()/2-12);
	c = rand()%(BigInt::GetCapacity()/2-12);
	Atest = A.ShiftLeft(c);
	Atest = Atest.ShiftRight(c);
	if(Atest.Compare(A) == 0) return testerror;
	else testerror = true;
	if(testerror){
		cout << "Detect \"Shift\" Error " << endl;
		cout << "\t A: " <<  A.Debug() << " << " << c << ":" << endl;
	}
	return testerror; 
}

bool OrAndCheck(void){
	bool testerror = false;
	int c;
	BigInt A, B, C, Tmp;
	A.GenerateRandomNumber(BigInt::GetCapacity()/2-12);
	B.GenerateRandomNumber(BigInt::GetCapacity()/2-12);
	C = A.Or(B);
	Tmp = C;
	C = C.And(A);
	if((c = C.Compare(A)) == 0) {
		C = Tmp;
		C = C.And(B);
		if((c = C.Compare(B)) == 0) {} // not valid code !
		else testerror = true;
	} 
	else testerror = true;
	if(testerror){
		cout << "Detect \"OrAnd\" Error " << endl;
		cout << "\t A: " <<  A.Debug() << " " << endl;
		cout << "\t B: " <<  B.Debug() << " " << endl;
	}
	return testerror; 
}

bool GCDCheck(void){
	bool testerror = false;
	int c;
	BigInt A, B, C, One(1);
	A.GenerateRandomNumber(BigInt::GetCapacity()/2-12);
	B.GenerateRandomNumber(BigInt::GetCapacity()/2-12);
	C = A.GCD(B);
	A = A.Div(C);
	B = B.Div(C);
	C = A.GCD(B);
	if((c = C.Compare(One)) == 0) return testerror;
	else testerror = true;
	if(testerror){
		cout << "Detect \"GCD\" Error " << endl;
		cout << "\t A: " <<  A.Debug() << " " << endl;
		cout << "\t B: " <<  B.Debug() << " " << endl;
	}
	return testerror; 
}

bool SimpleCheck(BigInt &A){
	BigInt One(1), Tmp(2), I(2), Null, Max;
	Max = A;
	Max = Max.Div(Tmp);
	Max = Max.Add(One);
	while(I.Compare(Max) < 1){
		Tmp = A.Mod(I);
		if(Tmp.Compare(Null)==0) return false;
		I = I.Add(One);
	}
	return true;
}
