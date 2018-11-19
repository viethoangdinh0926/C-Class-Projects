/*
 * CardDeck.h
 *
 * Author: Viet Dinh
 * Date: 11/19/2016
 */

#ifndef H_CARDDECK
#define H_CARDDECK
#define SUIT_NUM 4
#define SUIT_CARD_NUM 13
#define ALL_CARD_NUM 52

#include <list>

class Card{
	int suit, face;
public:
	static int suits[SUIT_NUM];
	static int faces[SUIT_CARD_NUM];
	Card(int s = 1, int f = 1) : suit(s), face(f){};
	int getSuit() const;
	void setSuit(int s){ suit = s; }
	int getFace() const;
	void setFace(int f){ face = f; }
	std::string toString();
};

class DeckOfCards{
	std::vector<Card> deck;
	//ranges from 1 to 52
	int currentCard;
public:
	DeckOfCards();
	//shuffles card deck
	void shuffle();
	//deals 1 card from card deck
	Card &dealCard();
	//check if there is at least a card left in card deck
	bool moreCards(){
		return currentCard < ALL_CARD_NUM + 1;
	};
};

//deals a 5-card hand from the deck
std::vector<Card> deal_a_five_cards(DeckOfCards &deck);
//moves all card from a vector of 5-card hand to sort cards easily in descending order
//this function is used in other functions to sort vector of 5-card hand
//sorting compares each two card in the 5 card hand, put them in a list in descending order
void sort_card_hand(std::vector<Card> &five_card_hand);

/*
 * This following group of functions is called in the order that functions appear
 * in order to determine what kind the 5-card hand is
 * also to get the vector of the 5-card hand which is sorted in the order of the way 
 * that the two card hands are compared
 */

//returns an empty vector if the 5-card hand is not a straight-flush
//returns a 5-card hand's vector as order of the way to compare 2 card hands under the rule of Poker game
std::vector<Card> straight_flush(const std::vector<Card> &five_card_hand);
//returns an empty vector if the 5-card hand is not a four-of-a-kind
//returns a 5-card hand's vector as order of the way to compare 2 card hands under the rule of Poker game
std::vector<Card> four_of_a_kind(const std::vector<Card> &five_card_hand);
//returns an empty vector if the 5-card hand is not a full-house
//returns a 5-card hand's vector as order of the way to compare 2 card hands under the rule of Poker game
std::vector<Card> full_house(const std::vector<Card> &five_card_hand);
//returns an empty vector if the 5-card hand is not a straight-flush
//returns a 5-card hand's vector as order of the way to compare 2 card hands under the rule of Poker game
std::vector<Card> flush(const std::vector<Card> &five_card_hand);
//returns an empty vector if the 5-card hand is not a straight
//returns a 5-card hand's vector as order of the way to compare 2 card hands under the rule of Poker game
std::vector<Card> straight(const std::vector<Card> &five_card_hand);
//returns an empty vector if the 5-card hand is not a three-of-a-kind
//returns a 5-card hand's vector as order of the way to compare 2 card hands under the rule of Poker game
std::vector<Card> three_of_a_kind(const std::vector<Card> &five_card_hand);
//returns an empty vector if the 5-card hand is not a two-pair
//returns a 5-card hand's vector as order of the way to compare 2 card hands under the rule of Poker game
std::vector<Card> two_pair(const std::vector<Card> &five_card_hand);
//returns an empty vector if the 5-card hand is not a 5-card hand containing only 1 pair
//returns a 5-card hand's vector as order of the way to compare 2 card hands under the rule of Poker game
std::vector<Card> pair_card(const std::vector<Card> &five_card_hand);
//returns a sorted vector of a 5-card hand which is not any special above combinations
std::vector<Card> sort_normal_hand(const std::vector<Card> &five_card_hand);

//combines all functions of the above group
//type of special combination is saved into argument "type"
//Type value falls in range [1, 9] for each type of special combinations of a 5-card hand from straight-flush combination to a normal combination
std::vector<Card> sort_card_hand_and_get_type(const std::vector<Card> &five_card_hand, int &type);

//decides if the dealer should draw the next card if availble
bool draw_more_card(const std::vector<Card> &five_card_hand, const int &type);

/*
 * each function in this group provide a way to deal with new card for each type that the original 5-card hand could be
 * this group of functions descibe how computers deal with new card and their current 5-card hand
 */
//when the original 5-card hand is a straight-flush
void fix_straight_flush(std::vector<Card> &five_card_hand, const Card &nextCard, int &type);
//when the original 5-card hand is a four-of-a-kind
void fix_four_of_a_kind(std::vector<Card> &five_card_hand, const Card &nextCard, int &type);
//when the original 5-card hand is a full-house
void fix_full_house(std::vector<Card> &five_card_hand, const Card &nextCard, int &type);
//when the original 5-card hand is a flush
//void fix_flush(std::vector<Card> &five_card_hand, const Card &nextCard, int &type);
//when the original 5-card hand is a straight
void fix_straight(std::vector<Card> &five_card_hand, const Card &nextCard, int &type);
//when the original 5-card hand is a three-of-a-kind
void fix_three_of_a_kind(std::vector<Card> &five_card_hand, const Card &nextCard, int &type);
//when the original 5-card hand has 2 pairs and is not any above kind
void fix_two_pair(std::vector<Card> &five_card_hand, const Card &nextCard, int &type);
//when the original 5-card hand has only one pair and is not any above kinds
void fix_one_pair(std::vector<Card> &five_card_hand, const Card &nextCard, int &type);
//when the original 5-card hand is not any above kinds
void fix_normal_combination(std::vector<Card> &five_card_hand, const Card &nextCard, int &type);

//combines all functions of above group to find the highest kind that a new 5-card hand can be formed
//from the new card and the original 5-card hand.
//the new 5-card hand is also sorted under the rule of Poker game in descending order
//found type is saved to parameter "type"
//new 5-card hand is saved to parameter "five_card_hand"
void fix_general_combination(std::vector<Card> &five_card_hand, const Card &nextCard, int &type);

/*
 * This function is used to compare 2 sorted vectors of 2 5-card hands
 * The two sorted vectors are archieved from the functions in the above group
 * Types of the two 5-card hands need to be determined before hand
 * Type value falls in range [1, 9] for each type of special combinations of a 5-card hand from straight-flush combination to a normal combination
 * Types can be determined after one of above functions returns an unempty vector
 * Types must be correct in order to the function operates correctly
 */
const std::vector<Card> &better_5_hand_card(const int &type_a, const std::vector<Card> &a, const int &type_b, const std::vector<Card> &b);

//split string
//works for user input
std::vector<std::string> split(std::string &s);

#endif