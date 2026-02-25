#pragma once
#include "Component.h"

#include "Renderer.h"
#include "ResourceManager.h"

namespace dae
{
    class Texture2D;
    class RenderComponent : public Component
    {
    public:
        RenderComponent(GameObject* owner);
        void SetTextureFilePath(const std::string& TextureFile);
        void SetTexture(std::shared_ptr<Texture2D> Texture);
        void Render() const override;

        std::type_index GetType() const override;

        RenderComponent(const RenderComponent& other) = delete;
        RenderComponent(RenderComponent&& other) = delete;
        RenderComponent& operator=(const RenderComponent& other) = delete;
        RenderComponent& operator=(RenderComponent&& other) = delete;
    private:
        std::shared_ptr<Texture2D> m_Texture{nullptr};
    };
}



