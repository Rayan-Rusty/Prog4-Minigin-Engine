#pragma once
#include <string>
#include <functional>
#include <filesystem>
#include <SDL3/SDL.h>

namespace dae
{
	class Game;
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

		void SetGame(std::shared_ptr<Game> game) { m_Game = game; }
	private:
		std::shared_ptr<Game> m_Game;
	};
}