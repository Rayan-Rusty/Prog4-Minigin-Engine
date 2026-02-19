
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
        //TODO Needs to be done in here instead of TextComponent
        const auto& pos {GetOwner()->GetTransform().GetPosition()};
        Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
    }
}

std::type_index dae::RenderComponent::GetType() const
{
    return typeid(RenderComponent);
}
