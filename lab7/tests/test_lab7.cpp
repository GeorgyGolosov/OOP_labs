#include <gtest/gtest.h>
#include "game.h"
#include "factory.h"
#include "npc.h"
#include "visitor.h"
#include "observer.h"
#include <fstream>
#include <cstdio>
#include <thread>
#include <chrono>
#include <sstream>

// Test NPC creation and basic properties
TEST(NpcTest, BasicProperties) {
    auto bandit = std::make_shared<Bandit>("Bob", 100, 200);
    EXPECT_EQ(bandit->getName(), "Bob");
    EXPECT_EQ(bandit->getX(), 100);
    EXPECT_EQ(bandit->getY(), 200);
    EXPECT_EQ(bandit->getType(), "Разбойник");
    EXPECT_EQ(bandit->getEmojiType(), "🔫");
    EXPECT_TRUE(bandit->isAlive());
}

// Test distance calculation
TEST(NpcTest, DistanceCalculation) {
    auto npc1 = std::make_shared<Bandit>("Bob", 0, 0);
    auto npc2 = std::make_shared<Squirrel>("Sally", 3, 4);
    EXPECT_DOUBLE_EQ(npc1->getDistance(*npc2), 5.0);
}

// Test NPC Factory
TEST(FactoryTest, CreateNpc) {
    auto squirrel = NpcFactory::createNpc("Белка", "Squirrel1", 150, 150);
    auto elf = NpcFactory::createNpc("Эльф", "Elf1", 300, 300);
    auto bandit = NpcFactory::createNpc("Разбойник", "Bandit1", 50, 50);

    EXPECT_EQ(squirrel->getType(), "Белка");
    EXPECT_EQ(elf->getType(), "Эльф");
    EXPECT_EQ(bandit->getType(), "Разбойник");

    EXPECT_THROW(NpcFactory::createNpc("InvalidType", "Test", 0, 0), std::runtime_error);
}

// Test Game NPC management
TEST(GameTest, AddNpc) {
    Game game;
    auto npc = NpcFactory::createNpc("Разбойник", "Bob", 100, 200);
    game.addNpc(npc);
    auto npcsList = game.getNpcs();
    EXPECT_EQ(npcsList.size(), 1);

    // Попытка добавить NPC с недопустимыми координатами (0<=x<=500, 0<=y<=500)
    auto invalidNpc = NpcFactory::createNpc("Разбойник", "Invalid", 600, 600);
    game.addNpc(invalidNpc);
    npcsList = game.getNpcs();
    EXPECT_EQ(npcsList.size(), 1); // invalidNpc не должна быть добавлена
}

// Test File Operations
TEST(GameTest, SaveLoadOperations) {
    Game game;
    const std::string testFile = "test_save.txt";

    game.addNpc(NpcFactory::createNpc("Белка", "Squirrel1", 100, 100));
    game.addNpc(NpcFactory::createNpc("Разбойник", "Bandit1", 200, 200));
    game.addNpc(NpcFactory::createNpc("Эльф", "Elf1", 300, 300));

    game.saveToFile(testFile);
    EXPECT_TRUE(std::ifstream(testFile).good());

    Game loadedGame;
    loadedGame.loadFromFile(testFile);
    auto loadedList = loadedGame.getNpcs();
    EXPECT_EQ(loadedList.size(), 3);

    std::remove(testFile.c_str());
    EXPECT_THROW(game.loadFromFile("nonexistent.txt"), std::runtime_error);
}

// Test Simulation Movement:
// Запускаем симуляцию на короткое время и проверяем, что позиция NPC изменилась.
TEST(SimulationTest, Movement) {
    Game game;
    auto elf = NpcFactory::createNpc("Эльф", "ElfTest", 50, 50);
    game.addNpc(elf);

    game.startSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game.stopSimulation();

    EXPECT_NE(elf->getX(), 50);
    EXPECT_NE(elf->getY(), 50);
}

// Test Simulation Combat:
// Размещаем два NPC в одной точке, запускаем симуляцию и проверяем, что хотя бы один из них погиб.
TEST(SimulationTest, Combat) {
    Game game;
    auto elf = NpcFactory::createNpc("Эльф", "ElfCombat", 10, 10);
    auto bandit = NpcFactory::createNpc("Разбойник", "BanditCombat", 10, 10);
    game.addNpc(elf);
    game.addNpc(bandit);

    game.startSimulation();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    game.stopSimulation();

    bool oneDead = !elf->isAlive() || !bandit->isAlive();
    EXPECT_TRUE(oneDead);
}

// Test Simulation PrintMap:
// Перенаправляем вывод std::cout в stringstream, запускаем вывод карты на короткое время и проверяем наличие заголовка.
TEST(SimulationTest, PrintMap) {
    Game game;
    auto squirrel = NpcFactory::createNpc("Белка", "SquirrelPrint", 20, 20);
    game.addNpc(squirrel);

    std::stringstream buffer;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    std::thread printThread([&game]() {
        game.simulationPrintMap(); // Вывод карты в отдельном потоке
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(1100));
    game.stopSimulation();
    printThread.join();

    std::cout.rdbuf(oldCoutStreamBuf);
    std::string output = buffer.str();
    EXPECT_NE(output.find("--- Карта ---"), std::string::npos);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
