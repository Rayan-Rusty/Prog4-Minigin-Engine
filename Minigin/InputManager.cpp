#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include "InputManager.h"



bool dae::InputManager::ProcessInput(float)
{

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}
		if (e.type == SDL_EVENT_KEY_DOWN) {
			for (auto& binding : m_Commands)
			{
				if (binding.key == e.key.scancode)
				{
					binding.command->Execute();
				}
			}
		}
		if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			
		}
		// etc...
		ImGui_ImplSDL3_ProcessEvent(&e);
	}

	return true;
}


void dae::InputManager::AddCommandBinding(SDL_Scancode key, std::unique_ptr<Command> command)
{
	m_Commands.push_back({key , std::move(command)});
}
