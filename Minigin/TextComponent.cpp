#include <stdexcept>
#include <utility>
#include <SDL3_ttf/SDL_ttf.h>
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "RenderComponent.h"

dae::TextComponent::TextComponent(GameObject* owner, std::string  text, std::shared_ptr<Font> font, const SDL_Color& color)
	: Component(owner), m_needsUpdate(true), m_text(std::move(text)), m_color(color), m_font(std::move(font)), m_textTexture(nullptr)
{ }

dae::TextComponent::TextComponent(GameObject *owner)
	: Component(owner) , m_needsUpdate(true), m_color({255, 255, 255, 255}) ,
m_font(dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36)), m_textTexture(nullptr)
{
	std::string text {"template text"};
	m_text = std::move(text);
}

void dae::TextComponent::Update(float )
{


	if (m_needsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_text.length(), m_color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_DestroySurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
		if (auto renderComp = GetOwner()->GetComponent<RenderComponent>())
		{
			renderComp->SetTexture(m_textTexture);
		}
		else
		{
			std::cerr << "RenderComponent could not be created." << std::endl;
		}
	}

}

void dae::TextComponent::Render() const
{
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}



void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_color = color;
	m_needsUpdate = true;
}


std::type_index dae::TextComponent::GetType() const
{
	return typeid(TextComponent);
}
