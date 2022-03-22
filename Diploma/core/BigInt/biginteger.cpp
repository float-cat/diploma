#ifndef	BIGINTEGER_CPP
#define BIGINTEGER_CPP

#include "biginteger.hpp"

void BigInt::parseString(string x){ // V
     int i,j,idx,bar;
     i = x.length()-1;
     negative = x[0] == '-';
     bar = negative ? 1 : 0;
     value[0] = 0; idx = 0;
     for(j=0; i>=bar; i--){
                   if(x[i]>47 && x[i]<58) value[idx] |= (x[i]-48) << (j*4);
                   else value[idx] |= (x[i]-55) << (j*4);
                   j++;
                   if(j >= COUNT_ACTIVE_DIGIT)
                        value[++idx]=0,j=0;
     }
     length = idx;
     if(j>0) length++;
}

void BigInt::PoweredCell(unsigned int x){ // V
	int i;
	for(i=length-1; i>=0; i--)
		value[i+x] = value[i];
	for(i=x-1; i>=0; i--)
		value[i] = 0;
	length += x;
}

void BigInt::CellPlus(type_cell x){ // V
	int i;
	if(length == 1 && value[0] == 0) value[0] = x;
	else{
		for(i=length; i>0; i--)
			value[i] = value[i-1];
		value[0] = x;
		length++;
	}
}

unsigned int BigInt::PhysLength(void){ // O
    type_cell check = 1;
    unsigned int result = (length - 1) * COUNT_ACTIVE_DIGIT;
    unsigned int i = length - 1;
    while(value[i]>=check){
          check <<= 4;
          result++;
    }
    return result;
}

unsigned int BigInt::PhysBitsCount(void){
    type_cell check = 1;
    unsigned int result = (length - 1) * COUNT_ACTIVE_BITS;
    unsigned int i = length - 1;
    while(value[i]>=check){
          check <<= 1;
          result++;
    }
    return result;
}

BigInt BigInt::Mul(type_double_cell x){ // optimal ?
	BigInt X(x);
	BigInt Result = *this;
	Result = Result.Mul(X);
	return Result;
}

void BigInt::InitClass(void){ // to-upper-level !
	srand(time(0));
}

void BigInt::SetCapacity(unsigned int bits){ // V
       capacity = bits / COUNT_ACTIVE_BITS + 1;
}

unsigned int BigInt::GetCapacity(void){
	return capacity * COUNT_ACTIVE_BITS;
}

unsigned int BigInt::GetCapacityBytes(void){
	return capacity * sizeof(type_cell);
}

unsigned int BigInt::GetCapacityCells(void){
	return capacity;
}

BigInt::BigInt(void){ // V
	value = new type_cell[capacity];
	Clear();
}

BigInt::BigInt(string x){ // V
	value = new type_cell[capacity];
	parseString(x);
}

BigInt::BigInt(type_double_cell x){ // V
	value = new type_cell[capacity];
	negative = x < 0;
	x = abs(x);
	value[0] = x % OVER_CELL;
	value[1] = x / OVER_CELL;
	length = (value[1]>0) ? 2 : 1;
}

BigInt::BigInt(const BigInt &x){
	value = new type_cell[capacity];
	memcpy(value, x.value, capacity*sizeof(type_cell));
	length = x.length;
	negative = x.negative;
}

BigInt::~BigInt(void){ // V
	delete [] value; // error double free
	//value = NULL;
}

void BigInt::operator=(const BigInt &x){ // V
	memcpy(value, x.value, capacity*sizeof(type_cell));
	length = x.length;
	negative = x.negative;
}

int BigInt::UsesCellsCount(void){
	return length;
}

void BigInt::Clear(void){ // V
	negative = false;
	length = 1;
	value[0] = 0;
}

signed int BigInt::Compare(BigInt x){ // 1 > -1 // V
       int i;
       if(negative != x.negative) return negative ? -1 : 1;
       if(length > x.length) return negative ? -1 : 1;
       if(length < x.length) return negative ? 1 : -1;
       for(i=length-1; i>=0; i--){
               if(value[i]>x.value[i]) return negative ? -1 : 1;
               if(value[i]<x.value[i]) return negative ? 1 : -1;
       }
       return 0;
}

