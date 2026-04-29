#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "Managers/SceneManager.h"
#include "Managers/ResourceManager.h"
#include "Components/TextComponent.h"
#include "Scene.h"
#include "Game.h"

#include <filesystem>

#include "Sound/Decorator.h"
#include "Sound/sdl_sound_system.h"
#include "Sound/ServiceLocator.h"
namespace fs = std::filesystem;


int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);

#if _DEBUG
	dae::ServiceLocator::register_sound_system(
	std::make_unique<dae::logging_sound_system>(std::make_unique<dae::sdl_sound_system>()));
#else
	servicelocator::register_sound_system(std::make_unique<sdl_sound_system>());
#endif



	dae::ServiceLocator::register_sound_system(std::make_unique<dae::sdl_sound_system>());

	auto& ss = dae::ServiceLocator::get_sound_system();
	ss.play(10, 1.f);



	std::unique_ptr<dae::Game> game = std::make_unique<dae::Game>();
	game->init();

	engine.SetGame(std::move(game));
	engine.Run();

    return 0;
}
