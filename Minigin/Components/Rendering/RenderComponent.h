
#include "Component.h"

#include "Renderer.h"
#include "ResourceManager.h"

namespace dae
{
    class SpriteAnimationComponent;
    class Texture2D;
    class RenderComponent final : public Component
    {
    public:
        explicit RenderComponent(GameObject* owner);
        ~RenderComponent() override = default;
        void SetTextureFilePath(const std::string& TextureFile);
        void SetTexture(std::shared_ptr<Texture2D> Texture);
        std::shared_ptr<Texture2D> GetTexture() const;
        void SetIsUI(bool isUI);
        void Render() const override;

        std::type_index GetType() const override;
        void SetDestSizeOverride(float w, float h) { m_DestOverrideW = w; m_DestOverrideH = h; }
        void ClearDestSizeOverride()               { m_DestOverrideW = -1.f; m_DestOverrideH = -1.f; }
        void SetDestPositionOffset(float x, float y) { m_DestOffsetX = x; m_DestOffsetY = y; }
        void ClearDestPositionOffset()               { m_DestOffsetX = 0.f; m_DestOffsetY = 0.f; }

        RenderComponent(const RenderComponent& other) = delete;
        RenderComponent(RenderComponent&& other) = delete;
        RenderComponent& operator=(const RenderComponent& other) = delete;
        RenderComponent& operator=(RenderComponent&& other) = delete;
    private:

        std::shared_ptr<Texture2D> m_Texture{nullptr};
        bool m_isUI{false};

        float m_DestOverrideW{ -1.f };
        float m_DestOverrideH{ -1.f };
        float m_DestOffsetX{ 0.f };
        float m_DestOffsetY{ 0.f };
    };
}



