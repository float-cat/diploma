#ifndef GROUP_CPP
#define GROUP_CPP

#include "group.hpp"

CardGroup::CardGroup(void){
	root = last = ptr = NULL;
	sorted = false;
}

CardGroup::CardGroup(const CardGroup &src){
	CardNode *p;
	root = last = ptr = NULL;
	sorted = false;
	for(p=src.root; p!=NULL; p=p->next)
		Append(p->card);
	sorted = src.sorted;
}

CardGroup::~CardGroup(void){
	Clear(root);
}

void CardGroup::operator=(const CardGroup &src){
	CardNode *p, *saveroot;
	saveroot = root;
	root = last = ptr = NULL;
	sorted = false;
	for(p=src.root; p!=NULL; p=p->next)
		Append(p->card);
	sorted = src.sorted;
	if(saveroot != NULL) Clear(saveroot);
}

void CardGroup::Append(Card card){
	CardNode *p,*prev;
	if(sorted){
		if(root == NULL){
			root = new CardNode;
			root->card = card;
			root->next = NULL;
			last = root;
			return;
		}
		else if(root->card.GetNominal() > card.GetNominal()){
			p = root;
			root = new CardNode;
			root->next = p;
			root->card = card;
			
		}
		prev = p = root;
		while(p!=NULL){
			if(p->card.GetNominal() > card.GetNominal()){
				prev->next = new CardNode;
				prev->next->card = card;
				prev->next->next = p;
				return;
			}
			prev = p;
			p = p->next;
		}
		prev->next = new CardNode;
		prev->next->card = card;
		prev->next->next = NULL;
	}
	else {
		if(root == NULL) last = root = new CardNode;
		else last = last->next = new CardNode;
		last->next = NULL;
		last->card = card;
	}
}

void CardGroup::Start(void){
	ptr = root;
}

bool CardGroup::IsEnd(void){
	return ptr == NULL;
}

void CardGroup::Next(void){
	ptr = ptr->next;
}

Card &CardGroup::UnderPtr(void){ //link ?
	return ptr->card;
}

bool CardGroup::IsEmpty(void){
	return root == NULL;
}

bool CardGroup::Included(CardGroup &src){
	for(src.Start();!src.IsEnd();src.Next()) // optimal ?
		if(!IsElement(src.UnderPtr())) return false;
	return true;
}

bool CardGroup::IsElement(Card &card){
	for(Start();!IsEnd();Next()) // optimal ?
		if(card.GetNominal() == UnderPtr().GetNominal()) return true;
	return false;
}

void CardGroup::Clear(CardNode *cnptr){
	if(cnptr != NULL){
		Clear(cnptr->next);
		delete cnptr;
	}
}

void CardGroup::Clear(void){
	Clear(root);
	root = last = ptr = NULL;
}

void CardGroup::Cons(CardGroup &src){
	for(src.Start();!src.IsEnd();src.Next())
		if(!IsElement(src.UnderPtr()))
			Append(src.UnderPtr());
}

void CardGroup::Delete(Card &card){ // optimal?
	CardNode *prev;
	prev = root;
	for(Start(); !IsEnd(); Next()){
		if(UnderPtr().GetNominal() == card.GetNominal()){
			if(ptr == root) root = root->next;
			else prev->next = prev->next->next;
			delete ptr;
			break;
		}
		prev = ptr;
	}
}

void CardGroup::Diff(CardGroup &src){
	for(src.Start();!src.IsEnd();src.Next())
		Delete(src.UnderPtr());
}

Cards::Cards(void){
	gridx = 0;
}

Cards::Cards(const Cards &src){
	int i;
	for(i=0;i<4;i++)
		cards[i] = src.cards[i];
}

void Cards::Append(Card card){
	cards[card.GetSuit()].Append(card);
}

void Cards::Start(void){
	gridx = 0;
	while(gridx<4 && cards[gridx].IsEmpty()) gridx++;	
	if(gridx<4) cards[gridx].Start();
}

bool Cards::IsEnd(void){
	return gridx == 4;
}

void Cards::Next(void){
	cards[gridx].Next();
	if(cards[gridx].IsEnd()){
		gridx++;
		while(gridx<4 && cards[gridx].IsEmpty()) gridx++;	
		if(gridx<4) cards[gridx].Start();
	}
}

Card &Cards::UnderPtr(void){
	return cards[gridx].UnderPtr();
}

bool Cards::Included(Cards &src){
	int i;
	for(i=0; i<4; i++)
		if(!cards[i].Included(src.cards[i]))
			return false;
	return true;
}

bool Cards::Equal(Cards &src){
	return Included(src) && src.Included(*this);
}

void Cards::Clear(void){
	int i;
	for(i=0;i<4;i++)
		cards[i].Clear();
}

Cards Cards::Cons(Cards &src){
	int i;
	Cards Result(*this);
	for(i=0;i<4;i++)
		Result.cards[i].Cons(src.cards[i]);
	return Result;
}

