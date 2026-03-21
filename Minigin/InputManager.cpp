#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include "InputManager.h"
#include "Gamepad.h"


bool dae::InputManager::ProcessInput(float)
{

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT)
		{
			return false;
		}


		//TODO Automatic detection Gamepads
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
		// etc...
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
void dae::InputManager::RemoveCommandBinding(std::variant<SDL_Scancode, int> keyOrButton)
{
	auto it = std::remove_if(m_Commands.begin(), m_Commands.end(),
		[&](const CommandBinding& binding)
		{
			return binding.keyOrButton == keyOrButton;
		});

	m_Commands.erase(it, m_Commands.end());
}

void dae::InputManager::DetectGamePads()
{
	auto indices = Gamepad::GetConnectedDevices();
	for (int index : indices)
	{
		bool exists = false;

		for (const auto& device : m_Devices)
		{
			if (device->GetDeviceID() == index)
			{
				exists = true;
				break;
			}
		}

		if (!exists)
		{
			AddDevice(std::make_unique<Gamepad>(index));
		}
	}

	m_Devices.erase(
		std::remove_if(m_Devices.begin(), m_Devices.end(),
			[&](const std::unique_ptr<InputDevice>& device)
			{
				return std::find(indices.begin(), indices.end(),
								 device->GetDeviceID()) == indices.end();
			}),
		m_Devices.end()
	);

}
