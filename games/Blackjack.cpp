#include "Blackjack.h"

#include <iomanip>

Blackjack::Blackjack(Player &player, Croupier &croupier) : Game(player), croupier(croupier), insurance(0) { }

void Blackjack::play() {
    reset();

    string question = "Ile stawiasz?";
    string temporary;

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
    cout << "Krupier rozdaje karty..." << endl;

    wait();
    clear();

    croupier.giveCard(player);
    croupier.giveCard(player);


    // do testowania splita
    // player.deck.at(0).value = "8";
    // player.deck.at(0).color = "Pik";
    // player.deck.at(1).value = "8";
    // player.deck.at(1).color = "Trefl";

    playerPoints = countPoints(player.deck);

    croupier.giveCardToYourself();
    croupier.giveCardToYourself();

    //do testowania insurance
    // croupier.deck.at(0).value = "As";
    // croupier.deck.at(0).color = "Pik";
    // croupier.deck.at(1).value = "4";
    // croupier.deck.at(1).color = "Trefl";

    croupierPoints = countPoints(croupier.deck);

    cout << "Twoje karty: " << endl;

    displayDeck(player.deck);

    wait();

    //if player or croupier has 21 points with first 2 cards, the game imedietally ends
    if (playerPoints == 21) {
        cout << "Masz blackjacka!" << endl;
        wait();
        cout << "Karty krupiera:" << endl;
        displayDeck(croupier.deck);
        wait();
        if (croupierPoints == 21) {
            cout << "Krupier też ma blackjacka!" << endl;
            wait();
            cout << "Remis" << endl;
            wait();
            cout << "Zwrot zakładu" << endl;
            player.winBet(1);
        } else {
            cout << "Wygrywasz zakład 3:2" << endl;
            wait();
            cout << "Wygrywasz " << player.bet * 2.5 << endl;
            player.winBet(2.5);
        }
    } else {
        //player gets to know one of croupier's cards
        cout << "Karta krupiera: " << endl;
        displayCard(croupier.deck.at(0));

        //if showed card is ace, player gets an opportunity to play insurance
        if (croupier.deck.at(0).value == "As") {
            string question = "Ubezpieczasz zakład? (t/n)";
            insurance = yesNoResponse(question);
            if (insurance) {
                player.cash -= player.bet / 2;
            }
        }
        if (croupierPoints == 21) {
            cout << "Krupier ma blackjacka" << endl;
            displayDeck(croupier.deck);
            if (insurance) {
                cout << "Zadziałało ubezpieczenie, wygrywasz " << player.bet * 1.5 << endl;
                player.winBet(1.5);
            } else {
                cout << "Przegrywasz zakład";
            }

            std::cout << "Wciśnij Enter, żeby kontynuować..." << flush;
            getline(cin, temporary);
            return;
        }
        if (insurance) {
            cout << "Krupier nie ma blackjacka, przegrywasz ubezpieczenie" << endl;
        }
        wait();
        //if player has 2 same value cards, he gets an opportunity to split the deck
        bool split = false;
        if (player.deck.at(0).value == player.deck.at(1).value && player.cash >= player.bet) {
            string question = "Masz dwie karty o identycznej wartości, decydujesz się na splita? (t/n)";
            split = yesNoResponse(question);
        }
        if (split) {
            player.cash -= player.bet;
            playerSplittedBet = player.bet;
            splittedDeck.push_back(player.deck.at(1));
            player.deck.pop_back();
            printDecksAfterSplit();
            cout << "Krupier daje kartę do ręki 1..." << endl;
            wait();
            croupier.giveCard(player);
            playerPoints = countPoints(player.deck);
            cout << "Dobrana karta: ";
            displayCard(player.deck.at(1));
            wait();
            cout << "Krupier daje kartę do ręki 2..." << endl;
            wait();
            croupier.giveCard(splittedDeck);
            playerSplittedPoints = countPoints(splittedDeck);
            cout << "Dobrana karta: ";
            displayCard(splittedDeck.at(1));
            //after split both hands are independent
            bool handOneFinish = false;
            bool handTwoFinish = false;
            // clear();
            //game ends if both hands had ended
            while (!handOneFinish || !handTwoFinish) {
                cout << "Karta krupiera: " << endl;
                displayCard(croupier.deck.at(0));
                cout << "Twoje karty: " << endl;
                printDecksAfterSplit();
                //player makes moves for both hands if the hand is not finished
                if (!handOneFinish) {
                    string question = "Jaki ruch wybierasz dla ręki 1 (s - stand/h - hit)";;
                    vector<string> options;
                    options.push_back("s");
                    options.push_back("h");
                    string response = multiChoiceResponse(question, options);
                    if (response == "s") {
                        handOneFinish = true;
                    } else if (response == "h") {
                        cout << "Krupier daje ci karte" << endl;
                        wait();
                        croupier.giveCard(player);
                        playerPoints = countPoints(player.deck);
                        cout << "Dobrana karta: " << endl;
                        displayCard(player.deck.at(player.deck.size() - 1));
                        wait();
                        cout << "Twoje karty: " << endl;
                        displayDeck(player.deck);
                        wait();
                        if (playerPoints > 21) {
                            cout << "Przekroczyłeś 21 punktów, przegrywasz zakład" << endl;
                            handOneFinish = true;
                        }
                    }
                }
                if (!handTwoFinish) {
                    string question = "Jaki ruch wybierasz dla ręki 2 (s - stand/h - hit)";;
                    vector<string> options;
                    options.push_back("s");
                    options.push_back("h");
                    string response = multiChoiceResponse(question, options);
                    if (response == "s") {
                        handTwoFinish = true;
                    } else if (response == "h") {
                        cout << "Krupier daje ci karte" << endl;
                        wait();
                        croupier.giveCard(splittedDeck);
                        playerSplittedPoints = countPoints(splittedDeck);
                        cout << "Dobrana karta: " << endl;
                        displayCard(splittedDeck.at(splittedDeck.size() - 1));
                        wait();
                        cout << "Twoje karty: " << endl;
                        displayDeck(splittedDeck);
                        wait();
                        if (playerSplittedPoints > 21) {
                            cout << "Przekroczyłeś 21 punktów, przegrywasz zakład" << endl;
                            handTwoFinish = true;
                        }
                    }
                }
                clear();
            }
            settleBet(true);
        } else {
            while (true) {
                clear();
                cout << "Karta krupiera: " << endl;
                displayCard(croupier.deck.at(0));
                cout << "Twoje karty: " << endl;
                displayDeck(player.deck);
                string question;
                vector<string> options;
                options.push_back("s");
                options.push_back("h");
                if (player.cash >= player.bet) {
                    options.push_back("d");
                    question = "Jaki ruch wybierasz (s - stand/h - hit/d - double down)";
                } else {
                    question = "Jaki ruch wybierasz (s - stand/h - hit)";
                }
                string response = multiChoiceResponse(question, options);
                if (response == "s") {
                    settleBet(false);
                    string temporary;
                    std::cout << "Wciśnij Enter, żeby kontynuować..." << flush;
                    getline(cin, temporary);
                    return;
                } else if (response == "h") {
                    cout << "Krupier daje ci karte" << endl;
                    wait();
                    croupier.giveCard(player);
                    playerPoints = countPoints(player.deck);
                    cout << "Dobrana karta: " << endl;
                    displayCard(player.deck.at(player.deck.size() - 1));
                    wait();
                    cout << "Twoje karty: " << endl;
                    displayDeck(player.deck);
                    wait();
                    if (playerPoints > 21) {
                        cout << "Przekroczyłeś 21 punktów, przegrywasz zakład" << endl;

                        std::cout << "Wciśnij Enter, żeby kontynuować..." << flush;
                        getline(cin, temporary);
                        return;
                    }
                } else if (response == "d") {
                    cout << "Następuje podwojenie stawki" << endl;
                    player.cash -= player.bet;
                    player.bet += player.bet;
                    wait();
                    cout << "Krupier daje ci karte" << endl;
                    wait();
                    croupier.giveCard(player);
                    playerPoints = countPoints(player.deck);
                    cout << "Dobrana karta: " << endl;
                    displayCard(player.deck.at(player.deck.size() - 1));
                    wait();
                    settleBet(false);

                    std::cout << "Wciśnij Enter, żeby kontynuować..." << flush;
                    getline(cin, temporary);
                    return;
                }
            }
        }
    }
    std::cout << "Wciśnij Enter, żeby kontynuować..." << flush;
    getline(cin, temporary);
}

