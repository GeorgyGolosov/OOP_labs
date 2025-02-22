#pragma once
#include "npc.h"

class NpcVisitor {
public:
    virtual void visit(Bandit& bandit) = 0;
    virtual void visit(Elf& elf) = 0;
    virtual void visit(Squirrel& squirrel) = 0;
    virtual ~NpcVisitor() = default;
};

class CombatVisitor : public NpcVisitor {
    Npc* opponent;
    double range;
    bool killed;
public:
    CombatVisitor(Npc* opponent, double range) : opponent(opponent), range(range), killed(false) {}
    void visit(Bandit& bandit) override;
    void visit(Elf& elf) override;
    void visit(Squirrel& squirrel) override;
    bool isKilled() const { return killed; }
};
