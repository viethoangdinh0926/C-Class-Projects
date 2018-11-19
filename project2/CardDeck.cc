/*
 * CardDeck.cc
 *
 * Implements static arrays and all classes.
 *
 * Author: Viet Dinh
 * Date: 11/19/2016
 */

#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <typeinfo>
#include "CardDeck.h"
#include "md5.h"

using namespace std;

//Spade<->1, Heart<->2, Diamon<->3, Club<->4
int Card::suits[] = {1, 2 ,3 ,4};
//From Ace to King
int Card::faces[] = { 14, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };

int Card::getSuit() const {
	return suit;
}

int Card::getFace() const {
	return face;
}

string Card::toString(){
	string suit_str, face_str;
	switch (suit){
	case 1:
		suit_str = "Spade(1)";
		break;
	case 2:
		suit_str = "Heart(2)";
		break;
	case 3:
		suit_str = "Diamond(3)";
		break;
	default:
		suit_str = "Club(4)";
		break;
	}
	switch (face){
	case 14:
		face_str = "Ace(1)";
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		face_str = to_string(face);
		break;
	case 11:
		face_str = "Jack(11)";
		break;
	case 12:
		face_str = "Queen(12)";
		break;
	default:
		face_str = "King(13)";
		break;
	}
	return suit_str + "-" + face_str;
}

DeckOfCards::DeckOfCards(){
	currentCard = 1;
	for (int i = 0; i < SUIT_NUM; ++i){
		for (int j = 0; j < SUIT_CARD_NUM; ++j){
			Card tempCard(Card::suits[i], Card::faces[j]);
			deck.push_back(tempCard);
		}
	}
}

Card &DeckOfCards::dealCard(){
	if (!moreCards()){
		throw 1;
	}
	++currentCard;
	return deck[currentCard - 2];
};

//randomly shuffles card deck
//gets current time in miliseconds, converts it to string, gets hash of the string by md5 function
//sums all charactors in the hash
//takes remainder by dividing the sum by 52
void DeckOfCards::shuffle(){
	int temp = 0;
	string hash;
	Card tempCard;
	for (int i = 0; i < ALL_CARD_NUM; ++i)
	{
		hash = md5(to_string(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count()));
		for (int j = 0; j < hash.length(); ++j){
			temp += hash.at(j);
		}
		temp %= 52;
		while (temp == i){
			hash = md5(to_string(chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now().time_since_epoch()).count()));
			for (int j = 0; j < hash.length(); ++j){
				temp += hash.at(j);
			}
			temp %= 52;
		};
		tempCard = deck[i];
		deck[i] = deck[temp];
		deck[temp] = tempCard;
	}	
}