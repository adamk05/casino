#include "Baccarat.h"

Baccarat::Baccarat(Player &player, Croupier &croupier) : Game(player), croupier(croupier) { }

void Baccarat::play() {
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
    // clear();
    cout << "Krupier rozdaje karty..." << endl;

    wait();
    // clear();

    croupier.giveCard(player);
    croupier.giveCard(player);

    croupier.giveCardToYourself();
    croupier.giveCardToYourself();

    playerPoints = countPoints(player.deck);
    croupierPoints = countPoints(croupier.deck);

    cout << "Twoje karty: " << endl;

    displayDeck(player.deck);

    wait();

    if (playerPoints >= 8) {
        cout << "Masz " << playerPoints << " punktów, koniec gry" << endl;
        wait();
        cout << "Karty krupiera:" << endl;
        displayDeck(croupier.deck);
        wait();
        cout << "Krupier ma " << croupierPoints << " punktów" << endl;
        wait();
        if (playerPoints < croupierPoints) {
            cout << "Przegrywasz zakład";
        } else if (playerPoints == croupierPoints) {
            cout << "Remis, zwrot zakładu" << endl;
            player.winBet(1);
        } else {
            cout << "Wygrywasz zakład 1:1" << endl << "Wygrywasz " << player.bet * 2 << endl;
            player.winBet(2);
        }
    } else if (croupierPoints >= 8) {
        cout << "Krupier ma " << croupierPoints << "punktów, koniec gry" << endl;
        cout << "Karty krupiera:" << endl;
        displayDeck(croupier.deck);
        wait();
        cout << "Ty masz " << playerPoints << " punktów, przegrywasz zakład";
    } else {
        string question = "Chcesz dobrać kartę (t/n)";
        bool drawCard = yesNoResponse(question);
        if (drawCard) {
            croupier.giveCard(player);
            playerPoints = countPoints(player.deck);
            cout << "Dobrana karta: " << endl;
            displayCard(player.deck.at(player.deck.size() - 1));
            wait();
            cout << "Twoje karty: " << endl;
            displayDeck(player.deck);
        }
        if (croupierPoints <= 4) {
            cout << "Krupier dobiera kartę" << endl;
            croupier.giveCardToYourself();
            croupierPoints = countPoints(croupier.deck);
        } else {
            cout << "Krupier nie dobiera karty" << endl;
        }
        wait();
        cout << "Twoje karty: " << endl;
        displayDeck(player.deck);
        wait();
        cout << "Masz " << playerPoints << " punktów" << endl;
        wait();
        cout << "Karty krupiera:" << endl;
        displayDeck(croupier.deck);
        wait();
        cout << "Krupier ma " << croupierPoints << "punktów" << endl;
        wait();
        if (playerPoints < croupierPoints) {
            cout << "Przegrywasz zakład";
        } else if (playerPoints == croupierPoints) {
            cout << "Remis, zwrot zakładu" << endl;
            player.winBet(1);
        } else {
            cout << "Wygrywasz zakład 1:1" << endl << "Wygrywasz " << player.bet * 2 << endl;
            player.winBet(2);
        }
    }
}

void Baccarat::reset() {
    player.bet = 0;
    croupier.clearUsedIndexes();
    croupier.deck.clear();
}

int Baccarat::countPoints(vector<Card> &deck) {
    int points = 0;
    for (Card& card : deck) {
        if (card.value == "2") points += 2;
        else if (card.value == "3") points += 3;
        else if (card.value == "4") points += 4;
        else if (card.value == "5") points += 5;
        else if (card.value == "6") points += 6;
        else if (card.value == "7") points += 7;
        else if (card.value == "8") points += 8;
        else if (card.value == "9") points += 9;
        else if (card.value == "As") points++;
    }
    return points % 10;
}



