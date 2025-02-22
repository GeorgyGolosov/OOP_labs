#include <iostream>
#include <iomanip>
#include <termios.h>
#include <unistd.h>
#include "game.h"
#include "factory.h"


const int ART_WIDTH = 35;
const int PADDING = 5;


// Function to configure terminal for raw input
void enableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

// Function to restore terminal settings
void disableRawMode() {
    termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

// Function to read arrow key input
char getArrowKey() {
    char c;
    read(STDIN_FILENO, &c, 1);

    if (c == '\033') {
        char seq[2];
        read(STDIN_FILENO, &seq[0], 1);
        read(STDIN_FILENO, &seq[1], 1);

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return 'U'; // Up
                case 'B': return 'D'; // Down
                case 'C': return 'R'; // Right
                case 'D': return 'L'; // Left
            }
        }
    }
    return c;
}

void printMenu(int selectedOption) {
    system("clear");
    std::cout << R"(
      ____        _                         ______    _          ____
     |  _ \      | |                       |  ____|  | |        |___ \
     | |_) | __ _| | __ _  __ _ _   _ _ __ | |__ __ _| |_ ___    __) |
     |  _ < / _` | |/ _` |/ _` | | | | '__||  __/ _` | __/ _ \  |__ <
     | |_) | (_| | | (_| | (_| | |_| | |    | | | (_| | || __/  ___) |
     |____/ \__,_|_|\__,_|\__, |\__,_|_|    |_| \__,_|\__\___| |____/
                           __/ |
                          |___/
    )" << "\n";
    std::cout << (selectedOption == 1 ? "> " : "  ") << "Add new NPC\n";
    std::cout << (selectedOption == 2 ? "> " : "  ") << "Print all NPCs\n";
    std::cout << (selectedOption == 3 ? "> " : "  ") << "Start combat mode\n";
    std::cout << (selectedOption == 4 ? "> " : "  ") << "Save to file\n";
    std::cout << (selectedOption == 5 ? "> " : "  ") << "Load from file\n";
    std::cout << (selectedOption == 0 ? "> " : "  ") << "Exit\n";
    std::cout << "\nUse arrow keys to navigate, Enter to select\n";
}

void addNpcMenu(Game& game) {
    system("clear");
    std::string type, name;
    int x, y;
    int selectedType = 1;
    bool typeSelected = false;
    const int NUM_TYPES = 3;

    // Обновлённый список названий NPC
    std::vector<std::string> npcNames = {"Белка", "Эльф", "Разбойник"};

    // Обновлённые ASCII-арты для каждого типа
    std::vector<std::string> asciiArts = {
        // Белка
        "   (\\__/)\n"
        "   (o.o )\n"
        "  /|   |\\\n"
        "   (> < )~~~~\n",

        // Эльф
        "    /\\\n"
        "   /__\\ \n"
        "   \\  / \n"
        "    \\/  \n"
        "    ||  \n"
        "   /||\\ \n",

        // Разбойник
        "   .----.\n"
        "  / .--. \\\n"
        " | |    | |\n"
        "  \\ '--' /\n"
        "   '----'\n"
    };

    while (!typeSelected) {
        system("clear");
        std::vector<std::stringstream> artLines(10); // Задаём достаточное количество строк

        // Выводим ASCII-арт каждого типа горизонтально
        for (int i = 0; i < NUM_TYPES; i++) {
            std::istringstream artStream(asciiArts[i]);
            std::string line;
            int lineNum = 0;
            while (std::getline(artStream, line) && lineNum < 10) {
                // Заполняем каждую строку до фиксированной ширины (ART_WIDTH)
                line.resize(ART_WIDTH, ' ');
                artLines[lineNum] << (i == selectedType - 1 ? "\033[1;32m" : "")
                                  << line << (i == selectedType - 1 ? "\033[0m" : "")
                                  << std::string(PADDING, ' ');
                lineNum++;
            }
        }

        // Выводим собранные строки
        for (const auto& line : artLines) {
            std::cout << line.str() << '\n';
        }
        std::cout << "\n\n";

        // Выводим названия под артом с центрированием
        for (int i = 0; i < NUM_TYPES; i++) {
            int padding = ((ART_WIDTH - npcNames[i].length()) / 2);
            if (i == selectedType - 1) {
                std::cout << "\033[1;32m";
            }
            // Немного смещаем второй элемент для визуального выравнивания
            if (i == 1)
                std::cout << std::string(padding - 5, ' ') << npcNames[i]
                          << std::string(ART_WIDTH - padding - npcNames[i].length() + 3, ' ')
                          << std::string(PADDING, ' ');
            else
                std::cout << std::string(padding - 6, ' ') << npcNames[i]
                          << std::string(ART_WIDTH - padding - npcNames[i].length() + 7, ' ')
                          << std::string(PADDING, ' ');
            if (i == selectedType - 1) {
                std::cout << "\033[0m";
            }
        }
        std::cout << "\n";
        std::cout << "\n\nUse Left/Right arrows to select, Enter to confirm\n";

        char key = getArrowKey();
        if (key == 'L') {
            selectedType = (selectedType - 2 + NUM_TYPES) % NUM_TYPES + 1;
        }
        else if (key == 'R') {
            selectedType = selectedType % NUM_TYPES + 1;
        }
        else if (key == '\n') {
            typeSelected = true;
            type = npcNames[selectedType - 1];
        }
    }



    disableRawMode();
    std::cout << "\x1B[34mEnter name: \033[0m";
    std::cin >> name;
    std::cout << "\x1B[34mEnter X and Y coordinates (0-500) separated by space: \033[0m";
    while (!(std::cin >> x >> y) || x < 0 || x > 500 || y < 0 || y > 500) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\x1B[31mInvalid coordinates! Please enter numbers between 0 and 500: \033[0m";
    }

    try {
        game.addNpc(NpcFactory::createNpc(type, name, x, y));
        std::cout << "\033[1;32mNPC added successfully!\033[0m\n";
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    } catch (const std::exception& e) {
        std::cout << "\x1B[31mError: " << e.what() << "\033[0m" << std::endl;
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    enableRawMode();
}

void handlePrintNpcs(Game& game) {
    disableRawMode();
    std::cout << "\n\x1B[34mCurrent NPCs:\033[0m\n";
    game.printNpcs();
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    enableRawMode();
}


void handleSaveGame(Game& game) {
    disableRawMode();
    std::string filename;
    std::cout << "\x1B[34mEnter filename to save: \033[0m";
    std::cin >> filename;
    game.saveToFile(filename);
    std::cout << "\033[1;32mGame saved to " << filename << "\033[0m" << std::endl;
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(100, '\n');
    std::cin.get();
    enableRawMode();
}

void handleLoadGame(Game& game) {
    disableRawMode();
    std::string filename;
    std::cout << "\x1B[34mEnter filename to load: \033[0m";
    std::cin >> filename;
    try {
        game.loadFromFile(filename);
        std::cout << "\033[1;32mGame loaded from \033[0m" << filename << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\x1B[31mError loading file: \033[0m" << e.what() << std::endl;
    }
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(100, '\n');
    std::cin.get();
    enableRawMode();
}
