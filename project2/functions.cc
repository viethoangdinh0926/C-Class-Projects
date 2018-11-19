/*
* functions.cc
*
* Implements global functions
*
* Author: Viet Dinh
* Date: 11/19/2016
*/

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include "CardDeck.h"

using namespace std;

vector<Card> deal_a_five_cards(DeckOfCards &deck){
	vector<Card> tempVec;
	for (int i = 0; i < 5; ++i){
		tempVec.push_back(deck.dealCard());
	}
	return tempVec;
}

void sort_card_hand(vector<Card> &five_card_hand){
	//only works on a 5-card hands
	if (five_card_hand.size() != 5){
		throw 2;
	}
	for (int i = 1; i < 5; ++i){
		int j = i - 1;
		while (five_card_hand[j].getFace() < five_card_hand[i].getFace()){
			--j;
		}
		if (j + 1 != i && j >= 0){
			Card tempC = five_card_hand[i];
			for (int k = i; k >= j + 2; --k){
				five_card_hand[k] = five_card_hand[k - 1];
			}
			five_card_hand[j + 1] = tempC;
		}
		else if (j < 0){
			Card tempC = five_card_hand[i];
			for (int k = i; k > 0; --k){
				five_card_hand[k] = five_card_hand[k - 1];
			}
			five_card_hand[0] = tempC;
		}
	}
}

vector<Card> royal_flush(const vector<Card> &five_card_hand){
	vector<Card> tempVec;
	//checks if all cards are in same suit
	bool suit_equal = true;
	for (int i = 0; i < 4; ++i){
		suit_equal = suit_equal && (five_card_hand[i].getSuit() == five_card_hand[i + 1].getSuit());
		if (!suit_equal) return tempVec;
	}

	//check if the 5-card hand is a royal straight flush
	bool is_royal_flush = true;
	is_royal_flush = is_royal_flush && five_card_hand[0].getFace() == 14;
	is_royal_flush = is_royal_flush && five_card_hand[1].getFace() == 13;
	is_royal_flush = is_royal_flush && five_card_hand[2].getFace() == 12;
	is_royal_flush = is_royal_flush && five_card_hand[3].getFace() == 11;
	is_royal_flush = is_royal_flush && five_card_hand[4].getFace() == 10;
	if (is_royal_flush){
		tempVec = five_card_hand;
	}
	return tempVec;
}

vector<Card> straight_flush(const vector<Card> &five_card_hand){
	vector<Card> tempVec;
	//checks if all cards are in same suit
	bool suit_equal = true;
	for (int i = 0; i < 4; ++i){
		suit_equal = suit_equal && (five_card_hand[i].getSuit() == five_card_hand[i + 1].getSuit());
		if (!suit_equal) return tempVec;
	}


	//checks if the 5-card hand is a straight flush
	
	if (five_card_hand[0].getFace() == 14 &&
		five_card_hand[1].getFace() == 5 &&
		five_card_hand[2].getFace() == 4 &&
		five_card_hand[3].getFace() == 3 &&
		five_card_hand[3].getFace() == 2){
		tempVec = five_card_hand;
	}
	else{
		bool is_sf = true;
		for (int i = 0; i < 4; ++i){
			if (five_card_hand[i].getFace() - 1 != five_card_hand[i + 1].getFace()){
				is_sf = false;
				break;
			}
		}
		if (is_sf){
			tempVec = five_card_hand;
		}
	}

	return tempVec;
}

vector<Card> four_of_a_kind(const vector<Card> &five_card_hand){
	vector<Card> tempVec;

	if (five_card_hand[0].getFace() == five_card_hand[1].getFace() && 
		five_card_hand[1].getFace() == five_card_hand[2].getFace() &&
		five_card_hand[2].getFace() == five_card_hand[3].getFace()){
		tempVec = five_card_hand;
	}
	else if (five_card_hand[1].getFace() == five_card_hand[2].getFace() && 
		five_card_hand[2].getFace() == five_card_hand[3].getFace() &&
		five_card_hand[3].getFace() == five_card_hand[4].getFace()){
		//moves the four to the front of 5-card hand
		for (int i = 0; i < 5; ++i){
			tempVec.push_back(five_card_hand[4 - i]);
		}
	}
	
	return tempVec;
}

