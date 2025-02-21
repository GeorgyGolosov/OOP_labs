#pragma once
#include "game.h"
void enableRawMode();
void disableRawMode();
char getArrowKey();
void printMenu(int selectedOption);
void addNpcMenu(Game& game);
void handlePrintNpcs(Game& game);
void handleCombatMode(Game& game);
void handleSaveGame(Game& game);
void handleLoadGame(Game& game);