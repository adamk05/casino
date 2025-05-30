#ifndef POKER_H
#define POKER_H

#include <vector>
#include <string>
#include "../deck/deck.h"

using namespace std;

// Checls of a number occurs n times
bool repeated(vector<int>& values, int n);

// Checks if there are pairs
bool repeatedPairs(vector<int>& values, int n);

// Checks if there is a gull house
bool isFull(vector<int>& values);

// Checks if there is a royal flush
bool isRoyalFlush(const vector<int>& values, vector<int>& colors);

// Checks if there is a straight
bool isStraight(const vector<int>& values);

// Checks if there is a straight flush
bool isStraightFlush(const vector<int>& values, vector<int>& colors);

// Gets cards values
int getHandValue(string hand, vector<Card> cards);

#endif //POKER_H