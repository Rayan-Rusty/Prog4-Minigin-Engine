//
// Created by omen on 06/05/2026.
//

#ifndef MINIGIN_POOKA_H
#define MINIGIN_POOKA_H
#include <memory>


class PookaState;

class Pooka
{
public:
    Pooka() = default;
    ~Pooka() = default;
    void Update(float dt);
    void Draw();
private:
    std::unique_ptr<PookaState> m_state;
};


#endif //MINIGIN_POOKA_H