cmake_minimum_required(VERSION 3.30)
project(casino)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(casino main.cpp
        deck/deck.cpp
        deck/deck.h
        players/Player.cpp
        players/Player.h
        players/Croupier.cpp
        players/Croupier.h
        games/Game.cpp
        games/Game.h
        functions/functions.cpp
        functions/functions.h
        games/Blackjack.cpp
        games/Blackjack.h
        games/Baccarat.cpp
        games/Baccarat.h
        games/Craps.cpp
        games/Craps.h
        games/OneHandedBandit.cpp
        games/OneHandedBandit.h
        games/Poker.cpp
        games/Poker.h
        players/Bot.cpp
        players/Bot.h
        functions/poker.cpp
        functions/poker.h
        players/Players.cpp
        players/Players.h
        games/OneHandedBandit.h
        games/Blackjack.h
        games/roulette/Roulette.cpp
        games/roulette/Roulette.h
        games/roulette/NumberField.cpp
        games/roulette/NumberField.h
        games/roulette/InputException.cpp
        games/roulette/InputException.h)
