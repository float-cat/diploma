#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "biginteger.hpp"

using namespace std;

#define SIZEOFBIGINT 8

#define debmsg(x) cout << "Debug: " << #x << " = " << x.Debug() << endl; fflush(stdout)
//#define debmsg(x) printf("Debug: %s = %X\n", # x , atoi(x.Debug().c_str())); fflush(stdout)
//#define debmsg(x) x = x;

/*BigInt RSA(BigInt M){
	BigInt M1, M2, N, P, Q, C, D, Fi, One(1), Null;
	bool negcheck = M.Compare(Null) < 0;
	if(negcheck) M1 = M.Not();
debmsg(M1);
	P.GenerateRandomSimple(24);
debmsg(P);
	Q.GenerateRandomSimple(24);
debmsg(Q);
	N = P.Mul(Q);
debmsg(N);
	P = P.Sub(One);
debmsg(P);
	Q = Q.Sub(One);
debmsg(Q);
	Fi = P.Mul(Q);
debmsg(Fi);
	do {
		D.GenerateRandomNumber(SIZEOFBIGINT);
debmsg(D);
	} while(Fi.Compare(D) < 1 || Fi.GCD(D).Compare(One) != 0);
	C = Fi.Euclid(D);
debmsg(C);
	M2 = M1.PowerAndMod(D, N);
debmsg(M2);
	M2 = M2.PowerAndMod(C, N);
debmsg(M2);
	if(negcheck) M2 = M2.Not();
	return M2;
}*/

BigInt RSA(BigInt M){ //Analiz not for Cap
	BigInt Mtest("EC"), Ptest("E1"), Qtest("6F");
	BigInt M1, M2, N, P, Q, C, D, Fi, One(1), Null;
	bool negcheck = M.Compare(Null) < 0;
	//if(negcheck) M1 = M.Not();
	M1 = Mtest;
debmsg(M1);
	P = Ptest;
debmsg(P);
	Q = Qtest;
debmsg(Q);
	N = P.Mul(Q);
debmsg(N);
	P = P.Sub(One);
debmsg(P);
	Q = Q.Sub(One);
debmsg(Q);
	Fi = P.Mul(Q);
debmsg(Fi);
	do {
		D.GenerateRandomNumber(SIZEOFBIGINT);
debmsg(D);
	} while(Fi.Compare(D) < 1 || Fi.GCD(D).Compare(One) != 0);
	C = Fi.Euclid(D);
debmsg(C);
	M2 = M1.PowerAndMod(D, N);
debmsg(M2);
	M2 = M2.PowerAndMod(C, N);
debmsg(M2);
	//if(negcheck) M2 = M2.Not();
	return M2;
}


int main(int argc, char *argv[])
{
    //Debug
    BigInt::InitClass();
    BigInt::SetCapacity(SIZEOFBIGINT);

/**/
/*BigInt Test;
for(int i=0; i<10; i++){
Test.GenerateRandomNumber(SIZEOFBIGINT);
cout << "Generator: Test = " << Test.Debug() << endl; fflush(stdout);
}*/

    BigInt M, Res;
    int i;
    for(i=0; i<5; i++){
	//M.GenerateRandomNumber(rand()%15+9);
	M.GenerateRandomNumber(SIZEOFBIGINT);
cout << "Generator: M = " << M.Debug() << endl; fflush(stdout);
	M = M.Not();
    	Res = RSA(M);
cout << "func RSA: Res = " << Res.Debug() << endl; fflush(stdout);
	if(Res.Compare(M) != 0){
		cout << "Error on " << i << " with " << M.Debug() << endl;
		break;
	}
	cout << i << " (" << M.Debug() << ") success!" << endl;
    }
    //getchar();
    //getchar();
    return EXIT_SUCCESS;
}
