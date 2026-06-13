#ifndef MINIGIN_LEVELSTRUCT_H
#define MINIGIN_LEVELSTRUCT_H
#include <string>
#include "glm/glm.hpp"
namespace DigDug
{
    struct LevelData
    {
        std::string tilemapSprites;
        std::string tilemapIndex;
        std::string EnemyPooka;
        std::string EnemyFygar;
        glm::vec3 PlayerPos;

    };

}
#endif //MINIGIN_LEVELSTRUCT_H