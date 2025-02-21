#include <iostream>
#include "game.h"
#include "factory.h"
#include "utils.h"
#include "observer.h"

int main() {
    Game game;

    game.addObserver(std::make_shared<ConsoleObserver>());
    game.addObserver(std::make_shared<FileObserver>());

    enableRawMode();
    int selectedOption = 1;
    bool running = true;

    while (running) {
        printMenu(selectedOption);
        char key = getArrowKey();

        // Обработка навигации по меню
        if (key == 'U') {
            selectedOption = (selectedOption == 0) ? 5 : selectedOption - 1;
        } else if (key == 'D') {
            selectedOption = (selectedOption == 5) ? 0 : selectedOption + 1;
        } else if (key == '\n') {
            switch(selectedOption) {
                case 1:
                    addNpcMenu(game);
                    break;
                case 2:
                    handlePrintNpcs(game);
                    break;
                case 3:
                    handleCombatMode(game);
                    break;
                case 4:
                    handleSaveGame(game);
                    break;
                case 5:
                    handleLoadGame(game);
                    break;
                case 0:
                    running = false;
                    break;
                default:
                    break;
            }
        }
    }

    disableRawMode();
    std::cout << "\x1B[34mExiting...\033[0m\n";
    return 0;
}