BigInt BigInt::Not(void){ // V optimal ?
	BigInt Result;
	Result = *this;
	Result.negative = !negative;
	return Result;
}

BigInt BigInt::Add(BigInt x){ // V optimal ?
       int i; bool upcheck = false;
       if(negative == x.negative){
	      BigInt A, B;
              A = (length>x.length) ? *this : x;
              B = (length>x.length) ? x : *this;
              for(i=0; i<B.length; i++){
                       A.value[i] += B.value[i];
                       if(A.value[i]>=OVER_CELL) {
                           A.value[i] %= OVER_CELL;
                           if(i+1 == A.length){ //check out of range? -for each meth
                                upcheck = true;
				A.value[i+1] = 1;
			   }
                           else A.value[i+1] += 1;
                       }
              }
              if(upcheck) 
                          A.length++;
              return A;
       }
       return negative ? x.Sub(this->Not()) : this->Sub(x.Not());
}

BigInt BigInt::Sub(BigInt x){ // V optimal ?
       int i,check; bool negcheck = false;
       if(negative == x.negative){
                   negcheck = negative;
                   negative = x.negative = false;
                   check = this->Compare(x);
                   BigInt A = (check >= 0) ? *this : x;
                   BigInt B = (check >= 0) ? x : *this;
                   if(!(check >= 0)) negcheck = !negcheck;
                   for(i=0; i<B.length; i++){
                            if(A.value[i]<B.value[i]){
                                    A.value[i] += OVER_CELL;
                                    A.value[i] -= B.value[i];
                                    A.value[i+1]--;
                            }
                            else A.value[i] -= B.value[i];
                   }
		   for(i=A.length-1; i>0; i--){
			       if(A.value[i]==0) A.length--;
                   	       else break;
		   }
		   for(i=0; i<A.length; i++){
                    if(A.value[i]<0){
                      A.value[i] += OVER_CELL;
                      A.value[i+1]--;
                    }
           }
           if(A.length>1 && A.value[A.length-1]==0) A.length--;
           if(negcheck && !(A.length==1 && A.value[0]==0)) A.negative = true;
           return A;
       }
       return this->Add(x.Not());
}

BigInt BigInt::Mul(BigInt x){ // V optimal ?
	bool negcheck;
	int i,j;
	type_double_cell tmpcell;
	BigInt Result, Tmp;
	negcheck = negative != x.negative;
	BigInt A = (length > x.length) ? *this : x;
	BigInt B = (length > x.length) ? x : *this;
	for(i=0; i<B.length; i++){
		Tmp.Clear();
		for(j=0; j<A.length; j++){
			tmpcell = B.value[i]; // optimal? -local
			tmpcell *= A.value[j];
			Tmp.value[j] += tmpcell % OVER_CELL;
			Tmp.value[j+1] = tmpcell / OVER_CELL;
			if(Tmp.value[j]>=OVER_CELL) {
				Tmp.value[j+1] += 1;
				Tmp.value[j] %= OVER_CELL;
			}
		}
		if(Tmp.value[A.length]>0) Tmp.length = A.length+1;
		else Tmp.length = A.length;
		Tmp.PoweredCell(i);
		Result = Result.Add(Tmp);
	}
	//A.value[0] = 0; // ??
	A = Result;
	for(i=A.length-1; i>0; i--){
		if(A.value[i]==0) A.length--;
                else break;
	}
	if(negcheck && !(A.length==1 && A.value[0]==0)) A.negative = true;
	return A;
}

