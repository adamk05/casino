#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <random>
#include <iostream>
#include <string>
#ifdef _WIN32
#define byte win_byte_override
#include <Windows.h>
#else
#include <unistd.h>
#endif


using namespace std;

// Losowanie liczby całkowitej w podanym zakresie
int randomize(int start, int end);

// Czyszczenie konsoli przy sprawdzeniu systemu operacyjnego
void clear();

// Czekanie na ruch
void wait();

float getFloatInput(string question);

bool yesNoResponse(string question);

string multiChoiceResponse(string question, vector<string> options);

string toLower(string str);

#endif //FUNCTIONS_H