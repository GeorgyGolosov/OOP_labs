#include "npc.h"
#include "visitor.h"

void Bandit::accept(NpcVisitor& visitor) {
    visitor.visit(*this);
}

void Elf::accept(NpcVisitor& visitor) {
    visitor.visit(*this);
}

void Squirrel::accept(NpcVisitor& visitor) {
    visitor.visit(*this);
}
