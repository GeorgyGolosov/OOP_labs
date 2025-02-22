#include "game.h"
#include <iostream>
#include <random>
#include <cmath>
#include <chrono>
#include <thread>

// Размер карты: 100 x 100
const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;

// Вспомогательные функции для определения дистанции передвижения и дистанции убийства
int getMovementDistance(const std::shared_ptr<Npc>& npc) {
    if (npc->getType() == "Белка") return 5;
    if (npc->getType() == "Эльф") return 10;
    if (npc->getType() == "Разбойник") return 10;
    return 0;
}

int getKillDistance(const std::shared_ptr<Npc>& npc) {
    if (npc->getType() == "Белка") return 5;
    if (npc->getType() == "Эльф") return 50;
    if (npc->getType() == "Разбойник") return 10;
    return 0;
}

// Генераторы случайных чисел
std::random_device rd;
std::mt19937 rng(rd());
std::uniform_real_distribution<double> angleDist(0, 2 * M_PI);
std::uniform_int_distribution<int> dieDist(1, 6);

void Game::simulationMovement() {
    while (simulationRunning.load()) {
        {
            // Перемещаем каждого живого NPC
            std::unique_lock<std::shared_mutex> lock(npcsMutex);
            for (auto& npc : npcs) {
                if (!npc->isAlive()) continue;
                int moveDist = getMovementDistance(npc);
                double angle = angleDist(rng);
                int dx = static_cast<int>(moveDist * std::cos(angle));
                int dy = static_cast<int>(moveDist * std::sin(angle));
                int newX = npc->getX() + dx;
                int newY = npc->getY() + dy;
                // Ограничение по границам карты
                if (newX < 0) newX = 0;
                if (newX > MAP_WIDTH) newX = MAP_WIDTH;
                if (newY < 0) newY = 0;
                if (newY > MAP_HEIGHT) newY = MAP_HEIGHT;
                npc->setX(newX);
                npc->setY(newY);
            }
            // Проверяем пары NPC, находящиеся на расстоянии убийства
            for (size_t i = 0; i < npcs.size(); ++i) {
                for (size_t j = i + 1; j < npcs.size(); ++j) {
                    auto& npc1 = npcs[i];
                    auto& npc2 = npcs[j];
                    if (!npc1->isAlive() || !npc2->isAlive()) continue;
                    double distance = npc1->getDistance(*npc2);
                    if (distance <= getKillDistance(npc1) || distance <= getKillDistance(npc2)) {
                        std::lock_guard<std::mutex> lockQueue(combatQueueMutex);
                        combatQueue.push({npc1, npc2});
                        combatCv.notify_one();
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Game::simulationCombat() {
    while (simulationRunning.load() || !combatQueue.empty()) {
        std::pair<std::shared_ptr<Npc>, std::shared_ptr<Npc>> task;
        {
            std::unique_lock<std::mutex> lock(combatQueueMutex);
            combatCv.wait(lock, [this]{ return !combatQueue.empty() || !simulationRunning.load(); });
            if (combatQueue.empty()) continue;
            task = combatQueue.front();
            combatQueue.pop();
        }
        {
            std::shared_lock<std::shared_mutex> lock(npcsMutex);
            if (!task.first->isAlive() || !task.second->isAlive())
                continue;
        }
        // Каждый NPC бросает 6-гранный кубик для атаки и защиты
        int attack1 = dieDist(rng);
        int defense1 = dieDist(rng);
        int attack2 = dieDist(rng);
        int defense2 = dieDist(rng);

        bool npc1KillsNpc2 = (attack1 > defense2);
        bool npc2KillsNpc1 = (attack2 > defense1);

        {
            std::unique_lock<std::shared_mutex> lock(npcsMutex);
            if (npc1KillsNpc2 && task.second->isAlive()) {
                task.second->kill();
                notifyKill(task.first->getEmojiType() + " " + task.first->getName(),
                           task.second->getEmojiType() + " " + task.second->getName());
                std::cout << task.first->getEmojiType() << " " << task.first->getName()
                          << " убивает " << task.second->getEmojiType() << " " << task.second->getName()
                          << " (А:" << attack1 << " > З:" << defense2 << ")" << std::endl;
            }
            if (npc2KillsNpc1 && task.first->isAlive()) {
                task.first->kill();
                notifyKill(task.second->getEmojiType() + " " + task.second->getName(),
                           task.first->getEmojiType() + " " + task.first->getName());
                std::cout << task.second->getEmojiType() << " " << task.second->getName()
                          << " убивает " << task.first->getEmojiType() << " " << task.first->getName()
                          << " (А:" << attack2 << " > З:" << defense1 << ")" << std::endl;
            }
        }
    }
}

std::mutex coutMutex;

void Game::simulationPrintMap() {
    while (simulationRunning.load()) {
        {
            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::shared_lock<std::shared_mutex> lock(npcsMutex);
            std::cout << "\n--- Карта ---" << std::endl;
            for (auto& npc : npcs) {
                if (npc->isAlive()) {
                    std::cout << npc->getEmojiType() << " " << npc->getName()
                              << " (" << npc->getX() << "," << npc->getY() << ")" << std::endl;
                }
            }
            std::cout << "-------------" << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Game::startSimulation() {
    simulationRunning.store(true);
    // Запускаем потоки симуляции: движение, бой и печать карты.
    std::thread movementThread(&Game::simulationMovement, this);
    std::thread combatThread(&Game::simulationCombat, this);
    std::thread printThread(&Game::simulationPrintMap, this);
    // Потоки отсоединяем, чтобы они выполнялись в фоне
    movementThread.detach();
    combatThread.detach();
    printThread.detach();
}

void Game::stopSimulation() {
    simulationRunning.store(false);
    combatCv.notify_all();
}
