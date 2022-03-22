#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "biginteger.cpp"

using namespace std;

void AddFunc(string, string, string); //v
void SubFunc(string, string, string); //v
void MulFunc(string, string, string); //v
void DivFunc(string, string, string); //v
void ModFunc(string, string, string); //v
void CompFunc(string, string, string); //v
void ShRFunc(string, unsigned int, string);
void ShLFunc(string, unsigned int, string);
void LogMulFunc(string, string, string);
void LogAddFunc(string, string, string);
void PowModFunc(string, string, string, string);
void GCDFunc(string, string, string);
void AtFunc(string, unsigned int, bool);

int main(int argc, char *argv[])
{

	/*BigInt A("DDFEFE44098");
	for(int i=A.PhysBitsCount()-1; i>=0; i--)
		cout << A.At(i);
	cout << endl;*/
	/*AddFunc("1E240", "9", "1E249");
	AddFunc("98967F", "98967F", "1312CFE");
	AddFunc("1E240", "-1E240", "0");
	AddFunc("3A98", "-1B8A", "1F0E");
	AddFunc("-41A", "-1B8A", "-1FA4");
	AddFunc("-64", "3E8", "384");
	AddFunc("0", "-1B8A", "-1B8A");
	AddFunc("0", "0", "0");
		cout << endl;
		getchar();
	SubFunc("1E240", "9", "1E237");
	SubFunc("98967F", "98967F", "0");
	SubFunc("1E240", "-1E240", "3C480");
	SubFunc("3A98", "-1B8A", "5622");
	SubFunc("-41A", "-1B8A", "1770");
	SubFunc("-64", "3E8", "-44C");
	SubFunc("0", "-1B8A", "1B8A");
	SubFunc("0", "0", "0");
		cout << endl;
		getchar();
	MulFunc("1E240", "9", "10F440");
	MulFunc("98967F", "98967F", "5AF30F491301");
	MulFunc("1E240", "-1E240", "-38C751000");
	MulFunc("3A98", "-1B8A", "-64D9DF0");
	MulFunc("-41A", "-1B8A", "70F404");
	MulFunc("-64", "3E8", "-186A0");
	MulFunc("0", "-1B8A", "0");
	MulFunc("0", "0", "0");
		cout << endl;
		getchar();*/
	DivFunc("1E240", "9", "3595");
	DivFunc("98967F", "98967F", "1");
	DivFunc("1E240", "-1E240", "-1");
	DivFunc("3A98", "-1B8A", "-2");
	DivFunc("-41A", "-1B8A", "0");
	DivFunc("-64", "3E8", "0");
	DivFunc("0", "-1B8A", "0");
	//DivFunc("0", "0", "0");nan
		cout << endl;
		getchar();
	ModFunc("1E240", "9", "3");
	ModFunc("98967F", "98967F", "0");
	ModFunc("1E240", "-1E240", "0");
	ModFunc("3A98", "-1B8A", "384");
	ModFunc("-41A", "-1B8A", "-41A");
	ModFunc("-64", "3E8", "384");
	ModFunc("0", "-1B8A", "0");
		cout << endl;
		getchar();
	/*CompFunc("1E240", "9", ">");
	CompFunc("98967F", "98967F", "==");
	CompFunc("1E240", "-1E240", ">");
	CompFunc("3A98", "-1B8A", ">");
	CompFunc("-41A", "-1B8A", ">");
	CompFunc("-64", "3E8", "<");
	CompFunc("0", "-1B8A", ">");
	CompFunc("0", "0", "==");
		cout << endl;
		getchar();
	ShRFunc("12345", 0x4, "1234");
	ShRFunc("1E240", 0x9, "F1");
	ShRFunc("FFFFF", 0x12, "3");
	ShRFunc("1E240", 0xB, "3C");
	ShRFunc("123456789ABCDEF", 0xA, "48D159E26AF3");
	ShRFunc("FFFFF", 0xF, "1F");
	ShRFunc("64", 0x64, "0");
	ShRFunc("64", 0x0, "64");
	ShRFunc("64", 0x1, "32");
	ShRFunc("0", 0xA, "0");
	ShRFunc("0", 0x0, "0");
			cout << endl;
		getchar();
	ShLFunc("12345", 0x4, "123450");
	ShLFunc("1E240", 0x9, "3C48000");
	ShLFunc("FFFFF", 0x12, "3FFFFC0000");
	ShLFunc("1E240", 0xB, "F120000");
	ShLFunc("123456789ABCDEF", 0xA, "48D159E26AF37BC00");
	ShLFunc("FFFFF", 0xF, "7FFFF8000");
	ShLFunc("64", 0x64, "640000000000000000000000000");
	ShLFunc("64", 0x0, "64");
	ShLFunc("64", 0x1, "C8");
	ShLFunc("0", 0xA, "0");
	ShLFunc("0", 0x0, "0");
		cout << endl;
		getchar();
	LogMulFunc("12345", "12345", "12345");
	LogMulFunc("1E240", "9", "0");
	LogMulFunc("FFFFF", "12", "12");
	LogMulFunc("1E240", "42E1", "4240");
	LogMulFunc("123ABC", "FED", "AAC");
	LogMulFunc("FFFFF", "AAAAA", "AAAAA");
	LogMulFunc("64", "0", "0");
	LogMulFunc("64", "1", "0");
	LogMulFunc("0", "A", "0");
	LogMulFunc("0", "0", "0");
		cout << endl;
		getchar();
	LogAddFunc("12345", "12345", "12345");
	LogAddFunc("1E240", "9", "1E249");
	LogAddFunc("FFFFF", "12", "FFFFF");
	LogAddFunc("1E240", "42E1", "1E2E1");
	LogAddFunc("123ABC", "FED", "123FFD");
	LogAddFunc("FFFFF", "AAAAA", "FFFFF");
	LogAddFunc("64", "0", "64");
	LogAddFunc("64", "1", "65");
	LogAddFunc("0", "A", "A");
	LogAddFunc("0", "0", "0");
		cout << endl;
		getchar();*/
	/*PowModFunc("12345", "12", "9999F", "83310");*/
	//PowModFunc("1E240", "9", "AB", "12");
	//PowModFunc("FFFFF", "12", "EEF", "8E4"); // ok
	/*PowModFunc("123456789ABCDEF", "F", "ABCDEF", "6590FA");*/
	//PowModFunc("FFFFF", "ABC", "2", "1");
	/*PowModFunc("64", "0", "2", "1");
	PowModFunc("64", "1", "2", "0");
	PowModFunc("0", "A", "A", "0");
	PowModFunc("0", "0", "9", "1");*//*
		cout << endl;
		getchar();
	GCDFunc("12345", "12345", "12345");
	GCDFunc("1E240", "9", "3");
	GCDFunc("FFFFF", "12", "3");
	GCDFunc("1E240", "42E1", "3");
	GCDFunc("123ABC", "FED", "3");
	GCDFunc("FFFFF", "AAAAA", "55555");
	GCDFunc("64", "0", "64");
	GCDFunc("64", "1", "1");
	GCDFunc("0", "A", "A");
	GCDFunc("0", "0", "0");
		cout << endl;
		getchar();
	AtFunc("12345", 5, false);
	AtFunc("1E240", 16, true);
	AtFunc("FFFFF", 18, true);
	AtFunc("1E240", 24, false);
	AtFunc("123ABC", 2, true);
	AtFunc("64", 2, true);
	AtFunc("64", 1, false);
	AtFunc("1", 0, true);
	AtFunc("0", 0, false);*/
	
getchar();
return EXIT_SUCCESS;
}

