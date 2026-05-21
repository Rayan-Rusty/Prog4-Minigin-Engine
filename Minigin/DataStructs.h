//
// Created by omen on 23/04/2026.
//

#ifndef MINIGIN_DATATYPES_H
#define MINIGIN_DATATYPES_H
#include <glm/glm.hpp>
namespace dae
{
    struct Rectf
    {
        glm::vec3 pos{0,0,0};
        glm::vec3 size{0,0,0};
    };

    struct Sphere
    {
        glm::vec3 pos{0,0,0};
        float radius{0};
    };


}
#endif //MINIGIN_DATATYPES_H