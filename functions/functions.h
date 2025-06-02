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

// draws a random number from a specified range
int randomize(int start, int end);

// clears the console
void clear();

// pauses the program for some time
void wait(int seconds = 3);

// handles getting a float input from the user
float getFloatInput(string question);

// handles getting an int input from the user where values are equal to those in the allowedValues vector
int getIntInputEqual(string question, vector<int> allowedValues, string errorMessage= "To nie liczba.");

// handles getting an int input from the user where values are between the upper and the lower limit
int getIntInputLimited(string question,  int lowerLimit, int upperLimit, string errorMessage= "To nie liczba.");

// handles getting a "yes/no" response from the user
bool yesNoResponse(string question);

// handles getting a response from the user where the input is present in options vector
string multiChoiceResponse(string question, vector<string> options, string errorMessage = "Nieprawidłowa odpowiedź!");

// transforms a string to the lower case
string toLower(string str);

// checks if a value is present in the vector
bool isInVector(const vector<int>& vec, const int& value);

#endif //FUNCTIONS_H