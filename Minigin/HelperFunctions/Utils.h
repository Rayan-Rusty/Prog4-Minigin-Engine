//
// Created by omen on 23/04/2026.
//

#ifndef MINIGIN_UTILS_H
#define MINIGIN_UTILS_H
#include "DataStructs.h"
#include "SDL3/SDL_rect.h"

namespace dae {
    bool CheckOverlap(const SDL_FRect& A , const SDL_FRect& B);
    bool CheckOverlap(const dae::Sphere& A , const SDL_FRect& B);
}
#endif //MINIGIN_UTILS_H