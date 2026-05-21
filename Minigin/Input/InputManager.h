#pragma once
#include <memory>
#include <variant>
#include <vector>

#include "Singleton.h"
#include "Command.h"

#include "InputDevice.h"
#include "GamepadDataStructs.h"
namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class KeyState
		{
			Down,
			Held,
			Up
		};

		void ProcessKeyBoard();
		void ProcessGamepad();
		bool ProcessInput(float DeltaTime);

		void AddDevice(std::unique_ptr<InputDevice> device);

		void AddCommandBinding(
			std::variant<GamepadButton, SDL_Scancode> keyOrButton,
			std::unique_ptr<Command> command,
			KeyState state);

		void RemoveCommandBinding(std::variant<GamepadButton, SDL_Scancode> keyOrButton);

	private:


		struct CommandBinding
		{
			std::variant<GamepadButton, SDL_Scancode> keyOrButton; //lets it switch depending on which value you give it!
			std::unique_ptr<Command> command;
			KeyState state;
		};

		std::vector<CommandBinding> m_Commands;
		std::vector<std::unique_ptr<InputDevice>> m_Devices;


		void DetectGamePads();
	};

}