BigInt BigInt::Div(BigInt x){ // V Restruct ? optimal ?
	bool negcheck;	
	int i, diff;
	bool once;
	BigInt A = *this;
	negcheck = negative != x.negative;
	negative = x.negative = false;
	int check = this->Compare(x);
	if(check<1) {
		A.Clear();
		if(check == 0) {
			A.value[0] = 1;
			A.negative = negcheck;
		}
		return A;
	}
	BigInt Tmp, Tmp1, Tmp2, Result; // why here ?
	type_double_cell min, max, tmp;
	Tmp1 = x;
	diff = length - x.length; 
	for(i=x.length-1; i>=0; i--)
		Tmp.value[i] = value[i+diff];
	Tmp.length = x.length;
	Result.length = 0;
	while(true){
		once = true;
    		while(Tmp.Compare(Tmp1)<0){
                	 if(diff>0) {
				Tmp.CellPlus(A.value[--diff]);
				if(!once) Result.CellPlus(0);
				else once = false;
			 }
               		 else break;
    		}
		//if(diff<1 && Tmp.Compare(Tmp1)<0) break; // ??
		min = 0;
		max = 1 << ((Tmp.PhysLength() - Tmp1.PhysLength() + 1) * 4);
		Tmp2 = Tmp;
		while(true){
		    tmp = (max+min) / 2;
	 		x = Tmp1;
	 		x = x.Mul(tmp);
         		if(x.Compare(Tmp2)<0){
               			if(min != tmp) min = tmp;
	       			    else break;
	 	      	}
         		else if (x.Compare(Tmp2)>0){ // optimal? -local
               			if(max != tmp) max = tmp;
	       			    else break;
           	 	}
                	else {
                        	max = min = tmp;
                        	break;
                	}
    		}
		Tmp = Tmp.Sub(x);
    		Result.CellPlus(tmp);
		if(diff<1 && Tmp.Compare(Tmp1)<0) break;
	}
	Result.negative = negcheck;
	return Result;
}

/*BigInt BigInt::Mod(BigInt x){ // V optimal ?
	bool negcheck,once;	
	int i, diff;
	BigInt A = *this;
	negcheck = negative;
	negative = x.negative = false;
	int check = this->Compare(x);
	if(check<1) {
		if(check == 0) {
			if(!negcheck) A.Clear();
		}
		else {
			if(negcheck) A = x.Sub(A);
		}
		return A;
	}
	BigInt Tmp, Tmp1, Tmp2, Result; // why here ?
	type_double_cell min, max, tmp;
	Tmp1 = x;
	diff = length - x.length; 
	for(i=x.length-1; i>=0; i--)
		Tmp.value[i] = value[i+diff];
	Tmp.length = x.length;
	Result.length = 0;
	while(true){
		once = true;
    		while(Tmp.Compare(Tmp1)<0){
                	 if(diff>0) {
				Tmp.CellPlus(A.value[--diff]);
				if(!once) Result.CellPlus(0);
				else once = false;
			 }
               		 else break;
    		}
		//if(diff<1 && Tmp.Compare(Tmp1)<0) break;
		min = 0;
		max = 1 << ((Tmp.PhysLength() - Tmp1.PhysLength() + 1) * 4);
		Tmp2 = Tmp;
		while(true){
		    tmp = (max+min) / 2; // not over ?
	 		x = Tmp1;
	 		x = x.Mul(tmp);
         		if(x.Compare(Tmp2)<0){
               			if(min != tmp) min = tmp;
	       			    else break;
	 	      	}
         		else if (x.Compare(Tmp2)>0){ // optimal? -local
               			if(max != tmp) max = tmp;
	       			    else break;
           	 	}
                	else {
                	        max = min = tmp;
                	        break;
                	}
    		}
		Tmp = Tmp.Sub(x);
    		Result.CellPlus(tmp);
		if(diff<1 && Tmp.Compare(Tmp1)<0) break;
	}
	A = Tmp;
	if(negcheck) A = Tmp1.Sub(Tmp);
	return A;
}*/

BigInt BigInt::Mod(BigInt x){ // Debug
	BigInt Result, Tmp;
	Result = (*this).Sub(x.Mul((*this).Div(x)));
	return Result;
}

