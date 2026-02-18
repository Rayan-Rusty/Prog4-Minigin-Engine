#pragma once
#include "Component.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ResourceManager.h"

namespace dae
{
    class RenderComponent : public Component
    {
    public:
        RenderComponent(GameObject* owner);
        void SetTextureFile(const std::string& TextureFile);
        void Render() const override;

        std::type_index GetType() const override;
    private:
        std::shared_ptr<Texture2D> m_Texture{nullptr};
    };
}



