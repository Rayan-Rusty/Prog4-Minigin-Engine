#pragma once
#include <string>
#include <memory>
#include "GameObject.h"
#include "Transform.h"
#include <SDL3/SDL.h>

#include "Component.h"

namespace dae
{
	class FPSComponent;
	class Font;
	class Texture2D;
	class TextComponent final : public Component
	{
	public:

		TextComponent(GameObject* owner ,const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255, 255, 255, 255 });


		void Update(float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);

		std::type_index GetType() const override;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		//Exercise week 1

		void AddFPSComponent();
		void RemoveFPSComponent();
	private:
		bool m_needsUpdate{};
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };

		std::shared_ptr<Font> m_font{};
		std::shared_ptr<Texture2D> m_textTexture{};
		std::unique_ptr<FPSComponent> m_fpsComponent;
		bool m_hasFPSComponent{false};
	};
}