BigInt BigInt::ShiftLeft(unsigned int shift){ // V
	unsigned int cells = (shift/COUNT_ACTIVE_BITS);
	unsigned int rem = shift - cells * COUNT_ACTIVE_BITS;
	unsigned int mask = ((1 << rem) - 1);
	unsigned int maskrev = mask << (COUNT_ACTIVE_BITS - rem);
	type_cell tmp;
	int i;
	BigInt A = *this;

	for(i=capacity-1; i>=length; i--) // optimal? need ?
		A.value[i]=0;
	for(i=A.length-1; i>=0; i--){
		tmp = A.value[i] >> (COUNT_ACTIVE_BITS - rem);
		A.value[i+cells] = (A.value[i] << rem) & MASK_CELL;
		A.value[i+cells+1] |= tmp;
	}
	for(i=cells-1; i>=0; i--)
        	A.value[i] = 0;
    	A.length += cells;
    	if(A.value[A.length]!=0) A.length++;

    return A;
}

BigInt BigInt::ShiftRight(unsigned int shift){ // V
	/*unsigned */int cells = (shift/COUNT_ACTIVE_BITS);
	/*unsigned */int rem = shift - cells * COUNT_ACTIVE_BITS;
	/*unsigned */int mask = ((1 << rem) - 1) << (COUNT_ACTIVE_BITS - rem);
	type_cell tmp;
	int i;
	BigInt A = *this;
	for(i=0; i<A.length; i++){
		tmp = (A.value[i] << (COUNT_ACTIVE_BITS - rem)) & mask;
		if(i-cells >= 0) A.value[i-cells] = A.value[i] >> rem;
		if(i-cells-1 >= 0)
			A.value[i-cells-1] |= tmp;
	}
    	if(A.length > cells) A.length -= cells;
	else A.Clear();
    	if(length > 1 && A.value[A.length-1]==0) A.length--;
	return A;
}

BigInt BigInt::And(BigInt x){ // V optimal ?
    int i;
    BigInt A = (length > x.length) ? *this : x;
    BigInt B = (length > x.length) ? x : *this;
    for(i=0; i<B.length; i++)
	B.value[i] = A.value[i] & B.value[i];
    B.negative = A.negative && B.negative;
    return B;
}

BigInt BigInt::Or(BigInt x){ // V optimal ?
    int i;
    BigInt A = (length > x.length) ? *this : x;
    BigInt B = (length > x.length) ? x : *this;
    for(i=0; i<B.length; i++)
	A.value[i] |= B.value[i];
    A.negative = A.negative || B.negative;
    return A;
}

BigInt BigInt::PowerAndMod(BigInt grade, BigInt mod){ // V optimal ?
    BigInt Result = *this, Tmp, Tmp1, Mod;
    Tmp = *this;
    Result.length = 1;
    Result.value[0] = 1;
    int i,physbitscount = grade.PhysBitsCount();
    for(i=0; i<physbitscount; i++){
	if(grade.At(i)){
		//Tmp1 = Tmp; // -x
        	Result = Result.Mul(Tmp);
		//mod = Mod; // -x
		Result = Result.Mod(mod);
	}
	//Tmp = Tmp1; -x
	//mod = Mod;
	//Tmp1 = Tmp1.Mod(mod);
	//Tmp1 = Tmp1.Mul(Tmp); // -cd1
	Tmp = Tmp.Mul(Tmp);
	//mod = Mod; // -x
	//Tmp1 = Tmp.Mod(mod); // -cd1
	Tmp = Tmp.Mod(mod);
    }
    return Result;
}

BigInt BigInt::GCD(BigInt x){ // V optimal?
	int check;
	BigInt R;
	check = this->Compare(x);
	BigInt A = (check >= 0) ? *this : x; // need change ?
	BigInt B = (check >= 0) ? x : *this;
	while(B.length > 1 || B.value[0]!=0){
		R = A.Mod(B);
		A = B;
		B = R;
	}
	return A;
}

BigInt BigInt::Euclid(BigInt x){
	// match a >= b
	BigInt A(*this), B(x), T, A1(0), B1(1), T1, q, Null;
	while(B.length > 1 || B.value[0]!=0){
		q = A.Div(B);
		T = A.Mod(B);
		T1 = A1.Sub(B1.Mul(q));
		A = B; A1 = B1;
		B = T; B1 = T1;
	}
	if(A1.Compare(Null)<0)
		A1 = A1.Add(*this);
	return A1;
}

