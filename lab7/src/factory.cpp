#include "factory.h"
#include "npc.h"
#include <stdexcept>

std::shared_ptr<Npc> NpcFactory::createNpc(const std::string& type, const std::string& name, int x, int y) {
    if (type == "Белка") return std::make_shared<Squirrel>(name, x, y);
    if (type == "Эльф") return std::make_shared<Elf>(name, x, y);
    if (type == "Разбойник") return std::make_shared<Bandit>(name, x, y);
    throw std::runtime_error("Unknown NPC type");
}
