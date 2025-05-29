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
        games/OneHandedBandit.h)
