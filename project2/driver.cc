/*
 * driver.cc
 *
 * Author: Viet Dinh
 * Date: 11/19/2016
 */

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <stdexcept>
#include "CardDeck.h"

using namespace std;

int main(){
	DeckOfCards deck;
	deck.shuffle();

	try{
		vector<Card> five_card_hand[2];
		five_card_hand[0] = deal_a_five_cards(deck);//computer's card hand
		five_card_hand[1] = deal_a_five_cards(deck);//player's card hand
		sort_card_hand(five_card_hand[0]);
		sort_card_hand(five_card_hand[1]);
		
		//manulally sets 2 5-card hands for testing
		//users are responsible for enterring valid values of suit [1, 4] and valid value of faces [1, 13]
		//otherwise, program crashes
		/*
		vector<Card> five_card_hand[2]; 
		Card tempC;
		
		tempC.setSuit(1); tempC.setFace(5);
		five_card_hand[0].push_back(tempC);
		tempC.setSuit(1); tempC.setFace(7);
		five_card_hand[0].push_back(tempC);
		tempC.setSuit(4); tempC.setFace(1);
		five_card_hand[0].push_back(tempC);
		tempC.setSuit(1); tempC.setFace(2);
		five_card_hand[0].push_back(tempC);
		tempC.setSuit(1); tempC.setFace(3);
		five_card_hand[0].push_back(tempC);

		tempC.setSuit(3); tempC.setFace(5);
		five_card_hand[1].push_back(tempC);
		tempC.setSuit(2); tempC.setFace(4);
		five_card_hand[1].push_back(tempC);
		tempC.setSuit(3); tempC.setFace(13);
		five_card_hand[1].push_back(tempC);
		tempC.setSuit(3); tempC.setFace(3);
		five_card_hand[1].push_back(tempC);
		tempC.setSuit(3); tempC.setFace(2);
		five_card_hand[1].push_back(tempC);
		*/

		cout << "Computer's 5-card hand: Hidden" << endl;
		cout << "Your 5-card hand: " << endl;
		for (int i = 0; i < 5; ++i){
			cout << "\t" << five_card_hand[1][i].toString() << endl;
		}
		cout << endl;
		
		
		vector<Card> temp[2];
		int type[2], count1, count2;
		for (int i = 0; i < 2; ++i){
			five_card_hand[i] = sort_card_hand_and_get_type(five_card_hand[i], type[i]);
		}
		count1 = count2 = 0;
		bool stop1, stop2;
		stop1 = stop2 = false;
		while (!stop1 || !stop2){
			if (!stop2){
				string command = "  ";
				while (command.length() != 1 || (tolower(command.at(0)) != 'y' &&
					tolower(command.at(0)) != 'n')){
					cout << "Would you like to draw a card?(y/n) ";
					getline(cin, command);
					
					if (tolower(command.at(0)) == 'y'){
						Card tempC = deck.dealCard();
						cout << "Your new card is: \n\t" << tempC.toString() << endl;
						cout << "Your current 5-card hand: " << endl;
						for (int i = 0; i < 5; ++i){
							cout << "\t" << five_card_hand[1][i].toString() << endl;
						}
						cout << endl;
						string tempStr;
						bool confirm_drop = false;
						while (!confirm_drop){
							cout << "Now you must drop one of 6 cards you have." << endl;
							cout << "For instance, if you wan to drop the card \"Spade(1)-Queen(12)\":" << endl;
							cout << "type \"1 12\"" << endl;
							cout << "Which card would you like to drop (SuitNumber FaceNumber)? ";
							getline(cin, tempStr);
							vector<string> strs = split(tempStr);
							if (strs.size() == 2){
								try{
									int suit = stoi(strs[0]);
									int face = stoi(strs[1]);
									if (face == 1) face == 14;
									if (suit > 0 && suit < 5 && face > 0 && face < 14){
										//the new card will be dropped
										if (suit == tempC.getSuit() && face == tempC.getFace()){
											confirm_drop = true;
											++count2;
											if (count2 == 3) stop2 = true;
										}
										//one of the cards in original hand will be dropped
										else{
											for (int i = 0; i < 5; ++i){
												if (suit == five_card_hand[1][i].getSuit() && face == five_card_hand[1][i].getFace()){
													five_card_hand[1][i] = tempC;
													sort_card_hand(five_card_hand[1]);
													five_card_hand[1] = sort_card_hand_and_get_type(five_card_hand[1], type[1]);
													confirm_drop = true;
													++count2;
													if (count2 == 3) stop2 = true;
													break;
												}
											}
										}
									}
								}
								catch (invalid_argument &e){}
								catch (out_of_range &e){}
							}
						}
					}
					else if (stop1){//user not drawing a card
						string command1 = "  ";
						while (command1.length() != 1 || (tolower(command1.at(0)) != 'y' &&
							tolower(command1.at(0)) != 'n')){
							cout << "If you don't draw a card, the game would stop. Stop game(y/n)? ";
							getline(cin, command1);
							if (tolower(command1.at(0)) == 'y'){
								stop2 = true;
							}
						}
					}
					
				}
			}

			if (!stop1){
				bool check = draw_more_card(five_card_hand[0], type[0]);
				if (!check){
					stop1 = true;
					cout << "computer has given up its turns." << endl;
				}
				else{
					Card tempC = deck.dealCard();
					fix_general_combination(five_card_hand[0], tempC, type[0]);
					++count1;
					if (count1 == 3) stop1 = true;
					cout << "computer took its turn." << endl;
				}
			}
		}
		
		vector<Card> better_hand = better_5_hand_card(type[0], five_card_hand[0], type[1], five_card_hand[1]);
		cout << "SHOW CARDS" << endl;
		for (int i = 0; i < 2; ++i){
			if(i == 0){
				cout << "Computer's 5-card hand: " << endl;
			}
			else{
				cout << "Your 5-card hand: " << endl;
			}
			for (int j = 0; j < 5; ++j){
				cout << "\t" << five_card_hand[i][j].toString() << endl;
			}
			cout << endl;
		}
		cout << "RESULT" << endl;
		cout << "The better 5-card hand: " << endl;
		for (int i = 0; i < 5; ++i){
			cout << "\t" << better_hand[i].toString() << endl;
		}
		cout << endl;
	}
	catch (int &e){
		if (e == 1){
			cerr << "Not enough cards left to form a 5-card hand.";
		}
		else if (e == 2){
			cerr << "Not a 5-card hand.";
		}
		else if (e == 3){
			cerr << "Invalid type of 5-card hand passed to function." << endl;
		}
		else if (e == 4){
			cout << "2 5-card hands are equal." << endl;
		}
	}
	return 0;
}