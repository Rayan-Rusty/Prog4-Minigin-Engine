
#include "RenderComponent.h"

#include "SpriteAnimationComponent.h"
#include "Texture2D.h"
#include "GameObject.h"


dae::RenderComponent::RenderComponent(GameObject *owner)
    : Component(owner)
{

}


void dae::RenderComponent::SetTextureFilePath(const std::string &TextureFile)
{
    m_Texture = ResourceManager::GetInstance().LoadTexture(TextureFile) ;
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> Texture)
{
    m_Texture = Texture;
}

std::shared_ptr<dae::Texture2D> dae::RenderComponent::GetTexture() const
{
    return m_Texture;
}

void dae::RenderComponent::SetIsUI(bool isUI) {
    m_isUI = isUI;
}

void dae::RenderComponent::Render() const
{

    if (!m_Texture || !GetOwner()->GetRenderObject()) return;

    auto spriteComp = GetOwner()->GetComponent<SpriteAnimationComponent>();
    const auto& pos = GetOwner()->GetWorldPosition();
    const auto& scale = GetOwner()->GetTransform().GetScale();

    SDL_FRect dst{};
    SDL_FRect src{};
    dst.x = pos.x + m_DestOffsetX;
    dst.y = pos.y + m_DestOffsetY;

    if (spriteComp)
    {
        const auto& srcComp = spriteComp->GetSourceRect();
        dst.w = srcComp.w * std::abs(scale.x);
        dst.h = srcComp.h * std::abs(scale.y);
        src = spriteComp->GetSourceRect();
    }
    else
    {
        dst.w = m_Texture->GetSize().x * std::abs(scale.x);
        dst.h = m_Texture->GetSize().y * std::abs(scale.y);
        src = {0,0, m_Texture->GetSize().x , m_Texture->GetSize().y};
    }

    if (m_DestOverrideW >= 0.f) dst.w = m_DestOverrideW;
    if (m_DestOverrideH >= 0.f) dst.h = m_DestOverrideH;


    SDL_FlipMode flip = SDL_FLIP_NONE;
    if (spriteComp)
    {
        int flipFlags = SDL_FLIP_NONE;
        if (spriteComp->GetFlipHorizontal()) flipFlags |= SDL_FLIP_HORIZONTAL;
        if (spriteComp->GetFlipVertical())   flipFlags |= SDL_FLIP_VERTICAL;
        flip = static_cast<SDL_FlipMode>(flipFlags);
    }



    Renderer::GetInstance().RenderTexture(*m_Texture, dst, src , flip);


}

std::type_index dae::RenderComponent::GetType() const
{
    return typeid(RenderComponent);
}
