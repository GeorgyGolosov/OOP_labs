#pragma once
#include <string>
#include <memory>
#include <cmath>

class NpcVisitor;

class Npc {
protected:
    std::string name;
    int x, y;
    bool alive;
public:
    Npc(const std::string& name, int x, int y) : name(name), x(x), y(y), alive(true) {}
    virtual ~Npc() = default;

    virtual void accept(NpcVisitor& visitor) = 0;
    virtual std::string getEmojiType() const = 0;
    virtual std::string getType() const = 0;

    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    double getDistance(const Npc& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return std::sqrt(dx*dx + dy*dy);
    }

    // Новые методы для симуляции:
    bool isAlive() const { return alive; }
    void kill() { alive = false; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
};

// Остальные классы (Bandit, Elf, Squirrel) остаются без изменений, поскольку наследуют поведение.
class Bandit : public Npc {
public:
    Bandit(const std::string& name, int x, int y) : Npc(name, x, y) {}
    void accept(NpcVisitor& visitor) override;
    std::string getEmojiType() const override { return "🔫"; }
    std::string getType() const override { return "Разбойник"; }
};

class Elf : public Npc {
public:
    Elf(const std::string& name, int x, int y) : Npc(name, x, y) {}
    void accept(NpcVisitor& visitor) override;
    std::string getEmojiType() const override { return "🏹"; }
    std::string getType() const override { return "Эльф"; }
};

class Squirrel : public Npc {
public:
    Squirrel(const std::string& name, int x, int y) : Npc(name, x, y) {}
    void accept(NpcVisitor& visitor) override;
    std::string getEmojiType() const override { return "🐿️"; }
    std::string getType() const override { return "Белка"; }
};
