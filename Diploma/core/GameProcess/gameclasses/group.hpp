#ifndef GROUP_HPP
#define GROUP_HPP

#include <stdio.h>
#include <stdlib.h>

#include "card.hpp"

class CardGroup;
class Cards;

class CardNode {
 friend class CardGroup;
	Card card;
	CardNode *next;
};

class CardGroup {
 friend class Cards;
	bool sorted;
	CardNode *root, *last, *ptr;
	CardGroup(const CardGroup &src);
	CardGroup(void);
	~CardGroup(void);
	void operator=(const CardGroup &src);
	void Append(Card card);
	void Start(void);
	bool IsEnd(void);
	void Next(void);
	Card &UnderPtr(void);
	bool IsEmpty(void);
	bool Included(CardGroup &src);
	bool IsElement(Card &card);
	void Clear(CardNode *cnptr);
	void Clear(void);
	void Cons(CardGroup &src);
	void Delete(Card &card); // optimal?
	void Diff(CardGroup &src);
};

class Cards {
	CardGroup cards[4];
	int gridx;
 public:
	Cards(void);
	Cards(const Cards &src);
	void Append(Card card);
	void Start(void);
	bool IsEnd(void);
	void Next(void);
	Card &UnderPtr(void);
	bool Included(Cards &src);
	bool Equal(Cards &src);
	void Clear(void);
	Cards Cons(Cards &src);
	Cards Diff(Cards &src);
	Cards Cross(Cards &src);
	Cards SymDiff(Cards &src);
};

#endif //GROUP_HPP