vector<Card> full_house(const vector<Card> &five_card_hand){
	vector<Card> tempVec;

	//checks the list to find if there is a full house
	if (five_card_hand[0].getFace() == five_card_hand[1].getFace() && 
		five_card_hand[1].getFace() == five_card_hand[2].getFace() &&
		five_card_hand[3].getFace() == five_card_hand[4].getFace()){
		tempVec = five_card_hand;
	}
	else if (five_card_hand[2].getFace() == five_card_hand[3].getFace() &&
		five_card_hand[3].getFace() == five_card_hand[4].getFace() &&
		five_card_hand[0].getFace() == five_card_hand[1].getFace()){
		for (int i = 0; i < 5; ++i){
			tempVec.push_back(five_card_hand[4 - i]);
		}
	}
	
	return tempVec;
}

vector<Card> flush(const vector<Card> &five_card_hand){
	vector<Card> tempVec;
	//checks if all cards are in same suit
	bool suit_equal = true;
	for (int i = 0; i < 4; ++i){
		suit_equal = suit_equal && (five_card_hand[i].getSuit() == five_card_hand[i + 1].getSuit());
		if (!suit_equal) return tempVec;//no flush found
	}

	//builds vector for the flush
	tempVec = five_card_hand;
	
	return tempVec;
}

vector<Card> straight(const vector<Card> &five_card_hand){
	vector<Card> tempVec;

	//check if the 5-card hand is a highest straight
	
	if (five_card_hand[0].getFace() == 14 &&
		five_card_hand[1].getFace() == 5 &&
		five_card_hand[2].getFace() == 4 &&
		five_card_hand[3].getFace() == 3 &&
		five_card_hand[4].getFace() == 2){
		tempVec = five_card_hand;
	}
	else {
		bool is_top_straight_flush = true;
		for (int i = 0; i < 5; ++i){
			if (five_card_hand[i].getFace() - 1 != five_card_hand[i + 1].getFace()){
				is_top_straight_flush = false;
				break;
			}
		}
		if (is_top_straight_flush){
			tempVec = five_card_hand;
		}
	}
	
	return tempVec;
}

vector<Card> three_of_a_kind(const vector<Card> &five_card_hand){
	vector<Card> tempVec;

	//checks the list to find if there is a three-of-a-kind
	if (five_card_hand[0].getFace() == five_card_hand[1].getFace() && 
		five_card_hand[1].getFace() == five_card_hand[2].getFace()){
		tempVec = five_card_hand;
	}
	else if (five_card_hand[1].getFace() == five_card_hand[2].getFace() && 
		five_card_hand[2].getFace() == five_card_hand[3].getFace()){
		tempVec.push_back(five_card_hand[1]);
		tempVec.push_back(five_card_hand[2]);
		tempVec.push_back(five_card_hand[3]);
		tempVec.push_back(five_card_hand[0]);
		tempVec.push_back(five_card_hand[4]);
	}
	else if (five_card_hand[2].getFace() == five_card_hand[3].getFace() &&
		five_card_hand[3].getFace() == five_card_hand[4].getFace()){
		tempVec.push_back(five_card_hand[2]);
		tempVec.push_back(five_card_hand[3]);
		tempVec.push_back(five_card_hand[4]);
		tempVec.push_back(five_card_hand[0]);
		tempVec.push_back(five_card_hand[1]);
	}
	
	return tempVec;
}

