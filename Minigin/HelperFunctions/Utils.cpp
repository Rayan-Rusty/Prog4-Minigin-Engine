//
// Created by omen on 23/04/2026.
//

#include "Utils.h"


bool dae::CheckOverlap(const SDL_FRect& A , const SDL_FRect& B)
{
    //AABB collisions for rectangles
    bool CollisionX{A.x + A.w >= B.x && B.x + B.w >= A.x};
    bool CollisionY{A.y + A.h >= B.y && B.y + B.h >= A.y};
    return CollisionX && CollisionY;
}

bool dae::CheckOverlap(const dae::Sphere& A, const SDL_FRect& B)
{

    glm::vec3 center{A.pos + A.radius};

    glm::vec3 halfExtend{B.x / 2.0f, B.h / 2.0f, 0.f};
    glm::vec3 aabbCenter{B.x + halfExtend.x, B.y + halfExtend.y , 0.f};

    glm::vec3 difference{center - aabbCenter};
    glm::vec3 clamped{glm::clamp(difference, -halfExtend, halfExtend)};

    glm::vec3 closest{aabbCenter + clamped};
    difference = closest - center;

    return glm::length(difference) < A.radius;
}