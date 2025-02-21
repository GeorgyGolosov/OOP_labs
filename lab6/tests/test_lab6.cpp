#include <gtest/gtest.h>
#include "game.h"
#include "factory.h"
#include "npc.h"
#include "visitor.h"
#include "observer.h"
#include <sstream>
#include <fstream>
#include <cstdio>

// Test NPC creation and basic properties
TEST(NpcTest, BasicProperties) {
    auto bandit = std::make_shared<Bandit>("Bob", 100, 200);
    EXPECT_EQ(bandit->getName(), "Bob");
    EXPECT_EQ(bandit->getX(), 100);
    EXPECT_EQ(bandit->getY(), 200);
    EXPECT_EQ(bandit->getType(), "Разбойник");
    EXPECT_EQ(bandit->getEmojiType(), "🔫");
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

    // Попытка добавить NPC с недопустимыми координатами (не должна быть добавлена)
    auto invalidNpc = NpcFactory::createNpc("Разбойник", "Invalid", 600, 600);
    game.addNpc(invalidNpc);


    SUCCEED();
}

// Test Combat System
TEST(GameTest, CombatSystem) {
    Game game;

    // Пара 1: Эльф vs Разбойник -> Разбойник погибает.
    game.addNpc(NpcFactory::createNpc("Эльф", "Elf1", 10, 10));
    game.addNpc(NpcFactory::createNpc("Разбойник", "Bandit1", 10, 10));

    // Пара 2: Белка vs Эльф -> Эльф погибает.
    game.addNpc(NpcFactory::createNpc("Белка", "Squirrel1", 20, 20));
    game.addNpc(NpcFactory::createNpc("Эльф", "Elf2", 20, 20));

    // Пара 3: Разбойник vs Белка -> Белка погибает.
    game.addNpc(NpcFactory::createNpc("Разбойник", "Bandit2", 30, 30));
    game.addNpc(NpcFactory::createNpc("Белка", "Squirrel2", 30, 30));

    game.combat(20.0);  // Все NPC находятся в пределах дистанции боя


    SUCCEED();
}

// Test Observer Pattern
class TestObserver : public Observer {
public:
    std::vector<std::pair<std::string, std::string>> kills;
    void onKill(const std::string& killer, const std::string& victim) override {
        kills.push_back({killer, victim});
    }
};

TEST(ObserverTest, KillNotification) {
    Game game;
    auto observer = std::make_shared<TestObserver>();
    game.addObserver(observer);

    // Используем пару, приводящую к убийству:
    // Эльф vs Разбойник -> Разбойник погибает.
    auto elf = NpcFactory::createNpc("Эльф", "Elf1", 10, 10);
    auto bandit = NpcFactory::createNpc("Разбойник", "Bandit1", 10, 10);

    game.addNpc(elf);
    game.addNpc(bandit);

    game.combat(20.0);

    EXPECT_FALSE(observer->kills.empty());
}

// Test File Operations
TEST(GameTest, SaveLoadOperations) {
    Game game;
    const std::string testFile = "test_save.txt";

    // Добавляем несколько NPC разных типов
    game.addNpc(NpcFactory::createNpc("Белка", "Squirrel1", 100, 100));
    game.addNpc(NpcFactory::createNpc("Разбойник", "Bandit1", 200, 200));
    game.addNpc(NpcFactory::createNpc("Эльф", "Elf1", 300, 300));

    // Тест сохранения
    game.saveToFile(testFile);
    EXPECT_TRUE(std::ifstream(testFile).good());

    // Тест загрузки
    Game loadedGame;
    loadedGame.loadFromFile(testFile);

    // Очистка временного файла
    std::remove(testFile.c_str());

    // Тест загрузки несуществующего файла
    EXPECT_THROW(game.loadFromFile("nonexistent.txt"), std::runtime_error);
}

// Test Combat Visitor according to new rules
TEST(VisitorTest, CombatRules) {
    // Тест: Разбойник vs Эльф -> Разбойник погибает (правило: Эльфы убивают Разбойников)
    {
        auto bandit = std::make_shared<Bandit>("Bandit1", 0, 0);
        auto elf = std::make_shared<Elf>("Elf1", 0, 0);
        CombatVisitor visitor1(elf.get(), 10.0);
        bandit->accept(visitor1);
        EXPECT_TRUE(visitor1.isKilled());  // Разбойник должен погибнуть
    }
    // Тест: Эльф vs Белка -> Эльф погибает (правило: Белки убивают Эльфов)
    {
        auto elf = std::make_shared<Elf>("Elf2", 0, 0);
        auto squirrel = std::make_shared<Squirrel>("Squirrel1", 0, 0);
        CombatVisitor visitor2(squirrel.get(), 10.0);
        elf->accept(visitor2);
        EXPECT_TRUE(visitor2.isKilled());  // Эльф должен погибнуть
    }
    // Тест: Белка vs Разбойник -> Белка погибает (правило: Разбойники убивают Белок)
    {
        auto squirrel = std::make_shared<Squirrel>("Squirrel2", 0, 0);
        auto bandit = std::make_shared<Bandit>("Bandit2", 0, 0);
        CombatVisitor visitor3(bandit.get(), 10.0);
        squirrel->accept(visitor3);
        EXPECT_TRUE(visitor3.isKilled());  // Белка должна погибнуть
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