vector<Card> two_pair(const vector<Card> &five_card_hand){
	vector<Card> tempVec;

	//checks the list to find if there is a two-pair
	if (five_card_hand[0].getFace() == five_card_hand[1].getFace() && 
		five_card_hand[2].getFace() == five_card_hand[3].getFace()){
		tempVec = five_card_hand;
	}
	//moves the two pairs to the front of the 5-card hand (single-pair-pair)
	else if (five_card_hand[1].getFace() == five_card_hand[2].getFace() &&
		five_card_hand[3].getFace() == five_card_hand[4].getFace()){
		tempVec.push_back(five_card_hand[1]);
		tempVec.push_back(five_card_hand[2]);
		tempVec.push_back(five_card_hand[3]);
		tempVec.push_back(five_card_hand[4]);
		tempVec.push_back(five_card_hand[0]);
	}
	//moves the two pairs to the front of the 5-card hand (pair-single-pair)
	else if (five_card_hand[0].getFace() == five_card_hand[1].getFace() &&
		five_card_hand[3].getFace() == five_card_hand[4].getFace()){
		tempVec.push_back(five_card_hand[0]);
		tempVec.push_back(five_card_hand[1]);
		tempVec.push_back(five_card_hand[3]);
		tempVec.push_back(five_card_hand[4]);
		tempVec.push_back(five_card_hand[2]);
	}

	return tempVec;
}

vector<Card> pair_card(const vector<Card> &five_card_hand){
	vector<Card> tempVec;

	if (five_card_hand[0].getFace() == five_card_hand[1].getFace()){
		tempVec = five_card_hand;
	}
	//moves the pair to the front of the 5-card hand (single-pair-single-single)
	else if (five_card_hand[1].getFace() == five_card_hand[2].getFace()){
		tempVec.push_back(five_card_hand[1]);
		tempVec.push_back(five_card_hand[2]);
		tempVec.push_back(five_card_hand[0]);
		tempVec.push_back(five_card_hand[3]);
		tempVec.push_back(five_card_hand[4]);
	}
	//moves the pair to the front of the 5-card hand (single-single-pair-single)
	else if (five_card_hand[2].getFace() == five_card_hand[3].getFace()){
		tempVec.push_back(five_card_hand[2]);
		tempVec.push_back(five_card_hand[3]);
		tempVec.push_back(five_card_hand[0]);
		tempVec.push_back(five_card_hand[1]);
		tempVec.push_back(five_card_hand[4]);
	}
	//(single - single - single - pair)
	else if (five_card_hand[3].getFace() == five_card_hand[4].getFace()){
		tempVec.push_back(five_card_hand[3]);
		tempVec.push_back(five_card_hand[4]);
		tempVec.push_back(five_card_hand[0]);
		tempVec.push_back(five_card_hand[1]);
		tempVec.push_back(five_card_hand[2]);
	}

	return tempVec;
}

vector<Card> sort_normal_hand(const vector<Card> &five_card_hand){
	return five_card_hand;
}

vector<Card> sort_card_hand_and_get_type(const std::vector<Card> &five_card_hand, int &type){
	//only works on a 5-card hands
	if (five_card_hand.size() != 5){
		throw 2;
	}
	vector<Card> temp;
	temp = royal_flush(five_card_hand);
	if(temp.size() == 0){
		temp = straight_flush(five_card_hand);
		if (temp.size() == 0){
			temp = four_of_a_kind(five_card_hand);
			if (temp.size() == 0){
				temp = full_house(five_card_hand);
				if (temp.size() == 0){
					temp = flush(five_card_hand);
					if (temp.size() == 0){
						temp = straight(five_card_hand);
						if (temp.size() == 0){
							temp = three_of_a_kind(five_card_hand);
							if (temp.size() == 0){
								temp = two_pair(five_card_hand);
								if (temp.size() == 0){
									temp = pair_card(five_card_hand);
									if (temp.size() == 0){
										type = 9;
										temp = sort_normal_hand(five_card_hand);
										//cout << "Normal 5-card hand found." << endl;
									}
									else{
										type = 8;
										//cout << "A pair found." << endl;
									}
								}
								else{
									type = 7;
									//cout << "A two-pair found." << endl;
								}
							}
							else{
								type = 6;
								//cout << "A three-of-a-kind found." << endl;
							}
						}
						else{
							type = 5;
							//cout << "A straight found." << endl;
						}
					}
					else{
						type = 4;
						//cout << "A flush found." << endl;
					}
				}
				else{
					type = 3;
					//cout << "A full-house found." << endl;
				}
			}
			else{
				type = 2;
				//cout << "A four-of-a-kind found." << endl;
			}
		}
		else{
			type = 1;
			//cout << "A straight-flush found." << endl;
		}
	}
	else{
		type = 0;
		//cout << "A royal-flush found." << endl;
	}
	return temp;
}

