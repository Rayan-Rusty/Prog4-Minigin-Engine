//
// Created by omen on 23/04/2026.
//

#ifndef MINIGIN_SPRITEANIMATIONCOMPONENT_H
#define MINIGIN_SPRITEANIMATIONCOMPONENT_H
#include <memory>
#include <SDL3/SDL.h>

#include "Component.h"
#include "Texture2D.h"

namespace dae
{

    class Font;
    class Texture2D;
    class SpriteAnimationComponent final : public Component
    {
    public:
        SpriteAnimationComponent(GameObject* owner,int rows, int columns,const std::string& TextureFile);
        ~SpriteAnimationComponent();







        std::type_index GetType() const override;

        void Render() const override;


    private:

        bool m_needsUpdate{false};
        std::shared_ptr<Texture2D> m_Texture{nullptr};
        int m_rows{};
        int m_cols{};
    };
}




#endif //MINIGIN_SPRITEANIMATIONCOMPONENT_H