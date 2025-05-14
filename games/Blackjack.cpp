#include "Blackjack.h"

Blackjack::Blackjack(Player &player, Croupier &croupier) : Game(player), croupier(croupier), insurance(0) { }

void Blackjack::play() {
    reset();

    string question = "Ile stawiasz?";;

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

    playerPoints = countPoints(player.deck);

    croupier.giveCardToYourself();
    croupier.giveCardToYourself();

    croupierPoints = countPoints(croupier.deck);

    cout << "Twoje karty: " << endl;

    displayDeck(player.deck);

    wait();

    if (playerPoints == 21) {
        cout << "Masz blackjacka!" << endl;
        wait();
        cout << "Karty krupiera:" << endl;
        displayDeck(croupier.deck);
        wait();
        if (croupierPoints == 21) {
            cout << "Krupier też ma blackjacka!" << endl;
            wait();
            cout << "Remis, wygrywasz zakład 1:1" << endl;
            wait();
            cout << "Wygrywasz " << player.bet << endl;
            player.winBet(1);
        } else {
            cout << "Wygrywasz zakład 3:2" << endl;
            wait();
            cout << "Wygrywasz " << player.bet * 1.5 << endl;
            player.winBet(1.5);
        }
    } else {
        cout << "Karta krupiera: " << endl;
        displayCard(croupier.deck.at(0));
        wait();
        bool split;
        if (player.deck.at(0).value == player.deck.at(1).value && player.cash >= player.bet) {
            string question = "Masz dwie karty o identycznej wartości, decydujesz się na splita? (t/n)";
            split = yesNoResponse(question);
        }
        if (split) {
            //todo split
            return;
        } else {
            while (true) {
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
                    settleBet();
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
                    settleBet();
                }
            }
        }
    }
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
    int aces = 0; // Ilość asów w talii

    // Liczenie punktów
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

    // Dodawanie punktów asów
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

void Blackjack::settleBet() {
    cout << "Twoje karty: " << endl;
    displayDeck(player.deck);
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
    if (croupierPoints > 21) {
        cout << "Krupier przekroczył 21 punktów (" << croupierPoints << ")" << endl;
        wait();
        cout << "Wygrywasz zakład 3:2" << endl;
        wait();
        cout << "Wygrywasz " << player.bet * 1.5 << endl;
        player.winBet(1.5);
    } else if (croupierPoints == playerPoints) {
        cout << "Remis, obaj gracze mają po " << playerPoints << " punktów, wygrywasz zakład 1:1" << endl;
        wait();
        cout << "Wygrywasz " << player.bet * 1 << endl;
        player.winBet(1);
    } else if (playerPoints > croupierPoints) {
        cout << "Masz " << playerPoints << " punktów, a krupier ma " << croupierPoints << "punktów" << endl;
        wait();
        cout << "Wygrywasz zakład 3:2" << endl;
        wait();
        cout << "Wygrywasz " << player.bet * 1.5 << endl;
    } else {
        cout << "Masz " << playerPoints << " punktów, a krupier ma " << croupierPoints << "punktów" << endl;
        wait();
        cout << "Przegrywasz zakład" << endl;
    }
}