void Blackjack::reset() {
    player.deck.clear();
    croupier.deck.clear();
    croupier.clearUsedIndexes();
    splittedDeck.clear();
    insurance = 0;
}

int Blackjack::countPoints(vector<Card> &deck) {
    int points = 0;
    int aces = 0; // ammount of aces in the deck

    for (Card& card : deck) {
        if (card.value == "2") points += 2;
        else if (card.value == "3") points += 3;
        else if (card.value == "4") points += 4;
        else if (card.value == "5") points += 5;
        else if (card.value == "6") points += 6;
        else if (card.value == "7") points += 7;
        else if (card.value == "8") points += 8;
        else if (card.value == "9") points += 9;
        else if (card.value == "10"
                || card.value == "Walet"
                || card.value == "Dama"
                || card.value == "Król") points += 10;
        else if (card.value == "As") aces++;
    }

    // adding aces' points
    for (int i = 0; i < aces; i++) {
        if (points < 21) {
            points += 11;
            if (points > 21) points -= 10;
        } else if (points > 21) {
            points += 1;
        }
    }

    return points;
}

void Blackjack::settleBet(bool splitted) {
    cout << "Twoje karty: " << endl;
    if (splitted) {
        printDecksAfterSplit();
    } else {
        displayDeck(player.deck);
    }
    wait();
    cout << "Karty krupiera: " << endl;
    displayDeck(croupier.deck);
    wait();
    while (croupierPoints < 17) {
        cout << "Krupier dobiera karte" << endl;
        croupier.giveCardToYourself();
        wait();
        cout << "Karty krupiera: " << endl;
        displayDeck(croupier.deck);
        croupierPoints = countPoints(croupier.deck);
        wait();
    }

    if (splitted) {
        cout << "Rozliczenie ręki 1: " << endl;
    }

    if (playerPoints > 21) {
        cout << "Przekroczyłeś 21 punktów, przegrywasz zakład" << endl;
    } else if (croupierPoints > 21) {
        cout << "Krupier przekroczył 21 punktów (" << croupierPoints << ")" << endl;
        wait();
        cout << "Wygrywasz zakład 1:1" << endl;
        wait();
        cout << "Wygrywasz " << player.bet * 2 << endl;
        player.winBet(2);
    } else if (croupierPoints == playerPoints) {
        cout << "Remis, obaj gracze mają po " << playerPoints << " punktów" << endl;
        wait();
        cout << "Zwrot zakładu" << endl;
        player.winBet(1);
    } else if (playerPoints > croupierPoints) {
        cout << "Masz " << playerPoints << " punktów, a krupier ma " << croupierPoints << "punktów" << endl;
        wait();
        cout << "Wygrywasz zakład 1:1" << endl;
        wait();
        cout << "Wygrywasz " << player.bet * 2 << endl;
        player.winBet(2);
    } else {
        cout << "Masz " << playerPoints << " punktów, a krupier ma " << croupierPoints << "punktów" << endl;
        wait();
        cout << "Przegrywasz zakład" << endl;
    }

    if (splitted) {
        cout << "Rozliczenie ręki 2: " << endl;
        if (playerSplittedPoints > 21) {
            cout << "Przekroczyłeś 21 punktów, przegrywasz zakład" << endl;
        } else if (croupierPoints > 21) {
            cout << "Krupier przekroczył 21 punktów (" << croupierPoints << ")" << endl;
            wait();
            cout << "Wygrywasz zakład 1:1" << endl;
            wait();
            cout << "Wygrywasz " << playerSplittedBet * 2 << endl;
            player.winIndependentBet(playerSplittedBet * 2);
        } else if (croupierPoints == playerSplittedPoints) {
            cout << "Remis, obaj gracze mają po " << playerSplittedPoints << " punktów" << endl;
            wait();
            cout << "Zwrot zakładu" << endl;
            player.winIndependentBet(playerSplittedBet);
        } else if (playerSplittedPoints > croupierPoints) {
            cout << "Masz " << playerSplittedPoints << " punktów, a krupier ma " << croupierPoints << "punktów" << endl;
            wait();
            cout << "Wygrywasz zakład 1:1" << endl;
            wait();
            cout << "Wygrywasz " << playerSplittedBet * 2 << endl;
            player.winIndependentBet(playerSplittedBet * 2);
        } else {
            cout << "Masz " << playerSplittedPoints << " punktów, a krupier ma " << croupierPoints << "punktów" << endl;
            wait();
            cout << "Przegrywasz zakład" << endl;
        }
    }
    wait();
}

void Blackjack::printDecksAfterSplit() {
    cout << "Ręka 1: " << endl;
    displayDeck(player.deck);
    cout << endl;
    cout << "Ręka 2: " << endl;
    displayDeck(splittedDeck);
}