Cards Cards::Diff(Cards &src){
	int i;
	Cards Result(*this);
	for(i=0;i<4;i++)
		Result.cards[i].Diff(src.cards[i]);
	return Result;
}

Cards Cards::Cross(Cards &src){
	Cards Result, Tmp;
	Result = this->Cons(src);
	Tmp = this->SymDiff(src);
	Result = Result.Diff(Tmp); // local optimal ?
	return Result;
}

Cards Cards::SymDiff(Cards &src){
	Cards Result, Tmp;
	Tmp = this->Diff(src);
	Result = src.Diff(*this);
	Result = Result.Cons(Tmp); // local optimal ?
	return Result;
}

/*int main(void){
	Cards CG1, CG2, CG3;
	CG1.Append(Card(SUIT_HEARTS, NOMINAL_SIX));
	CG1.Append(Card(SUIT_CLUBS, NOMINAL_SIX));
	CG1.Append(Card(SUIT_HEARTS, NOMINAL_TEN));
	CG1.Append(Card(SUIT_HEARTS, NOMINAL_SEVEN));
	CG1.Append(Card(SUIT_CLUBS, NOMINAL_JACK));
	CG1.Append(Card(SUIT_HEARTS, NOMINAL_KING));
	cout << "CG1:" << endl;
	for(CG1.Start(); !CG1.IsEnd(); CG1.Next())
		CG1.UnderPtr().DebugPrintName();
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_SIX));
	CG2.Append(Card(SUIT_CLUBS, NOMINAL_SIX));
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_KING));
	cout << "CG2:" << endl;
	for(CG2.Start(); !CG2.IsEnd(); CG2.Next())
		CG2.UnderPtr().DebugPrintName();
	if(CG1.Included(CG2)) cout << "CG1 soderzhit CG2" << endl;
	else cout << "CG1 ne soderzhit CG2" << endl;
	CG2.Clear();
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_SIX));
	CG2.Append(Card(SUIT_CLUBS, NOMINAL_SIX));
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_TEN));
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_SEVEN));
	CG2.Append(Card(SUIT_CLUBS, NOMINAL_JACK));
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_KING));
	if(CG1.Equal(CG2)) cout << "CG1 ravno CG2" << endl;
	else cout << "CG1 ne ravno CG2" << endl;
	CG2.Clear();
	CG2.Append(Card(SUIT_SPADES, NOMINAL_SIX));
	CG2.Append(Card(SUIT_SPADES, NOMINAL_SEVEN));
	CG2.Append(Card(SUIT_DIAMONDS, NOMINAL_SEVEN));
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_QUEEN));
	cout << "CG2:" << endl;
	for(CG2.Start(); !CG2.IsEnd(); CG2.Next())
		CG2.UnderPtr().DebugPrintName();
	CG1 = CG1.Cons(CG2);
	cout << "CG1 cons CG2" << endl;
	for(CG1.Start(); !CG1.IsEnd(); CG1.Next())
		CG1.UnderPtr().DebugPrintName();
	//razn
	CG2.Clear();
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_SEVEN));
	CG2.Append(Card(SUIT_CLUBS, NOMINAL_JACK));
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_KING));
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_ACE));
	cout << "CG2:" << endl;
	for(CG2.Start(); !CG2.IsEnd(); CG2.Next())
		CG2.UnderPtr().DebugPrintName();
	CG3 = CG1.Diff(CG2);
	cout << "CG1 diff CG2" << endl;
	for(CG3.Start(); !CG3.IsEnd(); CG3.Next())
		CG3.UnderPtr().DebugPrintName();
	//peresech
	CG1.Clear();
	CG1.Append(Card(SUIT_HEARTS, NOMINAL_EIGHT));
	CG1.Append(Card(SUIT_CLUBS, NOMINAL_JACK));
	CG1.Append(Card(SUIT_HEARTS, NOMINAL_KING));
	CG1.Append(Card(SUIT_HEARTS, NOMINAL_QUEEN));
	cout << "CG1:" << endl;
	for(CG1.Start(); !CG1.IsEnd(); CG1.Next())
		CG1.UnderPtr().DebugPrintName();
	CG2.Clear();
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_SEVEN));
	CG2.Append(Card(SUIT_CLUBS, NOMINAL_JACK));
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_KING));
	CG2.Append(Card(SUIT_HEARTS, NOMINAL_ACE));
	cout << "CG2:" << endl;
	for(CG2.Start(); !CG2.IsEnd(); CG2.Next())
		CG2.UnderPtr().DebugPrintName();
	CG3 = CG1.Cross(CG2);
	cout << "CG1 cross CG2" << endl;
	for(CG3.Start(); !CG3.IsEnd(); CG3.Next())
		CG3.UnderPtr().DebugPrintName();
	CG3 = CG1.SymDiff(CG2);
	cout << "CG1 symdiff CG2" << endl;
	for(CG3.Start(); !CG3.IsEnd(); CG3.Next())
		CG3.UnderPtr().DebugPrintName();
	return 0;
}*/

#endif
