#pragma once
#include <string>

using namespace std;

/*
 * these are ANSI escape codes that are used in order to change background color and text color of the terminal / console
 * or to reset all the manipulations made
 */

const string RESET = "\033[0m";
const string RED_BG = "\033[48;5;160m";
const string BLACK_BG = "\033[48;5;16m";
const string GREEN_BG = "\033[42m";
const string WHITE_TXT = "\033[97m";
const string DARK_TXT = "\033[38;5;232m";
const string WHITE_BG = "\033[48;5;251m";
const string MAHOGANY_BG = "\033[48;5;52m";
const string LIGHT_BLUE_BG = "\033[48;5;129m";