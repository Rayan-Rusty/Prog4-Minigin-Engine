//
// Created by omen on 23/04/2026.
//

#ifndef MINIGIN_UTILS_H
#define MINIGIN_UTILS_H
#include "DataTypes.h"
namespace Utils {
    bool CheckOverlap(const dae::Rect& A , const dae::Rect& B);
    bool CheckOverlap(const dae::Sphere& A , const dae::Rect& B);
}
#endif //MINIGIN_UTILS_H