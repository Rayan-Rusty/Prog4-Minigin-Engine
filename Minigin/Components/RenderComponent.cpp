
#include "RenderComponent.h"

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

void dae::RenderComponent::SetIsUI(bool isUI) {
    m_isUI = isUI;
}

void dae::RenderComponent::Render() const
{

    if (!m_Texture) return;

    const auto& pos = GetOwner()->GetWorldPosition();

    SDL_FRect dst;
    dst.x = pos.x;
    dst.y = pos.y;

    auto size = m_Texture->GetSize();
    dst.w = size.x;
    dst.h = size.y;

    Renderer::GetInstance().Submit(m_Texture, dst, m_isUI);
}

std::type_index dae::RenderComponent::GetType() const
{
    return typeid(RenderComponent);
}
