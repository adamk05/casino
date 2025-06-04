#include "Poker.h"
#include <iostream>
#include "../functions/functions.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <bits/regex_constants.h>

#include "../players/Bot.h"
#include "../players/Player.h"

using namespace std;

void Poker::play() {
    reset();
    croupier.clearUsedIndexes();

    string option;
    double money = 0;
    int index = 0;
    vector<Card> table;
    double actual_bet = 0, pot = 0;
    double bet;

    vector<Players*> line = {&player, &bob, &john, &tim};
    vector<Players*> check_line;

    for (int i = 0 ; i < 2; i++) {
        for (auto * j : line) {
            cout << "Krupier daje kartę graczowi " << j->name << endl;
            croupier.giveCard(*j);
            wait();
            clear();
        }
    }

    croupier.giveCard(table);
    croupier.giveCard(table);
    cout << "Karty na stole: " << endl;
    displayDeck(table);
    cout << endl;
    cout << "Karty gracza: " << endl;
    displayDeck(player.deck);
    wait();
    clear();

    while (table.size() < 5) {
        if (line.size() == 1) break;

        actual_bet = 0;

        for (auto * i : line) i->setCheck(false);
        check_line.clear();

        croupier.giveCard(table);
        cout << "Karty na stole: " << endl;
        displayDeck(table);
        cout << endl;
        cout << "Karty gracza: " << endl;
        displayDeck(player.deck);
        wait();
        clear();

        cout << "Gracze: ";
        for (auto * i : line) cout << i->name << " ";
        cout << endl;

        for (auto * i : line) {
            if (i->getAllIn()) continue;
            clear();
            if (i->name != player.name) cout << "Teraz gra gracz " << i->name << " (Aktualny zakład: " << actual_bet << ", Pieniądze na stole: " << pot << ")" << endl;
            if (i->name != player.name) {
                cout << "Karty na stole: " << endl;
                displayDeck(table);
                cout << endl;
                cout << "Karty gracza: " << endl;
                displayDeck(player.deck);
                wait();
            }
            if (i->name == player.name) {
                while (true) {
                    cout << "Teraz gra gracz " << i->name << " (Aktualny zakład: " << actual_bet << ", Pieniądze na stole: " << pot << ")" << endl;
                    cout << "Karty na stole: " << endl;
                    displayDeck(table);
                    cout << endl;
                    cout << "Karty gracza: " << " (" << i->checkCards(table) << ")" << endl;
                    displayDeck(player.deck);
                    cout << "Podaj opcję [Fold/Check/Call/Bet/All-in]:" << endl << "> ";
                    cin >> option;
                    if (option == "Fold") {
                        i->setFold(true);
                        break;
                    } if (option == "Check") {
                        i->setCheck(true);
                        check_line.push_back(i);
                        break;
                    } if (option == "Call" and actual_bet < player.getCash()) {
                        if (actual_bet == 0) {
                            cout << "Nie możesz wykonać Call – nikt jeszcze nie postawił." << endl;
                            wait();
                            clear();
                            continue;
                        }
                        bet = actual_bet;
                        player.setBet(bet);
                        player.setCash(player.getCash() - bet);
                        money += bet;
                        pot += bet;
                        break;
                    } if (option == "Bet" and actual_bet < player.getCash()) {
                        while (true) {
                            cout << "Podaj kwotę:" << endl << "> ";
                            cin >> bet;

                            if (bet >= actual_bet) {
                                actual_bet = bet;
                                pot += bet;
                                money += bet;
                                player.setBet(bet);
                                player.setCash(player.getCash() - bet);
                                break;
                            } else {
                                cout << "Niepoprawna kwota zakładu. Musi być większa niż aktualny zakład (" << actual_bet << ")" << endl;
                            }
                        }
                        break;
                    } if (option == "All-in") {
                        i->setAllIn(true);
                        actual_bet = player.getCash();
                        money += player.getCash();
                        break;
                    }
                    clear();
                }
                if (i->getFold() && i->name == player.name) break;
                continue;
            }

            Bot* bot = static_cast<Bot*>(i);
            option = bot->strategy(table, actual_bet, pot);
            cout << "Gracz " << i->name << " wybrał opcję: " << option << endl;
            wait();
            if (option == "Fold") {
                i->setFold(true);
                cout << "Gracz " << i->name << " spasował" << endl;
                wait();
            } else if (option == "Check") {
                i->setCheck(true);
                check_line.push_back(i);
            } else if (option == "Call") {
                if (actual_bet == 0) {
                    cout << "Bot nie może wykonać Call, bo nie ma zakładu do wyrównania" << endl;
                    wait();
                    continue;
                }
                bet = actual_bet;
                i->setBet(bet);
                pot += bet;
                cout << "Gracz " << i->name << " wyrównuje zakład: " << bet << endl;
                wait();
            } else if (option == "Bet" || option == "Raise") {
                double bot_bet = i->decideBetAmount(actual_bet);  // zakładamy, że masz taką metodę
                if (bot_bet > actual_bet) {
                    actual_bet = bot_bet;
                    pot += bot_bet;
                    money += bot_bet;
                    i->setBet(bot_bet);
                    cout << "Gracz " << i->name << " stawia " << bot_bet << endl;
                }
                wait();
            } else if (option == "All-in") {
                i->setAllIn(true);
                cout << "Gracz " << i->name << " gra va banque" << endl;
            }
        }

        if (!check_line.empty()) {
            for (auto * i : check_line) {
                if (i->getAllIn()) continue;
                clear();
                if (i->name != player.name) cout << "Teraz gra gracz " << i->name << " (Aktualny zakład: " << actual_bet << ", Pieniądze na stole: " << pot << ")" << endl;;
                if (i->name != player.name) {
                    cout << "Karty na stole: " << endl;
                    displayDeck(table);
                    cout << endl;
                    cout << "Karty gracza: " << endl;
                    displayDeck(player.deck);
                    wait();
                }
                if (i->name == player.name) {
                    while (true) {
                        cout << "Teraz gra gracz " << i->name << " (Aktualny zakład: " << actual_bet << ", Pieniądze na stole: " << pot << ")" << endl;
                        cout << "Karty na stole: " << endl;
                        displayDeck(table);
                        cout << endl;
                        cout << "Karty gracza: " << endl;
                        displayDeck(player.deck);
                        cout << "Podaj opcję [Fold/Call/Bet/All-in]:" << endl << "> ";
                        cin >> option;
                        if (option == "Fold") {
                            i->setFold(true);
                            break;
                        } if (option == "Call") {
                            if (actual_bet == 0) {
                                cout << "Nie możesz wykonać Call – nikt jeszcze nie postawił." << endl;
                                wait();
                                clear();
                                continue;
                            }
                            bet = actual_bet;
                            i->setBet(bet);
                            pot += bet;
                            break;
                        } if (option == "Bet") {
                            while (true) {
                                cout << "Podaj kwotę:" << endl << "> ";
                                cin >> bet;

                                if (bet > actual_bet) {
                                    if (actual_bet == 0) {
                                        actual_bet = bet;
                                        pot += bet;
                                    }
                                    money += bet;
                                    i->setBet(bet);
                                    break;
                                } else {
                                    cout << "Niepoprawna kwota zakładu. Musi być większa niż aktualny zakład (" << actual_bet << ")" << endl;
                                }
                            }
                            break;
                        } if (option == "All-in") {
                            i->setAllIn(true);
                            actual_bet = player.getCash();
                            money += player.getCash();
                            break;
                        }
                        clear();
                    }
                    if (i->getFold() && i->name == player.name) break;
                    continue;
                }

                Bot* bot = static_cast<Bot*>(i);
                option = bot->strategy(table, actual_bet, pot);
                cout << "Gracz " << i->name << " wybrał opcję: " << option << endl;
                wait();
                if (option == "Fold") {
                    i->setFold(true);
                    cout << "Gracz " << i->name << " spasował" << endl;
                    wait();
                } else if (option == "Call") {
                    if (actual_bet == 0) {
                        cout << "Bot nie może wykonać Call, bo nie ma zakładu do wyrównania" << endl;
                        wait();
                        continue;
                    }
                    bet = actual_bet;
                    i->setBet(bet);
                    pot += bet;
                    cout << "Gracz " << i->name << " wyrównuje zakład: " << bet << endl;
                    wait();
                } else if (option == "Bet" || option == "Raise") {
                    double bot_bet = i->decideBetAmount(actual_bet);  // zakładamy, że masz taką metodę
                    if (bot_bet > actual_bet) {
                        actual_bet = bot_bet;
                        pot += bot_bet;
                        money += bot_bet;
                        i->setBet(bot_bet);
                        cout << "Gracz " << i->name << " stawia " << bot_bet << endl;
                    }
                    wait();
                } else if (option == "All-in") {
                    i->setAllIn(true);
                    cout << "Gracz " << i->name << " gra va banque" << endl;
                    wait();
                    }
            }
        }

        line.erase(remove_if(line.begin(), line.end(), [](Players* player) {
            return player->getFold();
        }), line.end());

        if (table.size() > 2) rotate(line.rbegin(), line.rbegin() + 1, line.rend());

        if (player.getFold()) break;

        clear();
        pot += actual_bet;
    }

    cout << "Karty na stole: " << endl;
    displayDeck(table);
    cout << endl;
    cout << "Karty gracza: " << endl;
    displayDeck(player.deck);

    if (player.getFold()) {
        cout << "Wygrał gracz " << player.name << endl;
        player.setCash(player.getCash() + pot);
    } else {
        if (line.size() == 1) {
            cout << "Wygrał gracz " << player.name << endl;
            player.setCash(player.getCash() + pot);
        } else whoWinsPoker(line, table);
    }
}

