cmake_minimum_required(VERSION 3.26)
project(Minigin)

if(EMSCRIPTEN)
  message("Using Emscripten!")
endif()

# =========================
# Names
# =========================
set(ENGINE_NAME Minigin)
set(GAME_NAME Game)

if(EMSCRIPTEN)
  set(GAME_NAME minigin_web)
endif()

# =========================
# engine :D!!
# =========================
add_library(${ENGINE_NAME} STATIC
        # Core engine
        Minigin/Font.cpp
        Minigin/GameObject.cpp
        Minigin/Minigin.cpp
        Minigin/Renderer.cpp
        Minigin/Scene.cpp
        Minigin/Texture2D.cpp
        Minigin/Transform.cpp

        # Managers
        Minigin/Managers/InputManager.cpp
        Minigin/Managers/ResourceManager.cpp
        Minigin/Managers/SceneManager.cpp

        # Components
        Minigin/Components/TextComponent.cpp
        Minigin/Components/FPSComponent.cpp
        Minigin/Components/Component.cpp
        Minigin/Components/RenderComponent.cpp
        Minigin/Components/RotationComponent.cpp
        Minigin/Components/MovementComponent.cpp
        Minigin/Components/SpriteAnimationComponent.cpp

        # Commands
        Minigin/Commands/Command.cpp
        Minigin/Commands/MoveCommand.cpp
        Minigin/Commands/GameActorCommand.cpp

        # Input
        Minigin/Gamepad.cpp
        Minigin/Keyboard.cpp

        # Observers
        Minigin/Observers/ObserverManager.cpp
        Minigin/Observers/IObserver.cpp
        Minigin/Observers/Achievement.cpp

        # Systems
        Minigin/Systems/ScoreSystem.cpp
        Minigin/Systems/DebugSystem.cpp

        # Events
        Minigin/EventQueue/EventBus.cpp

        # Utils
        Minigin/HelperFunctions/Utils.cpp

        # Sound
        Minigin/Sound/SoundSystem.cpp
        Minigin/Sound/sdl_sound_system.cpp
        Minigin/Sound/ServiceLocator.cpp
        Minigin/Sound/null_sound_system.cpp
        Minigin/Sound/Decorator.cpp
        Minigin/Sound/SoundEventListener.cpp

        # Game interface
        Minigin/IGame.cpp
)

target_include_directories(${ENGINE_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/Minigin
)

target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_20)

# =========================
# Game
# =========================
add_executable(${GAME_NAME}
        Game/Main.cpp
        Game/Game.cpp
)

target_compile_features(${GAME_NAME} PUBLIC cxx_std_20)
target_link_libraries(${GAME_NAME} PRIVATE ${ENGINE_NAME})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${GAME_NAME})

# =========================
# Dependencies
# =========================
include(FetchContent)

# ---- GLM ----
find_package(glm CONFIG QUIET)
if(NOT glm_FOUND)
  FetchContent_Declare(
          glm
          URL https://github.com/g-truc/glm/releases/download/1.0.3/glm-1.0.3.zip
  )
  FetchContent_MakeAvailable(glm)
endif()

# ---- SDL3 ----
find_package(SDL3 3.4 CONFIG QUIET)
if(NOT SDL3_FOUND)
  if (WIN32)
    FetchContent_Declare(
            SDL3
            URL https://www.libsdl.org/release/SDL3-devel-3.4.0-VC.zip
    )
    FetchContent_MakeAvailable(SDL3)
  else()
    FetchContent_Declare(
            SDL3
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-3.4.0
    )
    FetchContent_MakeAvailable(SDL3)
  endif()
endif()

# ---- IMGUI ----
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.92.5-docking
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)

target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
target_link_libraries(imgui PUBLIC SDL3::SDL3)
target_compile_features(imgui PUBLIC cxx_std_20)


target_link_libraries(${ENGINE_NAME} PUBLIC imgui)

# ---- SDL3_ttf ----
find_package(SDL3_ttf 3.2.2 CONFIG QUIET)
if(NOT SDL3_ttf_FOUND)
  FetchContent_Declare(
          SDL3_ttf
          GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
          GIT_TAG release-3.2.2
  )
  FetchContent_MakeAvailable(SDL3_ttf)
endif()

# ---- SDL3_mixer ----
find_package(SDL3_mixer CONFIG QUIET)
if(NOT SDL3_mixer_FOUND)
  FetchContent_Declare(
          SDL3_mixer
          GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
          GIT_TAG main
  )
  FetchContent_MakeAvailable(SDL3_mixer)
endif()

# ---- VLD ----
find_package(VLD CONFIG)


target_include_directories(${ENGINE_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/Minigin/
        ${VLD_INCLUDE_DIRS}
)

target_link_libraries(${ENGINE_NAME} PUBLIC
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
        glm::glm
        ${VLD_LIBRARIES}
)

# =========================
# Steam?
# =========================
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/steam")
find_package(Steamworks QUIET)

if(Steamworks_FOUND)
  target_link_libraries(${GAME_NAME} PRIVATE Steamworks::Steamworks)
  target_compile_definitions(${GAME_NAME} PRIVATE USE_STEAMWORKS)
endif()

# =========================
# Emscripten
# =========================
if(EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")

  set_target_properties(${GAME_NAME} PROPERTIES
          COMPILE_FLAGS "-g"
          LINK_FLAGS "-sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1 -sALLOW_MEMORY_GROWTH --preload-file ${CMAKE_SOURCE_DIR}/Data@/"
  )

  add_custom_command(TARGET ${GAME_NAME} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_CURRENT_SOURCE_DIR}/web
          $<TARGET_FILE_DIR:${GAME_NAME}>
  )

  add_custom_command(TARGET ${GAME_NAME} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/Data
          $<TARGET_FILE_DIR:${GAME_NAME}>/Data
  )

elseif(WIN32)

  target_link_libraries(${GAME_NAME} PRIVATE xinput.lib)

  set_target_properties(${GAME_NAME} PROPERTIES
          VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${GAME_NAME}>"
  )

  add_custom_command(TARGET ${GAME_NAME} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/Data
          $<TARGET_FILE_DIR:${GAME_NAME}>/Data
  )
  # DLL COPY
  set(SDL_RUNTIME_DLLS
          SDL3::SDL3
          SDL3_mixer::SDL3_mixer
          SDL3_ttf::SDL3_ttf
  )

  foreach(dllTarget IN LISTS SDL_RUNTIME_DLLS)
    add_custom_command(
            TARGET ${GAME_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:${dllTarget}>"
            "$<TARGET_FILE_DIR:${GAME_NAME}>"
    )
  endforeach()

elseif(APPLE)

  set_target_properties(${GAME_NAME} PROPERTIES
          MACOSX_BUNDLE TRUE
  )

endif()

# =========================
# Warnings
# =========================
if(MSVC)
  target_compile_options(${ENGINE_NAME} PRIVATE /W4 /WX)
  target_compile_options(${GAME_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${ENGINE_NAME} PRIVATE -Wall -Wextra -Werror)
  target_compile_options(${GAME_NAME} PRIVATE -Wall -Wextra -Werror)
endif()