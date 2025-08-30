#include "Collision.h"

namespace Engine {

bool Collision::AABB(const Sprite& a, const Sprite& b) {
    auto A = a.getAABB();
    auto B = b.getAABB();

    bool overlapX = A.x + A.z >= B.x && B.x + B.z >= A.x;
    bool overlapY = A.y + A.w >= B.y && B.y + B.w >= A.y;

    return overlapX && overlapY;
}
void Collision::resolveAABB(Sprite& a, const Sprite& b) {
    
    auto A = a.getAABB();
    auto B = b.getAABB();

    float overlapLeft = (A.x + A.z) - B.x;
    float overlapRight = (B.x + B.z) - A.x;
    float overlapTop = (A.y + A.w) - B.y;
    float overlapBottom = (B.y + B.w) - A.y;

    bool fromLeft = std::abs(overlapLeft) < std::abs(overlapRight);
    bool fromTop = std::abs(overlapTop) < std::abs(overlapBottom);

    float minOverlapX = fromLeft ? overlapLeft : -overlapRight;
    float minOverlapY = fromTop ? overlapTop : -overlapBottom;

    if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
        a.setPosition({a.getPosition().x - minOverlapX, a.getPosition().y});
    } else {
        a.setPosition({a.getPosition().x, a.getPosition().y - minOverlapY});
    }


} // namespace Engine
}