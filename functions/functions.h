#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <random>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

// Losowanie liczby całkowitej w podanym zakresie
int randomize(int start, int end);

// Czyszczenie konsoli przy sprawdzeniu systemu operacyjnego
void clear();

// Czekanie na ruch
void wait(int seconds = 3);

float getFloatInput(string question);

int getIntInputEqual(string question, vector<int> allowedValues, string errorMessage= "To nie liczba.");

int getIntInputLimited(string question,  int lowerLimit, int upperLimit, string errorMessage= "To nie liczba.");

bool yesNoResponse(string question);

string multiChoiceResponse(string question, vector<string> options, string errorMessage = "Nieprawidłowa odpowiedź!");

string toLower(string str);

bool isInVector(const vector<int>& vec, const int& value);

#endif //FUNCTIONS_H