bool draw_more_card(const vector<Card> &five_card_hand, const int &type){
	if (type == 0){
		return false;
	}
	else if (type == 1){
		return true;
	}
	else if (type == 2){
		if (five_card_hand[0].getFace() == 14 && five_card_hand[4].getFace() == 13){
			return false;
		}
		else{
			return true;
		}
	}
	else if (type == 3){
		if (five_card_hand[0].getFace() == 14 && five_card_hand[4].getFace() == 13){
			return false;
		}
		else{
			return true;
		}
	}
	else if (type == 4){
		return false;
	}
	else if (type == 5){
		if (five_card_hand[0].getFace() == 14 && five_card_hand[4].getFace() == 13){
			return false;
		}
		else{
			return true;
		}
	}
	else if (type == 6){
		return true;
	}
	else if (type == 7){
		return true;
	}
	else if (type == 8){
		return true;
	}
	else if (type == 9){
		return true;
	}
	else{
		throw 5;
	}
}

void fix_straight_flush(vector<Card> &five_card_hand, const Card &nextCard, int &type){
	if (five_card_hand[0].getFace() == 14 &&
		nextCard.getFace() == 6 &&
		nextCard.getSuit() == five_card_hand[0].getSuit()){
		five_card_hand[0] = nextCard;
		type = 0;
	}
	else if (five_card_hand[0].getFace() + 1 == nextCard.getFace() &&
		nextCard.getSuit() == five_card_hand[0].getSuit()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = five_card_hand[2];
		five_card_hand[2] = five_card_hand[1];
		five_card_hand[1] = five_card_hand[0];
		five_card_hand[0] = nextCard;
		type = 0;
	}
}
void fix_four_of_a_kind(vector<Card> &five_card_hand, const Card &nextCard, int &type){
	if (nextCard.getFace() > five_card_hand[4].getFace()){
		five_card_hand[4] = nextCard;
	}
}
void fix_full_house(vector<Card> &five_card_hand, const Card &nextCard, int &type){
	if (nextCard.getFace() == five_card_hand[2].getFace()){
		five_card_hand[3] = nextCard;
		type = 2;//four-of-a-kind
	}
	else if (nextCard.getFace() == five_card_hand[3].getFace() &&
		five_card_hand[3].getFace() > five_card_hand[2].getFace()){
		five_card_hand[2] = nextCard;
		five_card_hand.push_back(five_card_hand[0]);
		five_card_hand.push_back(five_card_hand[1]);
		five_card_hand.erase(five_card_hand.begin());
		five_card_hand.erase(five_card_hand.begin());
	}
}
/*
void fix_flush(vector<Card> &five_card_hand, const Card &nextCard, int &type){

}
*/
void fix_straight(vector<Card> &five_card_hand, const Card &nextCard, int &type){
	vector<Card> temp;
	int different_index;
	for(int i = 0; i < 5; ++i){
		int count = 0;
		for(int j = 0; j < 5; ++j){
			if(i != j && five_card_hand[i].getSuit() == five_card_hand[j].getSuit()){
				++count;
			}
		}
		if(count == 3){
			temp.push_back(five_card_hand[i]);
		}
		else{
			different_index = i;
		}
	}
	if(temp.size() == 4){
		five_card_hand[different_index] = nextCard;
		sort_card_hand(five_card_hand);
		type = 4;//flush
	}
	else if(nextCard.getFace() == 6 && 
		five_card_hand[0].getFace() == 14 &&
		five_card_hand[1].getFace() == 5){
		five_card_hand[0] = nextCard;
	}
	else if (nextCard.getFace() == five_card_hand[0].getFace() + 1){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = five_card_hand[2];
		five_card_hand[2] = five_card_hand[1];
		five_card_hand[1] = five_card_hand[0];
		five_card_hand[0] = nextCard;
	}
}
void fix_three_of_a_kind(vector<Card> &five_card_hand, const Card &nextCard, int &type){
	if (nextCard.getFace() == five_card_hand[2].getFace()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = nextCard;
		type = 2;//four-of-a-kind
	}
	else if (nextCard.getFace() == five_card_hand[3].getFace()){
		five_card_hand[4] = nextCard;
		type = 3;//full-house
	}
	else if (nextCard.getFace() == five_card_hand[4].getFace()){
		five_card_hand[3] = nextCard;
		type = 3;//full-house
	}
	else{
		vector<Card> temp;
		int different_index;
		for(int i = 0; i < 5; ++i){
			int count = 0;
			for(int j = 0; j < 5; ++j){
				if(i != j && five_card_hand[i].getSuit() == five_card_hand[j].getSuit()){
					++count;
				}
			}
			if(count == 3){
				temp.push_back(five_card_hand[i]);
			}
			else{
				different_index = i;
			}
		}
		if(temp.size() == 4){
			five_card_hand[different_index] = nextCard;
			sort_card_hand(five_card_hand);
			type = 4;//flush
		}
		else if (nextCard.getFace() > five_card_hand[3].getFace()){
			five_card_hand[4] = five_card_hand[3];
			five_card_hand[3] = nextCard;
		}
		else if (nextCard.getFace() > five_card_hand[4].getFace()){
			five_card_hand[4] = nextCard;
		}
	}
}
void fix_two_pair(vector<Card> &five_card_hand, const Card &nextCard, int &type){
	if (five_card_hand[1].getFace() == nextCard.getFace()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[2] = nextCard;
		type = 3;//full-house
	}
	else if (five_card_hand[2].getFace() == nextCard.getFace()){
		five_card_hand[4] = nextCard;
		five_card_hand.push_back(five_card_hand[0]);
		five_card_hand.push_back(five_card_hand[1]);
		five_card_hand.erase(five_card_hand.begin());
		five_card_hand.erase(five_card_hand.begin());
		type = 3;//full-house
	}
	else{
		vector<Card> temp;
		int different_index;
		for(int i = 0; i < 5; ++i){
			int count = 0;
			for(int j = 0; j < 5; ++j){
				if(i != j && five_card_hand[i].getSuit() == five_card_hand[j].getSuit()){
					++count;
				}
			}
			if(count == 3){
				temp.push_back(five_card_hand[i]);
			}
			else{
				different_index = i;
			}
		}
		if(temp.size() == 4){
			five_card_hand[different_index] = nextCard;
			sort_card_hand(five_card_hand);
			type = 4;//flush
		}
		else if (five_card_hand[4].getFace() == nextCard.getFace()){
			if (nextCard.getFace() > five_card_hand[1].getFace()){
				Card tempC = five_card_hand[4];
				five_card_hand[4] = five_card_hand[3];
				five_card_hand[3] = five_card_hand[1];
				five_card_hand[2] = five_card_hand[0];
				five_card_hand[1] = tempC;
				five_card_hand[0] = nextCard;
			}
			else if (nextCard.getFace() > five_card_hand[3].getFace()){
				Card tempC = five_card_hand[4];
				five_card_hand[4] = five_card_hand[3];
				five_card_hand[3] = tempC;
				five_card_hand[2] = nextCard;
			}
		}
		else if (five_card_hand[4].getFace() < nextCard.getFace()){
			five_card_hand[4] = nextCard;
		}
	}
}
void fix_one_pair(vector<Card> &five_card_hand, const Card &nextCard, int &type){
	vector<Card> temp;
	int different_index;
	for(int i = 0; i < 5; ++i){
		int count = 0;
		for(int j = 0; j < 5; ++j){
			if(i != j && five_card_hand[i].getSuit() == five_card_hand[j].getSuit()){
				++count;
			}
		}
		if(count == 3){
			temp.push_back(five_card_hand[i]);
		}
		else{
			different_index = i;
		}
	}
	if(temp.size() == 4){
		five_card_hand[different_index] = nextCard;
		sort_card_hand(five_card_hand);
		type = 4;//flush
	}
	else if (five_card_hand[1].getFace() == nextCard.getFace()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = five_card_hand[2];
		five_card_hand[2] = nextCard;
		type = 6;//three-of-a-kind
	}
	else if (five_card_hand[2].getFace() == nextCard.getFace()){
		if (nextCard.getFace() > five_card_hand[1].getFace()){
			five_card_hand[4] = five_card_hand[3];
			five_card_hand[3] = five_card_hand[1];
			five_card_hand[1] = nextCard;
			Card tempC = five_card_hand[2];
			five_card_hand[2] = five_card_hand[0];
			five_card_hand[0] = tempC;	
		}
		else{
			five_card_hand[4] = five_card_hand[3];
			five_card_hand[3] = nextCard;
		}
		type = 7;//2 pairs
	}
	else if (five_card_hand[3].getFace() == nextCard.getFace()){
		if (nextCard.getFace() > five_card_hand[1].getFace()){
			five_card_hand[4] = five_card_hand[2];
			five_card_hand[2] = five_card_hand[0];
			five_card_hand[0] = nextCard;
			Card tempC = five_card_hand[1];
			five_card_hand[1] = five_card_hand[3];
			five_card_hand[3] = tempC;
		}
		else{
			five_card_hand[4] = five_card_hand[2];
			five_card_hand[2] = nextCard;
		}
		type = 7;//2 pairs
	}
	else if (five_card_hand[4].getFace() == nextCard.getFace()){
		if (nextCard.getFace() > five_card_hand[1].getFace()){
			five_card_hand[3] = five_card_hand[1];
			five_card_hand[1] = nextCard;
			Card tempC = five_card_hand[3];
			five_card_hand[4] = five_card_hand[2];
			five_card_hand[2] = five_card_hand[0];
			five_card_hand[0] = tempC;
			
		}
		else{
			Card tempC = five_card_hand[4];
			five_card_hand[4] = five_card_hand[2];
			five_card_hand[2] = nextCard;
			five_card_hand[3] = tempC;
		}
		type = 7;//2 pairs
	}
	else if (five_card_hand[2].getFace() < nextCard.getFace()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = five_card_hand[2];
		five_card_hand[2] = nextCard;
	}
	else if (five_card_hand[3].getFace() < nextCard.getFace()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = nextCard;
	}
	else if (five_card_hand[4].getFace() < nextCard.getFace()){
		five_card_hand[4] = nextCard;
	}
}
void fix_normal_combination(vector<Card> &five_card_hand, const Card &nextCard, int &type){
	vector<Card> temp;
	int different_index;
	for(int i = 0; i < 5; ++i){
		int count = 0;
		for(int j = 0; j < 5; ++j){
			if(i != j && five_card_hand[i].getSuit() == five_card_hand[j].getSuit()){
				++count;
			}
		}
		if(count == 3){
			temp.push_back(five_card_hand[i]);
		}
		else{
			different_index = i;
		}
	}
	if(temp.size() == 4){
		five_card_hand[different_index] = nextCard;
		sort_card_hand(five_card_hand);
		type = 4;//flush
	}
	else if (five_card_hand[0].getFace() == nextCard.getFace()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = five_card_hand[2];
		five_card_hand[2] = five_card_hand[1];
		five_card_hand[1] = nextCard;
		type = 8;//1 pair
	}
	else if (five_card_hand[1].getFace() == nextCard.getFace()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = five_card_hand[2];
		five_card_hand[2] = five_card_hand[0];
		five_card_hand[0] = nextCard;
		type = 8;//1 pair
	}
	else if (five_card_hand[2].getFace() == nextCard.getFace()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = five_card_hand[1];
		five_card_hand[1] = nextCard;
		Card tempC = five_card_hand[2];
		five_card_hand[2] = five_card_hand[0];
		five_card_hand[0] = tempC;
		type = 8;//1 pair
	}
	else if (five_card_hand[3].getFace() == nextCard.getFace()){
		five_card_hand[4] = five_card_hand[2];
		five_card_hand[2] = five_card_hand[0];
		five_card_hand[0] = nextCard;
		Card tempC = five_card_hand[3];
		five_card_hand[3] = five_card_hand[1];
		five_card_hand[1] = tempC;
		type = 8;//1 pair
	}
	else if (five_card_hand[4].getFace() == nextCard.getFace()){
		five_card_hand[3] = five_card_hand[1];
		five_card_hand[1] = nextCard;
		Card tempC = five_card_hand[4];
		five_card_hand[4] = five_card_hand[2];
		five_card_hand[2] = five_card_hand[0];
		five_card_hand[0] = tempC;
		type = 8;//1 pair
	}
	else if (five_card_hand[0].getFace() < nextCard.getFace()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = five_card_hand[2];
		five_card_hand[2] = five_card_hand[1];
		five_card_hand[1] = five_card_hand[0];
		five_card_hand[0] = nextCard;
	}
	else if (five_card_hand[1].getFace() < nextCard.getFace()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = five_card_hand[2];
		five_card_hand[2] = five_card_hand[1];
		five_card_hand[1] = nextCard;
	}
	else if (five_card_hand[2].getFace() < nextCard.getFace()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = five_card_hand[2];
		five_card_hand[2] = nextCard;
	}
	else if (five_card_hand[3].getFace() < nextCard.getFace()){
		five_card_hand[4] = five_card_hand[3];
		five_card_hand[3] = nextCard;
	}
	else if (five_card_hand[4].getFace() < nextCard.getFace()){
		five_card_hand[4] = nextCard;
	}
}

