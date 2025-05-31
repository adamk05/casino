#include "functions.h"

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

void wait() {
#ifdef _WIN32
    Sleep(3000);
#else
    sleep(3);
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

string multiChoiceResponse(string question, vector<string> options) {
    string input;
    while (true) {
        cout << question << endl;
        getline(cin, input);
        for (int i = 0; i < options.size(); i++) {
            if (toLower(input) == toLower(options.at(i))) {
                return options.at(i);
            }
        }
        cout << "Nieprawidłowa odpowiedź!" << endl;
    }
}

string toLower(string str) {
    for (char& c : str) {
        c = tolower(static_cast<unsigned char>(c));
    }
    return str;
}




