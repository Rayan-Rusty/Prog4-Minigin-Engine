//
// Created by omen on 23/04/2026.
//

#ifndef MINIGIN_DATATYPES_H
#define MINIGIN_DATATYPES_H
#include <glm/glm.hpp>
namespace dae
{
    struct Rect
    {
        glm::vec3 pos{};
        glm::vec3 size{};
    };

    struct Sphere
    {
        glm::vec3 pos{};
        float radius{};
    };


}
#endif //MINIGIN_DATATYPES_H