void fix_general_combination(vector<Card> &five_card_hand, const Card &nextCard, int &type){
	//only works on a 5-card hands
	if (five_card_hand.size() != 5){
		throw 2;
	}

	switch (type){
	case 0:
		break;
	case 1:
		fix_straight_flush(five_card_hand, nextCard, type);
		break;
	case 2:
		fix_four_of_a_kind(five_card_hand, nextCard, type);
		break;
	case 3:
		fix_full_house(five_card_hand, nextCard, type);
		break;
	case 4:
		//fix_flush(five_card_hand, nextCard, type);
		break;
	case 5:
		fix_straight(five_card_hand, nextCard, type);
		break;
	case 6:
		fix_three_of_a_kind(five_card_hand, nextCard, type);
		break;
	case 7:
		fix_two_pair(five_card_hand, nextCard, type);
		break;
	case 8:
		fix_one_pair(five_card_hand, nextCard, type);
		break;
	case 9:
		fix_normal_combination(five_card_hand, nextCard, type);
		break;
	default:
		throw 6;
		break;
	}
}

const vector<Card> &better_5_hand_card(const int &type_a, const vector<Card> &a, const int &type_b, const vector<Card> &b){
	//only works on 2 5-card hands
	if (a.size() != b.size() || a.size() != 5){
		throw 2;
	}

	if (type_a != type_b){
		return type_a > type_b ? b : a;
	}


	bool a_greater, check;
	a_greater = check = false;
	if (type_a == 0){
		throw 4;
	}
	else if (type_a == 1){
		if (a[0].getFace() == 14 && b[0].getFace() == 14){
			throw 4;
		}
		else if (a[0].getFace() == 14){
			a_greater = false;
		}
		else if (b[0].getFace() == 14){

		}
		else{
			for (int i = 0; i < 5; ++i){
				if (a[i].getFace() > b[i].getFace()){
					a_greater = true;
					check = true;
					break;
				}
				else if (a[i].getFace() < b[i].getFace()){
					check = true;
					break;
				}
			}
			if (!check) throw 4;
		}

		return a_greater ? a : b;
	}
	else if (type_a == 2){
		for (int i = 3; i < 5; ++i){
			if (a[i].getFace() > b[i].getFace()){
				a_greater = true;
				check = true;
				break;
			}
			else if (a[i].getFace() < b[i].getFace()){
				check = true;
				break;
			}
		}
		if (!check) throw 4;

		return a_greater ? a : b;
	}
	else if (type_a == 3){
		for (int i = 2; i < 4; ++i){
			if (a[i].getFace() > b[i].getFace()){
				a_greater = true;
				check = true;
				break;
			}
			else if (a[i].getFace() < b[i].getFace()){
				check = true;
				break;
			}
		}
		if (!check) throw 4;

		return a_greater ? a : b;
	}
	else if (type_a == 4){

		for (int i = 0; i < 5; ++i){
			if (a[i].getFace() > b[i].getFace()){
				a_greater = true;
				check = true;
				break;
			}
			else if (a[i].getFace() < b[i].getFace()){
				check = true;
				break;
			}
		}
		if (!check) throw 4;

		return a_greater ? a : b;
	}
	else if (type_a == 5){

		if (a[0].getFace() == 14 && 
			b[0].getFace() == 14 &&
			a[1].getFace() == 5 &&
			b[1].getFace() == 5){
			throw 4;
		}
		else if (b[0].getFace() == 14 && b[1].getFace() == 5){
			a_greater = true;
		}
		else if (a[0].getFace() == 14 && a[1].getFace() == 5){

		}
		else{
			for (int i = 0; i < 5; ++i){
				if (a[i].getFace() > b[i].getFace()){
					a_greater = true;
					check = true;
					break;
				}
				else if (a[i].getFace() < b[i].getFace()){
					check = true;
					break;
				}
			}
			if (!check) throw 4;
		}
		
		return a_greater ? a : b;
	}
	else if (type_a == 6){
		
		for (int i = 3; i < 5; ++i){
			if (a[i].getFace() > b[i].getFace()){
				check = true;
				a_greater = true;
				break;
			}
			else if (a[i].getFace() < b[i].getFace()){
				check = true;
				break;
			}
		}
		if (!check) throw 4;

		return a_greater ? a : b;
	}
	else if (type_a == 7){

		for (int i = 1; i < 5; ++i){
			if (a[i].getFace() > b[i].getFace()){
				a_greater = true;
				check = true;
				break;
			}
			else if (a[i].getFace() < b[i].getFace()){
				check = true;
				break;
			}
		}
		if (!check){
			throw 4;
		}
		return a_greater ? a : b;
	}
	else if (type_a == 8){

		for (int i = 1; i < 5; ++i){
			if (a[i].getFace() > b[i].getFace()){
				a_greater = true;
				check = true;
				break;
			}
			else if (a[i].getFace() < b[i].getFace()){
				check = true;
				break;
			}
		}
		if (!check) throw 4;
			
		return a_greater ? a : b;	
	}
	else if (type_a == 9){
		
		for (int i = 0; i < 5; ++i){
			if (a[i].getFace() > b[i].getFace()){
				a_greater = true;
				check = true;
				break;
			}
			else if (a[i].getFace() < b[i].getFace()){
				check = true;
				break;
			}
		}
		if (!check) throw 4;
		
		return a_greater ? a : b;
	}
	else{
		throw 3;
	}
}



vector<string> split(string &s){
	vector<string> tempVec;
	if (s.find_first_not_of(" \t") != string::npos){
		size_t first_not_a_space = s.find_first_not_of(" \t");
		size_t last_not_a_space = s.find_last_not_of(" \t");
		s = s.substr(first_not_a_space, last_not_a_space - first_not_a_space + 1);
		while (s.size() != 0){
			int pos = 0;
			bool space_detected = false;
			int size = s.size();
			char tempCh = s.at(pos);
			while (tempCh != ' ' && tempCh != '\t' && pos < size - 1){
				tempCh = s.at(++pos);
				if (tempCh == ' ' || tempCh == '\t'){
					space_detected = true;
				}
			}
			if (space_detected){
				tempVec.push_back(s.substr(0, pos));
			}
			else{
				tempVec.push_back(s.substr(0, pos + 1));
			}
			if (pos == size - 1){
				s.clear();
			}
			else{
				s = s.substr(pos, size - pos); 
				pos = s.find_first_not_of(" \t");
				s = s.substr(pos, size - pos);
			}
			
		}
	}
	return tempVec;
}