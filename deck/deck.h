#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

#ifndef DECK_H
#define DECK_H

// Struktura talii
struct Card {
    string color;
    string value;
};

void displayDeck(vector<Card>& deck);

void displayCard(const Card& card);

extern string colors[4];
extern string values[13];

#endif