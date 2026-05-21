
#include "RenderComponent.h"

#include "SpriteAnimationComponent.h"
#include "../Textures/Texture2D.h"
#include "../GameObject/GameObject.h"


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

    if (!m_Texture) return;
    auto spriteComp = GetOwner()->GetComponent<SpriteAnimationComponent>();
    const auto& pos = GetOwner()->GetWorldPosition();
    const auto& scale = GetOwner()->GetTransform().GetScale();

    SDL_FRect dst{};
    SDL_FRect src{};
    dst.x = pos.x;
    dst.y = pos.y;

    if (spriteComp)
    {
        const auto& srcComp = spriteComp->GetSourceRect();
        dst.w = srcComp.w * scale.x;
        dst.h = srcComp.h * scale.y;
        src = spriteComp->GetSourceRect();
    }
    else
    {
        dst.w = m_Texture->GetSize().x * scale.x;
        dst.h = m_Texture->GetSize().y * scale.y;
        src = {0,0, m_Texture->GetSize().x , m_Texture->GetSize().y};
    }


    Renderer::GetInstance().RenderTexture(*m_Texture, dst, src);


}

std::type_index dae::RenderComponent::GetType() const
{
    return typeid(RenderComponent);
}
