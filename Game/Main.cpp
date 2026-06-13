#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "../Minigin/Components/Text/TextComponent.h"

#include "IGame.h"
#include "DigDug.h"
#include <filesystem>
#include "Decorator.h"
#include "sdl_sound_system.h"
#include "ServiceLocator.h"
namespace fs = std::filesystem;


int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
	std::cout << "DATA ROOT = " << data_location << std::endl;
	std::cout << "CWD = " << std::filesystem::current_path() << std::endl;
#endif
	dae::Minigin engine(data_location);

#if _DEBUG
	dae::ServiceLocator::register_sound_system(
	std::make_unique<dae::logging_sound_system>(std::make_unique<dae::sdl_sound_system>()));
#else
	dae::ServiceLocator::register_sound_system(std::make_unique<dae::sdl_sound_system>());
#endif




	auto& ss = dae::ServiceLocator::get_sound_system();




	std::unique_ptr<DigDug::IGame> game = std::make_unique<DigDug::Game>();
	game->Init();

	engine.SetGame(std::move(game));
	engine.Run();
	ss.play(10, 1.f);
    return 0;
}
