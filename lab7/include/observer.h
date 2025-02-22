#pragma once
#include <string>
#include <fstream>
#include <iostream>

class Observer {
public:
    virtual void onKill(const std::string& killer, const std::string& victim) = 0;
    virtual ~Observer() = default;
};

class ConsoleObserver : public Observer {
public:
    void onKill(const std::string& killer, const std::string& victim) override {
        std::cout << killer << " 💀 " << victim << std::endl;
    }
};

class FileObserver : public Observer {
    std::ofstream file;
public:
    FileObserver() : file("log.txt", std::ios::app) {}
    void onKill(const std::string& killer, const std::string& victim) override {
        file << killer << " 💀 " << victim << std::endl;
    }
};

