#pragma once
#include "Sprite.h"

namespace Engine {

class Collision {
public:
    // AABB kontrolü
    static bool AABB(const Sprite& a, const Sprite& b);
    static void resolveAABB(Sprite& a, const Sprite& b);
};

} // namespace Engine
