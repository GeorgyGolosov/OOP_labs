#pragma once
#include "npc.h"
#include <memory>

class NpcFactory {
public:
    static std::shared_ptr<Npc> createNpc(const std::string& type, const std::string& name, int x, int y);
};

