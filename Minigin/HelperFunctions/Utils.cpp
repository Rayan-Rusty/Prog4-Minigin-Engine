//
// Created by omen on 23/04/2026.
//

#include "Utils.h"


bool Utils::CheckOverlap(const dae::Rect& A, const dae::Rect& B)
{
    //AABB collisions for rectangles
    bool CollisionX{A.pos.x + A.size.x >= B.pos.x && B.pos.x + B.size.x >= A.pos.x};
    bool CollisionY{A.pos.y + A.size.y >= B.pos.y && B.pos.y + B.size.y >= A.pos.y};
    return CollisionX && CollisionY;
}

bool Utils::CheckOverlap(const dae::Sphere& A, const dae::Rect& B)
{

    glm::vec3 center{A.pos + A.radius};

    glm::vec3 halfExtend{B.pos.x / 2.0f, B.size.y / 2.0f, 0.f};
    glm::vec3 aabbCenter{B.pos.x + halfExtend.x, B.pos.y + halfExtend.y , 0.f};

    glm::vec3 difference{center - aabbCenter};
    //glm::vec3 clamped{glm::clamp(difference.x, -halfExtend, halfExtend)};

    glm::vec3 closest{aabbCenter}; // + clamped};
    difference = closest - center;
    return glm::length(difference) < A.radius;
}