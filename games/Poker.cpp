#include "Poker.h"
#include <iostream>
#include "../functions/functions.h"
#include <string>
#include <vector>
#include <algorithm>
#include "../players/Bot.h"
#include "../players/Player.h"

using namespace std;

void Poker::play() const {
    reset();
    croupier.clearUsedIndexes();

    string option;
    double money = 0;
    int index = 0;
    vector<Card> table;
    double actual_bet = 0;
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
            if (i->name != player.name) cout << "Teraz gra gracz " << i->name << endl;
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
                    cout << "Teraz gra gracz " << i->name << endl;
                    cout << "Karty na stole: " << endl;
                    displayDeck(table);
                    cout << endl;
                    // player.displayHand(table);
                    cout << "Karty gracza: " << endl;
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
                    } if (option == "Call") {
                        bet = actual_bet;
                        i->setBet(bet);
                        money += bet;
                        break;
                    } if (option == "Bet") {
                        cout << "Podaj kwotę:" << endl << "> ";
                        if (bet > actual_bet) {
                            if (actual_bet == 0) actual_bet = bet;
                            cin >> bet;
                            money += bet;
                            i->setBet(bet);
                        } else {
                            cout << "Niepoprawna kwota zakłdadu" << endl;
                            cout << "Podaj kwotę:" << endl << "> ";
                            cin >> bet;
                            money += bet;
                            i->setBet(bet);
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
            option = bot->strategy(table, actual_bet);
            if (option == "Fold") {
                i->setFold(true);
                cout << endl << "Gracz " << i->name << " spasował" << endl;
                wait();
            } else if (option == "Check") {
                i->setCheck(true);
                check_line.push_back(i);
            } else if (option == "Call") continue;
            else if (option == "Bet") continue;
            else if (option == "All-in") {
                i->setAllIn(true);
                cout << endl << "Gracz " << i->name << " spasował" << endl;
            }
        }

        if (!check_line.empty()) {
            for (auto * i : check_line) {
                if (i->getAllIn()) continue;
                clear();
                if (i->name != player.name) cout << "Teraz gra gracz " << i->name << endl;
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
                        cout << "Teraz gra gracz " << i->name << endl;
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
                            bet = actual_bet;
                            i->setBet(bet);
                            money += bet;
                            break;
                        } if (option == "Bet") {
                            cout << "Podaj kwotę:" << endl << "> ";
                            if (bet > actual_bet) {
                                if (actual_bet == 0) actual_bet = bet;
                                cin >> bet;
                                money += bet;
                                i->setBet(bet);
                            } else {
                                cout << "Niepoprawna kwota zakłdadu" << endl;
                                cout << "Podaj kwotę:" << endl << "> ";
                                cin >> bet;
                                money += bet;
                                i->setBet(bet);
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
                option = bot->strategy(table, actual_bet);
                if (option == "Fold") {
                    i->setFold(true);
                    cout << endl << "Gracz " << i->name << " spasował" << endl;
                    wait();
                } else if (option == "Call") continue;
                else if (option == "Bet") continue;
                else if (option == "All-in") {
                    i->setAllIn(true);
                    cout << endl << "Gracz " << i->name << " gra va banque" << endl;
                }
            }
        }

        line.erase(remove_if(line.begin(), line.end(), [](Players* player) {
            return player->getFold();
        }), line.end());

        if (table.size() > 2) rotate(line.rbegin(), line.rbegin() + 1, line.rend());

        if (player.getFold()) break;

        clear();
    }

    cout << "Karty na stole: " << endl;
    displayDeck(table);
    cout << endl;
    cout << "Karty gracza: " << endl;
    displayDeck(player.deck);

    if (player.getFold()) {
        cout << "Wygrał gracz " << player.name << endl;
        player.setCash(player.getCash() + money);
    } else {
        if (line.size() == 1) {
            cout << "Wygrał gracz " << player.name << endl;
            player.setCash(player.getCash() + money);
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
    int bestHand = 0;

    for (auto player : line) {
        vector<Card> combinedCards = player->deck;
        combinedCards.insert(combinedCards.end(), table.begin(), table.end());

        string hand = player->checkCards(table);
        int handValue = getHandValue(hand, combinedCards);

        if (handValue > bestHand) {
            bestHand = handValue;
            winners = {player}; // Resetuj listę zwycięzców
        } else if (handValue == bestHand) {
            winners.push_back(player); // Dodaj gracza do listy zwycięzców
        }

    }

    winners.size() == 1 ? cout << "Wygrał gracz: " << winners[0]->name << endl : cout << "Remis" << endl;
}