#include "Craps.h"

Craps::Craps(Player &player) : Game(player), passLine(false), yoBet(0), any7Bet(0), fieldBet(0), crapsBet(0), hiLoBet(0), comeOutRoll(true), point(0) { }

void Craps::play() {
    reset();
    string question = "Obstawiasz Pass Line czy Don't Pass (pl/dp)?";
    vector<string> passLineOptions;
    passLineOptions.push_back("pl");
    passLineOptions.push_back("dp");
    string passLineResponse = multiChoiceResponse(question, passLineOptions);
    if (passLineResponse == "pl") {
        passLine = true;
    } else {
        passLine = false;
    }

    question = "Ile stawiasz?";

    while (true) {
        float bet = getFloatInput(question);
        if (player.cash >= bet) {
            player.cash -= bet;
            player.bet = bet;
            break;
        }
        cout << "Nie masz wystarczająco punktów (masz " << player.cash << ")" << endl;
    }

    clear();

    while (true) {
        // players gets the opportunity to place any ammount of prop bets. He can place one bet at the time, after it was placed
        // he is asked again to place a bet. When he decides he is done he presses "n". Player can't place 2 different bets for same thing
        string propBetResponse = "";
        while (propBetResponse != "n") {
            if (player.cash == 0) {
                cout << "Nie masz punktów, nie możesz obstawić nowego zakładu" << endl;
                break;
            }
            if (any7Bet > 0 || yoBet > 0 || hiLoBet > 0 || fieldBet > 0 || crapsBet > 0) {
                cout << "Obstawione zakłady poboczne: " << endl;
            }
            if (any7Bet > 0) {
                cout << " any 7: " << any7Bet << endl;
            }
            if (yoBet > 0) {
                cout << " yo: " << yoBet << endl;
            }
            if (hiLoBet > 0) {
                cout << " hi-lo: " << hiLoBet << endl;
            }
            if (crapsBet > 0) {
                cout << " craps: " << crapsBet << endl;
            }
            if (fieldBet > 0) {
                cout << " field: " << fieldBet << endl;
            }
            question = "Dostępne zakłady poboczne:\n any 7 (7)\n Yo (11)\n Hi-Lo (2 lub 12)\n Craps (2, 3, lub 12)\n Field (2, 3, 4, 9, 10, 11, 12)\nCzy chcesz obstawić jakiś zakład poboczny? (a - any 7 / y - yo / h - hi-lo / c - craps / f -field / n - nie chcę stawiać pobocznego zakładu)";
            vector <string> propBetOptions;
            propBetOptions.push_back("a");
            propBetOptions.push_back("y");
            propBetOptions.push_back("h");
            propBetOptions.push_back("c");
            propBetOptions.push_back("f");
            propBetOptions.push_back("n");
            propBetResponse = multiChoiceResponse(question, propBetOptions);
            if (propBetResponse == "a") {
                if (any7Bet != 0) {
                    cout << "Obstawiłeś już any 7 w tej rundzie" << endl;
                    wait();
                } else {
                    question ="Ile obstawiasz?";
                    while (true) {
                        float bet = getFloatInput(question);
                        if (player.cash >= bet) {
                            player.cash -= bet;
                            any7Bet = bet;
                            break;
                        }
                        cout << "Nie masz wystarczająco punktów (masz " << player.cash << ")" << endl;
                    }
                }
            } else if (propBetResponse == "y") {
                if (yoBet != 0) {
                    cout << "Obstawiłeś już Yo w tej rundzie" << endl;
                    wait();
                } else {
                    question ="Ile obstawiasz?";
                    while (true) {
                        float bet = getFloatInput(question);
                        if (player.cash >= bet) {
                            player.cash -= bet;
                            yoBet = bet;
                            break;
                        }
                        cout << "Nie masz wystarczająco punktów (masz " << player.cash << ")" << endl;
                    }
                }
            } else if (propBetResponse == "h") {
                if (hiLoBet != 0) {
                    cout << "Obstawiłeś już Hi-Lo w tej rundzie" << endl;
                    wait();
                } else {
                    question ="Ile obstawiasz?";
                    while (true) {
                        float bet = getFloatInput(question);
                        if (player.cash >= bet) {
                            player.cash -= bet;
                            hiLoBet = bet;
                            break;
                        }
                        cout << "Nie masz wystarczająco punktów (masz " << player.cash << ")" << endl;
                    }
                }
            } else if (propBetResponse == "c") {
                if (crapsBet != 0) {
                    cout << "Obstawiłeś już Craps w tej rundzie" << endl;
                    wait();
                } else {
                    question ="Ile obstawiasz?";
                    while (true) {
                        float bet = getFloatInput(question);
                        if (player.cash >= bet) {
                            player.cash -= bet;
                            crapsBet = bet;
                            break;
                        }
                        cout << "Nie masz wystarczająco punktów (masz " << player.cash << ")" << endl;
                    }
                }
            } else if (propBetResponse == "f") {
                if (fieldBet != 0) {
                    cout << "Obstawiłeś już Field w tej rundzie" << endl;
                    wait();
                } else {
                    question ="Ile obstawiasz?";
                    while (true) {
                        float bet = getFloatInput(question);
                        if (player.cash >= bet) {
                            player.cash -= bet;
                            fieldBet = bet;
                            break;
                        }
                        cout << "Nie masz wystarczająco punktów (masz " << player.cash << ")" << endl;
                    }
                }
            }
            clear();
        }
        cout << "Kości zostały rzucone..." << endl;
        wait();
        clear();
        int dice1 = randomize(1, 6);
        int dice2 = randomize(1, 6);
        cout << "Kość 1: " << dice1 << endl;
        cout << "Kość 2: " << dice2 << endl;
        wait();
        int result = dice1 + dice2;
        cout << "Wynik: " << result << endl;
        if (comeOutRoll) {
            if (result == 7 || result == 11) {
                if (passLine) {
                    cout << "Wygrywasz zakład Pass Line" << endl;
                    cout << "Wygrywasz " << player.bet * 2 << endl;
                    player.winBet(2);
                    settlePropBets(result);
                } else {
                    cout << "Przegrywasz zakład Don't Pass" << endl;
                    settlePropBets(result);
                }
                string temp;
                cout << "Kliknij enter by kontynuować" << endl;
                cin >> temp;
                return;
            }

            if (result == 2 || result == 3 || result == 12) {
                if (passLine) {
                    cout << "Przegrywasz zakład Pass Line" << endl;
                    settlePropBets(result);
                } else {
                    if (result == 12) {
                        cout << "Remis, zwrot stawki" << endl;
                        player.winBet(1);
                    } else {
                        cout << "Wygrywasz zakład Don't Pass" << endl;
                        cout << "Wygrywasz " << player.bet * 2 << endl;
                        player.winBet(2);
                        settlePropBets(result);
                    }
                }
                string temp;
                cout << "Kliknij enter by kontynuować" << endl;
                cin >> temp;
                return;
            }

            cout << "Ustanawia się point na " << result << endl;
            wait();
            clear();
            point = result;
            settlePropBets(result);
            cout << "Gra trwa dalej, kolejne zakłady, kolejny rzut" << endl;
            comeOutRoll = false;
        } else {
            cout << "(point " << point << ")" << endl;
            if (result == 7) {
                if (passLine) {
                    cout << "Przegrywasz zakład Pass Line" << endl;
                    settlePropBets(result);
                } else {
                    cout << "Wygrywasz zakład Don't Pass" << endl;
                    cout << "Wygrywasz " << player.bet * 2 << endl;
                    player.winBet(2);
                    settlePropBets(result);
                }
                string temp;
                cout << "Kliknij enter by kontynuować" << endl;
                cin >> temp;
                return;
            }
            if (result == point) {
                if (passLine) {
                    cout << "Wygrywasz zakład Pass Line" << endl;
                    cout << "Wygrywasz " << player.bet * 2 << endl;
                    player.winBet(2);
                    settlePropBets(result);
                } else {
                    cout << "Przegrywasz zakład Don't Pass" << endl;
                    settlePropBets(result);
                }
                string temp;
                cout << "Kliknij enter by kontynuować" << endl;
                cin >> temp;
                return;
            }
            settlePropBets(result);
            cout << "Gra trwa dalej, kolejne zakłady, kolejny rzut" << endl;
        }
    }
}

