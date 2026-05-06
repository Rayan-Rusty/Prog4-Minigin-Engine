
#include "RenderComponent.h"

#include "SpriteAnimationComponent.h"
#include "Texture2D.h"
#include "../GameObject.h"


dae::RenderComponent::RenderComponent(GameObject *owner)
    : Component(owner)
{
    m_spriteComp = owner->GetComponent<SpriteAnimationComponent>();
}


void dae::RenderComponent::SetTextureFilePath(const std::string &TextureFile)
{
    m_Texture = ResourceManager::GetInstance().LoadTexture(TextureFile) ;
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> Texture)
{
    m_Texture = Texture;
}

void dae::RenderComponent::SetIsUI(bool isUI) {
    m_isUI = isUI;
}

void dae::RenderComponent::Render() const
{

    if (!m_Texture) return;

    const auto& pos = GetOwner()->GetWorldPosition();
    SDL_FRect dst{pos.x , pos.y , m_Texture->GetSize().x , m_Texture->GetSize().y};


    SDL_FRect src;

    if (m_spriteComp)
        src = m_spriteComp->GetSourceRect();
    else
        src = {0,0, m_Texture->GetSize().x , m_Texture->GetSize().y};



    Renderer::GetInstance().Submit(m_isUI, m_Texture, dst, src);
}

std::type_index dae::RenderComponent::GetType() const
{
    return typeid(RenderComponent);
}
