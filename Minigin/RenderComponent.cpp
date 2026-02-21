
#include "RenderComponent.h"

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
