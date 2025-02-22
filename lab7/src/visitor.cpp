#include "visitor.h"
#include "npc.h"

void CombatVisitor::visit(Bandit& bandit) {
    // Если противник - Эльф, то Разбойник погибает
    if (dynamic_cast<Elf*>(opponent)) {
        killed = true;
    }
}

void CombatVisitor::visit(Elf& elf) {
    // Если противник - Белка, то Эльф погибает
    if (dynamic_cast<Squirrel*>(opponent)) {
        killed = true;
    }
}

void CombatVisitor::visit(Squirrel& squirrel) {
    // Если противник - Разбойник, то Белка погибает
    if (dynamic_cast<Bandit*>(opponent)) {
        killed = true;
    }
}