//Add:
void AddFunc(string a, string b, string c){
	BigInt A(a), B(b), C;
	cout << A.Debug() << " + " << B.Debug();
	C = A.Add(B);
	cout << " = " << C.Debug();
	if (C.Debug()!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
}

//Sub:
void SubFunc(string a, string b, string c){
	BigInt A(a), B(b), C;
	cout << A.Debug() << " - " << B.Debug();
	C = A.Sub(B);
	cout << " = " << C.Debug();
	if (C.Debug()!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
}

//Mul:
void MulFunc(string a, string b, string c){
	BigInt A(a), B(b), C;
	cout << A.Debug() << " * " << B.Debug();
	C = A.Mul(B);
	cout << " = " << C.Debug();
	if (C.Debug()!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
}

//Div:
void DivFunc(string a, string b, string c){
	BigInt A(a), B(b), C;
	cout << A.Debug() << " / " << B.Debug();
	C = A.Div(B);
	cout << " = " << C.Debug();
	if (C.Debug()!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
}

//Mod:
void ModFunc(string a, string b, string c){
	BigInt A(a), B(b), C;
	cout << A.Debug() << " % " << B.Debug();
	C = A.Mod(B);
	cout << " = " << C.Debug();
	if (C.Debug()!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
}

//Compare:
void CompFunc(string a, string b, string c){
	BigInt A(a), B(b);
	int check = A.Compare(B);
	string C(check==0?"==":check>0?">":"<");
	cout << A.Debug() << " " << C << " " << B.Debug();
	if (C!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
}

//ShiftRight:
void ShRFunc(string a, unsigned int b, string c){
	BigInt A(a), C;
	cout << A.Debug() << " >> " << b;
	C = A.ShiftRight(b);
	cout << " = " << C.Debug();
	if (C.Debug()!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
}

//ShiftLeft:
void ShLFunc(string a, unsigned int b, string c){
	BigInt A(a), C;
	cout << A.Debug() << " << " << b;
	C = A.ShiftLeft(b);
	cout << " = " << C.Debug();
	if (C.Debug()!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
}

//LogicMulLeft:
void LogMulFunc(string a, string b, string c){
	BigInt A(a), B(b), C;
	cout << A.Debug() << " & " << B.Debug();
	C = A.And(B);
	cout << " = " << C.Debug();
	if (C.Debug()!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
}

//LogicAddLeft:
void LogAddFunc(string a, string b, string c){
	BigInt A(a), B(b), C;
	cout << A.Debug() << " | " << B.Debug();
	C = A.Or(B);
	cout << " = " << C.Debug();
	if (C.Debug()!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
}

//PowerAndMod:
void PowModFunc(string a, string b, string m, string c){
	BigInt A(a), B(b), M(m), C;
	cout << A.Debug() << " ^ " << B.Debug() << " mod " << M.Debug();
	C = A.PowerAndMod(B, M);
	cout << " = " << C.Debug();
	if (C.Debug()!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
	fflush(stdout);
}

//GCD:
void GCDFunc(string a, string b, string c){
	BigInt A(a), B(b), C;
	cout << A.Debug() << " gcd " << B.Debug();
	C = A.GCD(B);
	cout << " = " << C.Debug();
	if (C.Debug()!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
}

//At:
void AtFunc(string a, unsigned int b, bool c){
	BigInt A(a);
	bool C;
	cout << A.Debug() << " At " << b;
	C = A.At(b);
	cout << " = " << (C?"true":"false");
	if (C!=c) cout <<" FAIL!" << endl;    
	else  cout <<" OK!" << endl; 
}
