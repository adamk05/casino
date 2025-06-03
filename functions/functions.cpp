#include "functions.h"

#include "../games/roulette/InputException.h"

#ifdef _WIN32
#define NOMINMAX
#define byte win_byte_override
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

int randomize(const int start, const int end) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> distrib(start, end);

    return distrib(gen);
}

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait(int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
}

float getFloatInput(string question) {
    string input;
    while (true) {
        cout << question << endl;
        getline(cin, input);
        try {
            return stof(input);
        } catch (...) {
            cout << "To nie jest liczba.\n";
        }
    }
}

int getIntInputEqual(string question, vector<int> allowedValues, string errorMessage) {
    string input;
    int answer;
    while (true) {
        cout << question << endl;
        getline(cin, input);
        try {
            answer = stoi(input);
            for (int value: allowedValues) {
                if (value == answer) {
                    return answer;
                }
            }
            throw InputException("Nie można wybrać takiego numeru!");
        } catch (InputException& e) {
            cout << e.what() << endl;
        } catch (...) {
            cout << errorMessage << endl;
        }
    }
}

int getIntInputLimited(string question, int lowerLimit, int upperLimit, string errorMessage) {
    string input;
    int answer;
    while (true) {
        cout << question << endl;
        getline(cin, input);
        try {
            answer = stoi(input);
            if (answer < lowerLimit || answer > upperLimit) {
                throw InputException("Numer jest z poza zakresu!");
            }
            return answer;
        } catch (InputException& e) {
            cout << e.what() << endl;
        } catch (...) {
            cout << errorMessage << endl;
        }
    }
}

bool yesNoResponse(string question) {
    string input;
    while (true) {
        cout << question << endl;
        getline(cin, input);
        if (input == "t" || input == "T") {
            return true;
        } else if (input == "n" || input == "N") {
            return false;
        } else {
            cout << "Nieprawidłowa odpowiedź!" << endl;
        }
    }
}

string multiChoiceResponse(string question, vector<string> options, string errorMessage) {
    string input;
    while (true) {
        cout << question << endl;
        getline(cin, input);
        for (int i = 0; i < options.size(); i++) {
            if (toLower(input) == toLower(options.at(i))) {
                return options.at(i);
            }
        }
        cout << errorMessage << endl;
    }
}

string toLower(string str) {
    for (char& c : str) {
        c = tolower(static_cast<unsigned char>(c));
    }
    return str;
}

bool isInVector(const vector<int>& vec, const int& value) {
    for (int number : vec) {
        if (number == value) {
            return true;
        }
    }
    return false;
}