bool BigInt::At(unsigned int position){ // V
     if(length<=(position/COUNT_ACTIVE_BITS)) return false;
     return ((value[position/COUNT_ACTIVE_BITS]>>(position%COUNT_ACTIVE_BITS))&1)==1;
}


/*void BigInt::PackToString(type_cell * buffer){ // full? // valid for mysql? // need func ?
	int i;
	buffer[0] = sizeof(type_cell) + length * sizeof(type_cell);
	for(i=0; i<length; i++)
		buffer[i+1] = value[i];
	if(negative) buffer[1] = -buffer[1];
}*/

/*void BigInt::UnPackFromString(type_cell * buffer){ // full? // valid for mysql? // need func ?
	int i;
	length = (buffer[0] - sizeof(type_cell)) / sizeof(type_cell);
	if(buffer[1]<0) buffer[1] = -buffer[1];
	for(i=0; i<length; i++)
		value[i] = buffer[i+1];
}*/

int BigInt::PackToString(char * buffer){ // O
	char * p = buffer;
	int size = sizeof(length), i;
	memcpy(p, &length, sizeof(length));
	p += sizeof(length);
	if(negative) value[0] = -value[0];
	for(i=0; i<length; i++){
		memcpy(p, &value[i], sizeof(type_cell));
		p += sizeof(type_cell);
		size += sizeof(type_cell);
	}
	if(negative) value[0] = -value[0];
}

void BigInt::UnPackFromString(/*int len, */char * buffer){ // O
	char * p = buffer;
	int i;
	//len -= sizeof(length);
	memcpy(&length, p, sizeof(length));
	p += sizeof(length);
	for(i=0; i<length; i++){
		memcpy(&value[i], p, sizeof(type_cell));
		p += sizeof(type_cell);
		//size += sizeof(type_cell); ?
	}
	if(value[0]<0){
		negative = true;
		value[0] = -value[0];
	}
}


string BigInt::Debug(void){ // D
    char *to_convert;
    to_convert = new char[length*COUNT_ACTIVE_DIGIT+2];
    int idx=0,i,j; char tch; bool icheck = false;
    if(negative) to_convert[idx++] = '-';
    i = length-1;
    for(j=COUNT_ACTIVE_DIGIT-1; j>=0; j--){ //First cell
        tch = (value[i] >> (j*4)) & 0xF;
        if(tch > 0 || icheck) {
               if(tch < 10) to_convert[idx++] = tch + 48;
               else to_convert[idx++] = tch + 55;
               icheck = true;
        }
    }
    for(i--; i>=0; i--)
        for(j=COUNT_ACTIVE_DIGIT-1; j>=0; j--){
               tch = (value[i] >> (j*4)) & 0xF;
               if(tch < 10) to_convert[idx++] = tch + 48;
               else to_convert[idx++] = tch + 55;
        }
    if(idx == negative ? 1 : 0) to_convert[idx++] = 48;
    to_convert[idx] = 0;
	string result(to_convert);
	delete [] to_convert;
	return result;
}

void BigInt::SetString(string x){ // V
	parseString(x);
}

void BigInt::GenerateRandomNumber(unsigned int bits){ // O
	int cells, rem, mask, i;
	negative = false;
	//bits = rand()%bits+1;
	cells = (bits/COUNT_ACTIVE_BITS);
	rem = bits - cells * COUNT_ACTIVE_BITS; // optimal?
	mask = (1 << rem);
	//printf("Gen mask cells %d; rem %d : 0x%X\n", cells, rem, mask); // here useless itarations
 	for(i=0; i<cells; i++)
		value[i] = rand()%MASK_CELL;
	if(rem > 0){
		value[cells] = rand()%mask;
		length = cells+1;
	}
	else length = cells;
	if(value[length - 1] == 0 && length > 1) length--; 
}

