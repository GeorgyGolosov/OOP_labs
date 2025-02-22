#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <thread>
#include <atomic>
#include "npc.h"
#include "factory.h"
#include "observer.h"
#include "visitor.h"

class Game {
    std::vector<std::shared_ptr<Npc>> npcs;
    std::vector<std::shared_ptr<Observer>> observers;

    mutable std::shared_mutex npcsMutex; // Защита вектора NPC
    std::mutex combatQueueMutex;
    std::condition_variable combatCv;
    // Очередь заданий для боя (пара NPC)
    std::queue<std::pair<std::shared_ptr<Npc>, std::shared_ptr<Npc>>> combatQueue;
    std::atomic<bool> simulationRunning{false};

public:
    // Существующие функции
    void addNpc(std::shared_ptr<Npc> npc) {
        if (npc->getX() >= 0 && npc->getX() <= 500 &&
            npc->getY() >= 0 && npc->getY() <= 500) {
            std::unique_lock<std::shared_mutex> lock(npcsMutex);
            npcs.push_back(npc);
        }
    }

    void addObserver(std::shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    void notifyKill(const std::string& killer, const std::string& victim) {
        for (auto& observer : observers) {
            observer->onKill(killer, victim);
        }
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        std::shared_lock<std::shared_mutex> lock(npcsMutex);
        for (const auto& npc : npcs) {
            file << npc->getType() << " " << npc->getName() << " "
                 << npc->getX() << " " << npc->getY() << std::endl;
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }
        std::unique_lock<std::shared_mutex> lock(npcsMutex);
        npcs.clear();
        std::string type, name;
        int x, y;
        while (file >> type >> name >> x >> y) {
            // Проверяем координаты согласно условию (0<=x<=500, 0<=y<=500)
            if (x >= 0 && x <= 500 && y >= 0 && y <= 500) {
                npcs.push_back(NpcFactory::createNpc(type, name, x, y));
            }
        }
        if (file.bad()) {
            throw std::runtime_error("Error occurred while reading file: " + filename);
        }
    }

    void printNpcs() const {
        std::shared_lock<std::shared_mutex> lock(npcsMutex);
        for (const auto& npc : npcs) {
            std::cout << npc->getEmojiType() << " " << npc->getName()
                     << " at (" << npc->getX() << "," << npc->getY() << ")"
                     << std::endl;
        }
    }

    void startSimulation();
    void stopSimulation();
    // Функции, запускаемые в потоках
    void simulationMovement();
    void simulationCombat();
    void simulationPrintMap();

    // Для получения копии списка NPC с блокировкой
    std::vector<std::shared_ptr<Npc>> getNpcs() const {
        std::shared_lock<std::shared_mutex> lock(npcsMutex);
        return npcs;
    }
};
