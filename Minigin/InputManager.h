#pragma once
#include <variant>

#include "Singleton.h"
#include "Commands/Command.h"
#include "InputDevice.h"
namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput(float DeltaTime) ;

		void AddDevice(std::unique_ptr<InputDevice> device);

		void AddCommandBinding(std::variant<SDL_Scancode,int> keyOrButton,
							   std::unique_ptr<Command> command);


	private:


		struct CommandBinding
		{
			//https://en.cppreference.com/w/cpp/utility/variant.html
			std::variant<SDL_Scancode, int> keyOrButton; //lets it switch depending on which value you give it!
			std::unique_ptr<Command> command;
		};

		std::vector<CommandBinding> m_Commands;
		std::vector<std::unique_ptr<InputDevice>> m_Devices;
	};

}