void BigInt::GenerateRandomSimple(unsigned int bits){
	int attempt = 0;
	BigInt Number, A, D, One(1), Tmp1, Tmp2; // optimal?
	negative = false;
	Number.GenerateRandomNumber(bits); 
	while(attempt < ITERATION_COUNT_FERMA){ // optimal number mod 2 == 0 ?
		A.GenerateRandomNumber(bits);
		Tmp1 = One;
		D = Number;
		D = D.Sub(Tmp1);
		Tmp1 = Number;
		A = A.PowerAndMod(D, Tmp1);
		if(A.Compare(One) != 0){
			Number.GenerateRandomNumber(bits);
			attempt = 0;
		}
		else attempt++;
	}
	*this = Number;
}

void BigInt::CheckSimple(void){
	printf("SimpleCheck %s start!\n", Debug().c_str());
	fflush(stdout);
	BigInt One(1), Tmp(2), I(2), Null, Max;
	Max = *this;
	Max = Max.Div(Tmp);
	Max = Max.Add(One);
	while(I.Compare(Max) < 1){
		Tmp = this->Mod(I);
		if(Tmp.Compare(Null)==0) {
			printf("Number %s is not simple! for %s\n", Debug().c_str(), I.Debug().c_str());
			fflush(stdout);
			return;
		}
		I = I.Add(One);
	}
	printf("Number %s is simple!\n", Debug().c_str());
	fflush(stdout);
}

void BigInt::ConvertDataToBigInt(char * data, int &len, int size, BigInt *Key){ // no supported type_cell <> 2
	int i,cells;
	if(len >= size){
		value[0] = 0;
		length = 1;
		negative = false;
		return;
	}
	length = 0;
	if(Key == NULL) cells = capacity/2;
	else cells = Key->length-2;
	for(i=0; len < size; len++, i++){
		switch(i%3){
			case 0:
				value[length] = data[len];
				if(data[len]<0) value[length] |= 0x80;
				value[length] <<= 4;
				length++;
				if(length == cells) {
					len++;
					value[length] = 0x1; //tada !!
					length++;
					return; // critical place
				}
				break;
			case 1:
				value[length-1] |= (data[len] & 0x70) >> 4;
				if(data[len]<0) value[length-1] |= 0x8;
				value[length] = (data[len] & 0xF) << 8;
				if(len == size-1) length++; // optimal ?
				break;
			case 2:
				value[length] |= data[len] & 0x7F;
				if(data[len]<0) value[length] |= 0x80;
				length++;
				if(length == cells){
					len++;
					value[length] = 0x1; //tada !!
					length++;
					return; // critical place
				}
				break;
		}
	}
	value[length] = 0x1; //tada !!
	length++;
}

void BigInt::ConvertBigIntToData(char * data, int &len, int size){ // sign norm ? // no supported type_cell <> 2
	int i;
	length--;
	//if value[length] == 0x1; //tada !!
	for(i=0; i<length; i++){
		switch(i%2){
			case 0: data[len] = (value[i] & 0x7F0) >> 4;
				if((value[i]&0x800) != 0) data[len] = -data[len];
				//if(len>=size) return;
				len++;
				if(len>=size) return;
				data[len] = (value[i] & 0x7) << 4;
				break;
			case 1: data[len] |= (value[i] & 0xF00) >> 8;
				if((value[i-1]&0x8) != 0) data[len] = -data[len];
				//if(len>=size) return;
				len++;
				if(len>=size) return;
				data[len] = value[i] & 0x7F;
				if((value[i]&0x80) != 0) data[len] = -data[len];
				//if(len>=size) return;
				len++;
				if(len>=size) return;
				break;
		}
	}
}

int BigInt::ToInt(void){
	int result = value[0] & MASK_CELL;
	if(length > 1) result += (value[0] & MASK_CELL) << COUNT_ACTIVE_BITS;
	if(negative) result = -result;
	return result;
}

/*int main(void){
	BigInt A("10000"), B("1A5D215"), C;
	BigInt::InitClass();
	A.CheckSimple();
	//B.CheckSimple();
	C.GenerateRandomSimple(16);
	C.CheckSimple();
	return 0;
}*/

#endif
