#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include "InputManager.h"



bool dae::InputManager::ProcessInput(float)
{

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT)
		{
			return false;
		}



		if (e.type == SDL_EVENT_KEY_DOWN) {
			SDL_Scancode sc = e.key.scancode;
			for (auto& binding : m_Commands)
			{
				// Only trigger if this is a keyboard command
				if (std::holds_alternative<SDL_Scancode>(binding.keyOrButton) &&
					std::get<SDL_Scancode>(binding.keyOrButton) == sc)
				{
					binding.command->Execute();
				}
			}
		}
		if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			
		}
		ImGui_ImplSDL3_ProcessEvent(&e);
	}

	for (auto& device : m_Devices)
		device->Update();

	for (auto& binding : m_Commands)
	{
		for (auto& device : m_Devices)
		{
			if (device->IsPressed(binding.keyOrButton))
			{
				binding.command->Execute();
			}
		}
	}


	return true;
}

void dae::InputManager::AddDevice(std::unique_ptr<InputDevice> device)
{
	m_Devices.push_back(std::move(device));
}

void dae::InputManager::AddCommandBinding(std::variant<SDL_Scancode, int> keyOrButton, std::unique_ptr<Command> command)
{
	m_Commands.emplace_back(keyOrButton , std::move(command));
}