void Poker::reset() const {
    player.deck.clear();
    bob.deck.clear();
    john.deck.clear();
    tim.deck.clear();
    player.setFold(false);
    bob.setFold(false);
    john.setFold(false);
    tim.setFold(false);
    player.setAllIn(false);
    bob.setAllIn(false);
    john.setAllIn(false);
    tim.setAllIn(false);
    player.setCheck(false);
    bob.setCheck(false);
    john.setCheck(false);
    tim.setCheck(false);
}

void Poker::whoWinsPoker(vector<Players*> line, vector<Card>& table) const {
    vector<Players*> winners;
    int bestHandValue = 0;

    for (auto player : line) {
        if (player->getFold()) continue; // Skip folded players

        vector<Card> combinedCards = player->deck;
        combinedCards.insert(combinedCards.end(), table.begin(), table.end());

        string hand = player->checkCards(table);
        int handValue = getHandValue(hand, combinedCards);

        if (handValue > bestHandValue) {
            bestHandValue = handValue;
            winners = {player};
        }
        else if (handValue == bestHandValue) {
            // If same hand value, we need to compare the actual cards
            bool isBetter = false;
            if (!winners.empty()) {
                // Compare the best cards in both hands
                vector<Card> currentBestCards = winners[0]->deck;
                currentBestCards.insert(currentBestCards.end(), table.begin(), table.end());

                // Sort both hands in descending order
                sort(combinedCards.begin(), combinedCards.end(),
                    [](const Card& a, const Card& b) {
                        map<string, int> values = {
                            {"2",2},{"3",3},{"4",4},{"5",5},{"6",6},{"7",7},{"8",8},
                            {"9",9},{"10",10},{"Walet",11},{"Dama",12},{"Król",13},{"As",14}
                        };
                        return values[a.value] > values[b.value];
                    });

                sort(currentBestCards.begin(), currentBestCards.end(),
                    [](const Card& a, const Card& b) {
                        map<string, int> values = {
                            {"2",2},{"3",3},{"4",4},{"5",5},{"6",6},{"7",7},{"8",8},
                            {"9",9},{"10",10},{"Walet",11},{"Dama",12},{"Król",13},{"As",14}
                        };
                        return values[a.value] > values[b.value];
                    });

                // Compare card by card
                for (size_t i = 0; i < min(combinedCards.size(), currentBestCards.size()); i++) {
                    map<string, int> values = {
                        {"2",2},{"3",3},{"4",4},{"5",5},{"6",6},{"7",7},{"8",8},
                        {"9",9},{"10",10},{"Walet",11},{"Dama",12},{"Król",13},{"As",14}
                    };

                    int currentCard = values[combinedCards[i].value];
                    int bestCard = values[currentBestCards[i].value];

                    if (currentCard > bestCard) {
                        isBetter = true;
                        break;
                    } else if (currentCard < bestCard) {
                        break;
                    }
                }
            }

            if (isBetter) {
                bestHandValue = handValue;
                winners = {player};
            } else if (handValue == bestHandValue) {
                winners.push_back(player);
            }
        }
    }

    if (winners.empty()) {
        cout << "Wszyscy gracze spasowali!" << endl;
    } else if (winners.size() == 1) {
        cout << "Wygrał gracz: " << winners[0]->name << " z układem: " << winners[0]->checkCards(table) << endl;
        winners[0]->displayHand(table);
    } else {
        cout << "Remis między graczami: ";
        for (size_t i = 0; i < winners.size(); i++) {
            cout << winners[i]->name;
            if (i < winners.size() - 1) cout << ", ";
        }
        cout << " z układem: " << winners[0]->checkCards(table) << endl;
        for (auto winner : winners) {
            winner->displayHand(table);
        }
    }
    wait();
    clear();
}