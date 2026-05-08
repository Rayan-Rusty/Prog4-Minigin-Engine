
#include "RenderComponent.h"

#include "SpriteAnimationComponent.h"
#include "Texture2D.h"
#include "../GameObject.h"


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

    SDL_FRect dst{
        pos.x,
        pos.y,
        m_Texture->GetSize().x * scale.x,
        m_Texture->GetSize().y * scale.y
    };


    SDL_FRect src;

    if (spriteComp)
        src = spriteComp->GetSourceRect();
    else
        src = {0,0, m_Texture->GetSize().x , m_Texture->GetSize().y};



    Renderer::GetInstance().Submit(m_isUI, m_Texture, dst, src);
}

std::type_index dae::RenderComponent::GetType() const
{
    return typeid(RenderComponent);
}
