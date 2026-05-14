//
// Created by omen on 30/04/2026.
//

#ifndef MINIGIN_IGAME_H
#define MINIGIN_IGAME_H


namespace DigDug
{
    class IGame
    {
    public:
        virtual ~IGame() = default;

        virtual void Init() = 0;
        virtual void Update(float deltaTime) = 0;
        virtual void Draw() const = 0;
    };
}

#endif //MINIGIN_IGAME_H