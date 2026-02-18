
#include "RenderComponent.h"

#include "GameObject.h"


dae::RenderComponent::RenderComponent(GameObject *owner)
    : Component(owner)
{
}


void dae::RenderComponent::SetTextureFile(const std::string &TextureFile)
{
    m_Texture = ResourceManager::GetInstance().LoadTexture(TextureFile) ;
}

void dae::RenderComponent::Render() const
{

    if (m_Texture)
    {
        const auto& pos {m_owner->GetTransform().GetPosition()};
        Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
    }
}
