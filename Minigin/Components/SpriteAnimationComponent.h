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

        void Update(float deltaTime) override;
        const SDL_FRect& GetSourceRect() const;



        std::type_index GetType() const override;


    private:


        SDL_FRect m_Src{};
        int m_CurrentFrame{};
        float m_Timer{};
        bool m_NeedsUpdate{false};
        std::shared_ptr<Texture2D> m_Texture{nullptr};
        float m_FrameTime = 0.1f;

        int m_Rows{};
        int m_Cols{};
    };
}




#endif //MINIGIN_SPRITEANIMATIONCOMPONENT_H