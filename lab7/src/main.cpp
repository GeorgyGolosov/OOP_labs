#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <memory>
#include "game.h"
#include "factory.h"
#include "observer.h"

int main() {
    Game game;

    // Добавляем наблюдателей: вывод на экран и запись в файл
    game.addObserver(std::make_shared<ConsoleObserver>());
    game.addObserver(std::make_shared<FileObserver>());

    // Создаём 50 NPC в случайных позициях внутри карты 100 x 100
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 100;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distX(0, MAP_WIDTH);
    std::uniform_int_distribution<int> distY(0, MAP_HEIGHT);
    std::uniform_int_distribution<int> typeDist(0, 2); // 0: Белка, 1: Эльф, 2: Разбойник

    for (int i = 0; i < 50; ++i) {
        int x = distX(rng);
        int y = distY(rng);
        int typeIndex = typeDist(rng);
        std::string type, name;
        if (typeIndex == 0) {
            type = "Белка";
            name = "Белка" + std::to_string(i);
        } else if (typeIndex == 1) {
            type = "Эльф";
            name = "Эльф" + std::to_string(i);
        } else {
            type = "Разбойник";
            name = "Разбойник" + std::to_string(i);
        }
        game.addNpc(NpcFactory::createNpc(type, name, x, y));
    }

    // Запускаем симуляцию (движение, бой и вывод карты)
    game.startSimulation();

    // Основной поток ждёт 30 секунд работы симуляции
    std::this_thread::sleep_for(std::chrono::seconds(30));

    // Останавливаем симуляцию
    game.stopSimulation();

    // Выводим список выживших NPC
    std::cout << "\n--- Выжившие NPC ---" << std::endl;
    game.printNpcs();

    return 0;
}
