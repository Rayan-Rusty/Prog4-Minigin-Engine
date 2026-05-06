#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "Singleton.h"
#include <memory>
class TextObject;
namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
	public:


		struct DrawCommand
		{
			std::shared_ptr<Texture2D> texture;
			SDL_FRect dst;
			SDL_FRect src;
			bool isUI{false};
		};

		void Init(SDL_Window* window);
		void Render();
		void Destroy();
		void Shutdown();
		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const SDL_FRect& dst) const;
		void RenderTexture(const Texture2D& texture , const SDL_FRect& dst,const SDL_FRect& src) const;
		void Submit(bool isUI, const std::shared_ptr<Texture2D>& texture,const SDL_FRect& dst , const SDL_FRect& src);


		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

		std::vector<DrawCommand> m_drawCommands;

		//student functions
		void Clear() const;
	};
}