void Craps::reset() {
    passLine = false;
    point = 0;
    crapsBet = 0;
    fieldBet = 0;
    yoBet = 0;
    hiLoBet = 0;
    any7Bet = 0;
}

void Craps::settlePropBets(int result) {
    if (any7Bet > 0 || yoBet > 0 || hiLoBet > 0 || fieldBet > 0 || crapsBet > 0) {
        cout << "Rozliczenie zakładów pobocznych: " << endl;
    }
    if (any7Bet > 0) {
        wait();
        if (result == 7) {
            cout << "Wygrywasz any 7 (4:1)" << endl;
            cout << "Wygrywasz " << any7Bet * 5 << endl;
            player.winIndependentBet(any7Bet * 5);
        } else {
            cout << "Przegrywasz any 7" << endl;
        }
    }
    if (yoBet > 0) {
        wait();
        if (result == 11) {
            cout << "Wygrywasz Yo 15:1" << endl;
            cout << "Wygrywasz " << yoBet * 16 << endl;
            player.winIndependentBet(yoBet * 16);
        } else {
            cout << "Przegrywasz Yo" << endl;
        }
    }
    if (crapsBet > 0) {
        wait();
        if (result == 2 || result == 3 || result == 12) {
            cout << "Wygrywasz craps 7:1" << endl;
            cout << "Wygrywasz " << crapsBet * 8 << endl;
            player.winIndependentBet(crapsBet * 8);
        } else {
            cout << "Przegrywasz craps" << endl;
        }
    }
    if (fieldBet > 0) {
        wait();
        if (result == 3 || result == 4 || result == 9 || result == 10 || result == 11) {
            cout << "Wygrywasz field 1:1" << endl;
            cout << "Wygrywasz " << fieldBet * 2 << endl;
            player.winIndependentBet(fieldBet * 2);
        } else if (result == 2 || result == 12) {
            cout << "Wygrywasz field 2:1" << endl;
            cout << "Wygrywasz " << fieldBet * 3 << endl;
            player.winIndependentBet(fieldBet * 3);
        } else {
            cout << "Przegrywasz field" << endl;
        }
    }
    if (hiLoBet > 0) {
        wait();
        if (result == 12 || result == 2) {
            cout << "Wygrywasz hi-lo 15:1" << endl;
            cout << "Wygrywasz " << hiLoBet * 16 << endl;
            player.winIndependentBet(hiLoBet * 16);
        } else {
            cout << "Przegrywasz hi-lo" << endl;
        }
    }
    any7Bet = 0;
    yoBet = 0;
    crapsBet = 0;
    fieldBet = 0;
    hiLoBet = 0;
    wait();
}




