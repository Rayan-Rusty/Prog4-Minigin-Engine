//
// Created by omen on 23/04/2026.
//

#ifndef MINIGIN_SPRITEANIMATIONCOMPONENT_H
#define MINIGIN_SPRITEANIMATIONCOMPONENT_H

#include <vector>
#include <SDL3/SDL.h>

#include "../BaseComp/Component.h"
#include "Texture2D.h"

namespace dae
{

    class Font;
    class Texture2D;
    class SpriteAnimationComponent final : public Component
    {
    public:
        SpriteAnimationComponent(GameObject* owner,int rows, int columns);
        ~SpriteAnimationComponent();

        void Update(float deltaTime) override;
        const SDL_FRect& GetSourceRect() const;

        void SetFlipHorizontal(bool flip);
        bool GetFlipHorizontal();

        void SetFlipVertical(bool flip);
        bool GetFlipVertical();
        //void SetAnimation(int row, int startCol, int endCol,  int frameWidth = 1, int frameHeight = 1);
        void SetAnimation(const std::vector<SDL_FRect>& Sizes , float duration , bool looping = true);
        //SetCustomAnimation(std::vector<SDL_FRect>);
        std::type_index GetType() const override;


    private:

        struct SpriteFrame
        {
            SDL_FRect src;
            float duration;
        };



        struct AnimationClip
        {
            std::vector<SpriteFrame> spritesFrames;
            bool looping{true}; //TODO make it so that you can loop things or not through this
        };

        SDL_FRect m_Src{};
        int m_CurrentFrame{0};
        float m_Timer{0.f};

        float m_FrameTime = 0.2f;

        AnimationClip m_CurrentAnim{};

        int m_CurrentFrameIndex{0};
        bool m_FlipHorizontal{false};
        bool m_FlipVertical{false};
    };
}




#endif //MINIGIN_SPRITEANIMATIONCOMPONENT_H