#pragma once
#include <string>
#include <functional>
#include <filesystem>
#include <SDL3/SDL.h>

#include "IGame.h"

namespace dae
{
	class Minigin final
	{
		bool m_quit{};
	public:
		explicit Minigin(const std::filesystem::path& dataPath);
		~Minigin();
		void Run();
		void RunOneFrame();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		// Student functions
		static float GetFrameTime();

		void SetGame(std::unique_ptr<DigDug::IGame> game) { m_Game = std::move(game); }
	private:
		std::unique_ptr<DigDug::IGame> m_Game;
	};
}
