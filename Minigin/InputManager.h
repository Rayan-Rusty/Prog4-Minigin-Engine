#pragma once
#include "Singleton.h"
#include "Commands/Command.h"
namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput(float DeltaTime) ;
		void AddCommandBinding(SDL_Scancode key , std::unique_ptr<Command> command);

	private:

		enum InputState
		{
			Pressed,
			Released,
			Held
		};

		struct CommandBinding
		{
			SDL_Scancode key;

			std::unique_ptr<Command> command;
		};

		std::vector<CommandBinding> m_Commands;
	};

}
