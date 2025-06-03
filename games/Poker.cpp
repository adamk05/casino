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
        double current_round_bet = 0;  // To track the highest bet in current betting round
        bool bet_raised = false;       // Flag to indicate if bet was raised

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

        // First betting round
        int players_to_act = line.size();
        while (players_to_act > 0) {
            for (auto * i : line) {
                if (i->getAllIn() || i->getFold()) continue;

                clear();
                if (i->name != player.name)
                    cout << "Teraz gra gracz " << i->name << " (Aktualny zakład: " << current_round_bet << ", Pieniądze na stole: " << pot << ")" << endl;

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
                        cout << "Teraz gra gracz " << i->name << " (Aktualny zakład: " << current_round_bet << ", Pieniądze na stole: " << pot << ")" << endl;
                        cout << "Karty na stole: " << endl;
                        displayDeck(table);
                        cout << endl;
                        cout << "Karty gracza: " << " (" << i->checkCards(table) << ")" << endl;
                        displayDeck(player.deck);

                        // Available options
                        if (current_round_bet == 0) {
                            cout << "Podaj opcję [Fold/Check/Bet/All-in]:" << endl << "> ";
                        } else {
                            cout << "Podaj opcję [Fold/Call/Raise/All-in]:" << endl << "> ";
                        }

                        cin >> option;

                        if (option == "Fold") {
                            i->setFold(true);
                            players_to_act--;
                            break;
                        }
                        else if (option == "Check" && current_round_bet == 0) {
                            i->setCheck(true);
                            check_line.push_back(i);
                            players_to_act--;
                            break;
                        }
                        else if (option == "Call" && current_round_bet > 0) {
                            if (current_round_bet > i->getCash()) {
                                cout << "Nie masz wystarczająco pieniędzy, aby wyrównać!" << endl;
                                wait();
                                continue;
                            }
                            bet = current_round_bet - i->getBet();
                            i->setBet(current_round_bet);
                            i->setCash(i->getCash() - bet);
                            pot += bet;
                            players_to_act--;
                            break;
                        }
                        else if ((option == "Bet" && current_round_bet == 0) || (option == "Raise" && current_round_bet > 0)) {
                            while (true) {
                                cout << "Podaj kwotę:" << endl << "> ";
                                cin >> bet;

                                if (bet > current_round_bet && bet <= i->getCash()) {
                                    double total_bet = i->getBet() + bet;
                                    if (total_bet > current_round_bet) {
                                        current_round_bet = total_bet;
                                        actual_bet = current_round_bet;
                                        pot += bet;
                                        i->setBet(total_bet);
                                        i->setCash(i->getCash() - bet);
                                        players_to_act = line.size() - 1;  // Reset counter for other players
                                        bet_raised = true;
                                        break;
                                    } else {
                                        cout << "Nowy zakład musi być większy niż aktualny (" << current_round_bet << ")" << endl;
                                    }
                                } else {
                                    cout << "Niepoprawna kwota zakładu!" << endl;
                                }
                            }
                            break;
                        }
                        else if (option == "All-in") {
                            bet = i->getCash();
                            if (bet > current_round_bet) {
                                current_round_bet = bet;
                                actual_bet = current_round_bet;
                                players_to_act = line.size() - 1;
                            }
                            i->setAllIn(true);
                            i->setBet(i->getBet() + bet);
                            pot += bet;
                            players_to_act--;
                            break;
                        }
                        else {
                            cout << "Niepoprawna opcja!" << endl;
                            wait();
                        }
                    }
                    if (i->getFold() && i->name == player.name) break;
                    continue;
                }

                // Bot logic
                Bot* bot = static_cast<Bot*>(i);
                option = bot->strategy(table, current_round_bet - i->getBet());
                cout << "Gracz " << i->name << " wybrał opcję: " << option << endl;
                wait();

                if (option == "Fold") {
                    i->setFold(true);
                    players_to_act--;
                    cout << "Gracz " << i->name << " spasował" << endl;
                }
                else if (option == "Check" && current_round_bet == 0) {
                    i->setCheck(true);
                    check_line.push_back(i);
                    players_to_act--;
                }
                else if (option == "Call" && current_round_bet > 0) {
                    bet = current_round_bet - i->getBet();
                    if (bet > i->getCash()) {
                        cout << "Gracz " << i->name << " nie ma wystarczająco pieniędzy!" << endl;
                        i->setAllIn(true);
                        bet = i->getCash();
                    }
                    i->setBet(current_round_bet);
                    i->setCash(i->getCash() - bet);
                    pot += bet;
                    players_to_act--;
                    cout << "Gracz " << i->name << " wyrównuje do " << current_round_bet << endl;
                }
                else if (option == "Bet" || option == "Raise") {
                    double bot_bet = bot->decideBetAmount(current_round_bet);
                    if (bot_bet > current_round_bet && bot_bet <= i->getCash()) {
                        current_round_bet = i->getBet() + bot_bet;
                        actual_bet = current_round_bet;
                        pot += bot_bet;
                        i->setBet(current_round_bet);
                        i->setCash(i->getCash() - bot_bet);
                        players_to_act = line.size() - 1;
                        bet_raised = true;
                        cout << "Gracz " << i->name << " podbija do " << current_round_bet << endl;
                    }
                }
                else if (option == "All-in") {
                    bet = i->getCash();
                    if (bet > current_round_bet) {
                        current_round_bet = bet;
                        actual_bet = current_round_bet;
                        players_to_act = line.size() - 1;
                    }
                    i->setAllIn(true);
                    i->setBet(i->getBet() + bet);
                    pot += bet;
                    players_to_act--;
                    cout << "Gracz " << i->name << " idzie all-in z " << bet << endl;
                }
                wait();
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

    // Showdown
    cout << "Karty na stole: " << endl;
    displayDeck(table);
    cout << endl;
    cout << "Karty gracza: " << " (" << player.checkCards(table) << ")" << endl;
    displayDeck(player.deck);

    if (player.getFold()) {
        cout << "Wygrał gracz " << player.name << endl;
        player.setCash(player.getCash() + pot);
    } else {
        if (line.size() == 1) {
            cout << "Wygrał gracz " << line[0]->name << endl;
            line[0]->setCash(line[0]->getCash() + pot);
        } else {
            whoWinsPoker(line, table);
        }
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
    vector<Card> bestHand;

    for (auto player : line) {
        if (player->getFold()) continue; // Pomijamy graczy, którzy spasowali

        vector<Card> combinedCards = player->deck;
        combinedCards.insert(combinedCards.end(), table.begin(), table.end());

        string hand = player->checkCards(table); // e.g. "Para", "Strit", itd.
        int handValue = getHandValue(hand, combinedCards);

        if (handValue > bestHandValue) {
            bestHandValue = handValue;
            winners = {player};
            bestHand = combinedCards;
        }
        else if (handValue == bestHandValue) {
            // Remis ręki – porównanie najwyższych kart
            sort(combinedCards.begin(), combinedCards.end(), [](const Card& a, const Card& b) {
                static map<string, int> values = {
                    {"2",2},{"3",3},{"4",4},{"5",5},{"6",6},{"7",7},{"8",8},
                    {"9",9},{"10",10},{"Walet",11},{"Dama",12},{"Król",13},{"As",14}
                };
                return values[a.value] > values[b.value];
            });

            sort(bestHand.begin(), bestHand.end(), [](const Card& a, const Card& b) {
                static map<string, int> values = {
                    {"2",2},{"3",3},{"4",4},{"5",5},{"6",6},{"7",7},{"8",8},
                    {"9",9},{"10",10},{"Walet",11},{"Dama",12},{"Król",13},{"As",14}
                };
                return values[a.value] > values[b.value];
            });

            for (size_t i = 0; i < min(combinedCards.size(), bestHand.size()); ++i) {
                static map<string, int> values = {
                    {"2",2},{"3",3},{"4",4},{"5",5},{"6",6},{"7",7},{"8",8},
                    {"9",9},{"10",10},{"Walet",11},{"Dama",12},{"Król",13},{"As",14}
                };
                int valA = values[combinedCards[i].value];
                int valB = values[bestHand[i].value];

                if (valA > valB) {
                    winners = {player};
                    bestHand = combinedCards;
                    break;
                } else if (valA < valB) {
                    break;
                } else {
                    continue;
                }
            }

            // Jeśli wszystko równe, dodajemy do zwycięzców
            if (!winners.empty() && find(winners.begin(), winners.end(), player) == winners.end()) winners.push_back(player);
        }
    }

    if (winners.size() == 1) {
        cout << "Wygrał gracz " << winners[0]->name << "!" << endl;
        winners[0]->setCash(winners[0]->getCash() + pot);
        cout << "z układem: " << winners[0]->checkCards(table) << endl;
        for (auto winner : winners) winner->displayHand(table);
    } else {
        cout << "Remis między: ";
        for (auto* p : winners) {
            cout << p->name << " ";
            p->setCash(p->getCash() + pot / winners.size());
        }
        for (auto* p : winners) for (auto card : p->deck) cout << p->name << " (" << p->checkCards(table) << ")" << endl << card.value << " " << card.color << endl;
        cout << endl;
    }

    wait();
    reset();
}