cmake_minimum_required(VERSION 3.26)
project(Minigin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)


if(EMSCRIPTEN)
  message("Using Emscripten!")
  set(GAME_NAME Dig_Dug)
  set(TARGET_PARAM)
else ()
  set(GAME_NAME Dig_Dug)
  set(TARGET_PARAM WIN32)
endif()

# =========================
# TARGET NAMES
# =========================
set(ENGINE_NAME Minigin)
set(GAME_NAME Game)

if(EMSCRIPTEN)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/emscripten")

  set(SDL3TTF_USE_SYSTEM_FREETYPE ON CACHE BOOL "" FORCE)
  set(SDL3TTF_VENDORED OFF CACHE BOOL "" FORCE)
  set(SDLTTF_PLUTOSVG OFF CACHE BOOL "" FORCE)

  add_compile_options(-sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1)
  add_link_options(-sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1)
  set(GAME_NAME minigin_web)
endif()

# =========================
# ENGINE (STATIC LIB)
# =========================
add_library(${ENGINE_NAME} STATIC
        # Core engine
        Minigin/Textures/Font.cpp
        Minigin/GameObject/GameObject.cpp
        Minigin/Minigin.cpp
        Minigin/Rendering/Renderer.cpp
        Minigin/Scene/Scene.cpp
        Minigin/Textures/Texture2D.cpp
        Minigin/Transform/Transform.cpp

        # Managers
        Minigin/Input/InputManager.cpp
        Minigin/Textures/ResourceManager.cpp
        Minigin/Scene/SceneManager.cpp

        # Components
        Minigin/Components/Text/TextComponent.cpp
        Minigin/Components/Fps/FPSComponent.cpp
        Minigin/Components/BaseComp/Component.cpp
        Minigin/Components/Rendering/RenderComponent.cpp
        Minigin/Components/Rotation/RotationComponent.cpp
        Minigin/Components/Movement/MovementComponent.cpp
        Minigin/Components/Sprites/SpriteAnimationComponent.cpp

        # Commands
        Minigin/Commands/Command.cpp
        Minigin/Commands/MoveCommand.cpp
        Minigin/Commands/GameActorCommand.cpp

        # Input
        Minigin/Devices/Gamepad.cpp
        Minigin/Devices/Keyboard.cpp

        # Observers
        Minigin/Observers/ObserverManager.cpp
        Minigin/Observers/IObserver.cpp
        Minigin/Observers/Achievement.cpp
        Minigin/Observers/GameActor.cpp
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


        # Game interface
        Minigin/IGame.cpp
        Minigin/Components/Collision/CollisionComponent.cpp
        Minigin/Components/Collision/CollisionComponent.h
        Minigin/Collisions/CollisionManager.cpp
        Minigin/Collisions/CollisionManager.h
        Minigin/Components/Health/HealthComponent.cpp
        Minigin/Components/Health/HealthComponent.h

)


target_include_directories(${ENGINE_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/Minigin
        ${CMAKE_SOURCE_DIR}/Minigin/DataStructs
        ${CMAKE_SOURCE_DIR}/Minigin/Devices
        ${CMAKE_SOURCE_DIR}/Minigin/GameObject
        ${CMAKE_SOURCE_DIR}/Minigin/Imgui
        ${CMAKE_SOURCE_DIR}/Minigin/Input
        ${CMAKE_SOURCE_DIR}/Minigin/Rendering
        ${CMAKE_SOURCE_DIR}/Minigin/Scene
        ${CMAKE_SOURCE_DIR}/Minigin/Singletons
        ${CMAKE_SOURCE_DIR}/Minigin/Textures
        ${CMAKE_SOURCE_DIR}/Minigin/Transform
        ${CMAKE_SOURCE_DIR}/Minigin/Components
        ${CMAKE_SOURCE_DIR}/Minigin/Components/Collision
        ${CMAKE_SOURCE_DIR}/Minigin/Components/BaseComp
        ${CMAKE_SOURCE_DIR}/Minigin/Components/Debug
        ${CMAKE_SOURCE_DIR}/Minigin/Components/Fps
        ${CMAKE_SOURCE_DIR}/Minigin/Components/Health
        ${CMAKE_SOURCE_DIR}/Minigin/Components/Movement
        ${CMAKE_SOURCE_DIR}/Minigin/Components/Rendering
        ${CMAKE_SOURCE_DIR}/Minigin/Components/Rotation
        ${CMAKE_SOURCE_DIR}/Minigin/Components/Sprites
        ${CMAKE_SOURCE_DIR}/Minigin/Components/Text
        ${CMAKE_SOURCE_DIR}/Minigin/Commands
        ${CMAKE_SOURCE_DIR}/Minigin/Systems
        ${CMAKE_SOURCE_DIR}/Minigin/EventQueue
        ${CMAKE_SOURCE_DIR}/Minigin/Sound
        ${CMAKE_SOURCE_DIR}/Minigin/Observers
        ${CMAKE_SOURCE_DIR}/Minigin/HelperFunctions
        ${CMAKE_SOURCE_DIR}/Minigin/States
        ${CMAKE_SOURCE_DIR}/Minigin/Collisions
)

set(ENGINE_DIRS Minigin/ Minigin/Components Minigin/Commands Minigin/Systems Minigin/Devices Minigin/EventQueue
        Minigin/HelperFunctions Minigin/Managers Minigin/Observers Minigin/Singletons)


target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_20)

# =========================
# GAME (EXECUTABLE)
# =========================



add_executable(${GAME_NAME}
        Game/Main.cpp
        Game/DigDug.cpp
        Game/Utils.cpp
        Game/Utils.h

        # Player
        Game/Player/PlayerBehaviour.cpp
        Game/Player/PlayerBehaviour.h
        Game/Player/Movement/PlayerMovement.cpp
        Game/Player/Movement/PlayerMovement.h
        Game/Player/CollisionObserver/PlayerCollisionHandler.cpp
        Game/Player/CollisionObserver/PlayerCollisionHandler.h

        # Player States
        Game/Player/States/PlayerIdleState.cpp
        Game/Player/States/PlayerIdleState.h
        Game/Player/States/PlayerWalkingState.cpp
        Game/Player/States/PlayerWalkingState.h
        Game/Player/States/PlayerAttackState.cpp
        Game/Player/States/PlayerAttackState.h
        Game/Player/States/PlayerInflatingState.cpp
        Game/Player/States/PlayerInflatingState.h

        # Player Commands
        Game/Player/Command/PlayerMoveCommand.cpp
        Game/Player/Command/PlayerMoveCommand.h
        Game/Player/Command/AttackCommand.cpp
        Game/Player/Command/AttackCommand.h

        # Pump
        Game/Player/Pump/PumpBehaviour.cpp
        Game/Player/Pump/PumpBehaviour.h
        Game/Player/Pump/State/PumpIdleState.cpp
        Game/Player/Pump/State/PumpIdleState.h
        Game/Player/Pump/State/PumpAttackState.cpp
        Game/Player/Pump/State/PumpAttackState.h

        # Pooka
        Game/Enemies/Pooka/PookaBehaviour.cpp
        Game/Enemies/Pooka/PookaBehaviour.h
        Game/Enemies/Pooka/Movement/PookaMovement.cpp
        Game/Enemies/Pooka/Movement/PookaMovement.h
        Game/Enemies/Pooka/States/PookaNormalState.cpp
        Game/Enemies/Pooka/States/PookaNormalState.h
        Game/Enemies/Pooka/States/PookaGhostState.cpp
        Game/Enemies/Pooka/States/PookaGhostState.h
        Game/Enemies/Pooka/States/PookaInflatedState.cpp
        Game/Enemies/Pooka/States/PookaInflatedState.h
        Game/Enemies/Pooka/States/PookaDeadState.cpp
        Game/Enemies/Pooka/States/PookaDeadState.h

        # Fygar
        Game/Enemies/Fygar/FygarBehaviour.cpp
        Game/Enemies/Fygar/FygarBehaviour.h
        Game/Enemies/Fygar/Movement/FygarMovement.cpp
        Game/Enemies/Fygar/Movement/FygarMovement.h
        Game/Enemies/Fygar/States/FygarNormalState.cpp
        Game/Enemies/Fygar/States/FygarNormalState.h
        Game/Enemies/Fygar/States/FygarGhostState.cpp
        Game/Enemies/Fygar/States/FygarGhostState.h
        Game/Enemies/Fygar/States/FygarAttackState.cpp
        Game/Enemies/Fygar/States/FygarAttackState.h
        Game/Enemies/Fygar/States/FygarInflatedState.cpp
        Game/Enemies/Fygar/States/FygarInflatedState.h
        Game/Enemies/Fygar/States/FygarDeadState.cpp
        Game/Enemies/Fygar/States/FygarDeadState.h

        # Tilemap
        Game/TileMap/TilemapComponent.cpp
        Game/TileMap/TilemapComponent.h
        Game/TileMap/BaseTilemapLoader.cpp
        Game/TileMap/BaseTilemapLoader.h
        Game/TileMap/EnemySpawnerComponent.cpp
        Game/TileMap/EnemySpawnerComponent.h
        Game/TileMap/EnemyTraits.h
        Game/TileMap/Layers/GameLayers.h

        # Blocks
        Game/Blocks/BlockBehaviour.cpp
        Game/Blocks/BlockBehaviour.h
        Game/Blocks/States/BlockDestroyedState.cpp
        Game/Blocks/States/BlockDestroyedState.h
        Game/Blocks/States/BlockSolidState.cpp
        Game/Blocks/States/BlockSolidState.h

        # Level
        Game/Level/LevelComponent.cpp
        Game/Level/LevelComponent.h
        Game/Level/LevelStruct.h
        Game/Level/HighScore/HighScoreNavigatecommand.cpp
        Game/Level/HighScore/HighScoreNavigatecommand.h
        Game/Level/HighScore/HighScoreConfirmCommand.cpp
        Game/Level/HighScore/HighScoreConfirmCommand.h

        # Menu
        Game/Menu/MenuMarker.cpp
        Game/Menu/MenuMarker.h
        Game/Menu/BackGround/Movement/MenuMovement.cpp
        Game/Menu/BackGround/Movement/MenuMovement.h
        Game/Menu/Events/System/MenuNavigateCommand.cpp
        Game/Menu/Events/System/MenuNavigateCommand.h
        Game/Menu/Events/System/MenuNavigateSystem.cpp
        Game/Menu/Events/System/MenuNavigateSystem.h

        # Commands
        Game/Commands/ConfirmedCommand.cpp
        Game/Commands/ConfirmedCommand.h

        # Components
        Game/Components/ScoreComponent.cpp
        Game/Components/ScoreComponent.h
        Game/Components/HighScoreComponent.cpp
        Game/Components/HighScoreComponent.h
        # sound
        Game/Sound/SoundEventListener.cpp
)

target_include_directories(${GAME_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/Game
        ${CMAKE_SOURCE_DIR}/Game/Sound
        ${CMAKE_SOURCE_DIR}/Game/Enemies
        ${CMAKE_SOURCE_DIR}/Game/Enemies/Pooka
        ${CMAKE_SOURCE_DIR}/Game/Enemies/Pooka/States
        ${CMAKE_SOURCE_DIR}/Game/Enemies/Pooka/Movement
        ${CMAKE_SOURCE_DIR}/Game/Enemies/Fygar
        ${CMAKE_SOURCE_DIR}/Game/Enemies/Fygar/States
        ${CMAKE_SOURCE_DIR}/Game/Enemies/Fygar/Movement
        ${CMAKE_SOURCE_DIR}/Game/Player/States
        ${CMAKE_SOURCE_DIR}/Game/Player/CollisionObserver
        ${CMAKE_SOURCE_DIR}/Game/Player
        ${CMAKE_SOURCE_DIR}/Game/Player/Command
        ${CMAKE_SOURCE_DIR}/Game/Player/Movement
        ${CMAKE_SOURCE_DIR}/Game/Player/Pump/
        ${CMAKE_SOURCE_DIR}/Game/Player/Pump/State
        ${CMAKE_SOURCE_DIR}/Game/Player/Pump/States
        ${CMAKE_SOURCE_DIR}/Game/Level/
        ${CMAKE_SOURCE_DIR}/Game/Level/HighScore
        ${CMAKE_SOURCE_DIR}/Game/Menu/BackGround/
        ${CMAKE_SOURCE_DIR}/Game/Menu/BackGround/Movement
        ${CMAKE_SOURCE_DIR}/Game/Menu/Events/System
        ${CMAKE_SOURCE_DIR}/Game/TileMap
        ${CMAKE_SOURCE_DIR}/Game/TileMap/Layers
        ${CMAKE_SOURCE_DIR}/Game/Menu/
        ${CMAKE_SOURCE_DIR}/Game/Menu/Events/
        ${CMAKE_SOURCE_DIR}/Game/Menu/Events/System
        ${CMAKE_SOURCE_DIR}/Game/Blocks/
        ${CMAKE_SOURCE_DIR}/Game/Blocks/States
        ${CMAKE_SOURCE_DIR}/Game/Commands
        ${CMAKE_SOURCE_DIR}/Game/Components
        ${CMAKE_SOURCE_DIR}/Game/Highscore/


)

target_compile_features(${GAME_NAME} PUBLIC cxx_std_20)
target_link_libraries(${GAME_NAME} PRIVATE ${ENGINE_NAME})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${GAME_NAME})

# =========================
# DEPENDENCIES
# =========================
include(FetchContent)

# ---- GLM ----

find_package(glm CONFIG QUIET)
if(NOT glm_FOUND)
  FetchContent_Declare(
          glm
          URL https://github.com/g-truc/glm/releases/download/1.0.3/glm-1.0.3.zip
          DOWNLOAD_NO_PROGRESS ON
          DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
  )
  FetchContent_MakeAvailable(glm)
endif()


FetchContent_MakeAvailable(glm)

# ---- SDL3 ----
find_package(SDL3 3.4 CONFIG QUIET)
if(NOT SDL3_FOUND)
  if (WIN32)
    FetchContent_Declare(
            SDL3
            URL https://www.libsdl.org/release/SDL3-devel-3.4.0-VC.zip
            DOWNLOAD_NO_PROGRESS ON
            DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
    )
    FetchContent_MakeAvailable(SDL3)
    list(PREPEND CMAKE_PREFIX_PATH "${sdl3_SOURCE_DIR}")
    find_package(SDL3 CONFIG REQUIRED)
  else()
    FetchContent_Declare(
            SDL3
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-3.4.0
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(SDL3)
  endif()
endif()



# ---- SDL3_ttf ----
find_package(SDL3_ttf 3.2.2 CONFIG QUIET)
if(NOT SDL3_ttf_FOUND)
  if (WIN32)
    FetchContent_Declare(
            SDL3_ttf
            URL https://www.libsdl.org/projects/SDL_ttf/release/SDL3_ttf-devel-3.2.2-VC.zip
            DOWNLOAD_NO_PROGRESS ON
            DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
    )
    FetchContent_MakeAvailable(SDL3_ttf)
    list(PREPEND CMAKE_PREFIX_PATH "${sdl3_ttf_SOURCE_DIR}")
    find_package(SDL3_ttf CONFIG REQUIRED)
  else()
    FetchContent_Declare(
            SDL3_ttf
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
            GIT_TAG release-3.2.2
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    set(SDL3TTF_INSTALL OFF)
    if(EMSCRIPTEN)
      list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/emscripten")
      set(SDL3TTF_USE_SYSTEM_FREETYPE ON)
      set(SDL3TTF_VENDORED OFF)
      set(SDLTTF_PLUTOSVG OFF)
      add_compile_options(-sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1)
      add_link_options(-sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1)
    endif()
    FetchContent_MakeAvailable(SDL3_ttf)
  endif()
endif()

# ---- SDL3_mixer ----
find_package(SDL3_mixer 3.2.0 CONFIG QUIET)
if(NOT SDL3_mixer_FOUND)
  if (WIN32)
    FetchContent_Declare(
            SDL3_mixer
            URL https://github.com/libsdl-org/SDL_mixer/releases/download/release-3.2.0/SDL3_mixer-devel-3.2.0-VC.zip
            DOWNLOAD_NO_PROGRESS ON
            DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/downloads
    )
    FetchContent_MakeAvailable(SDL3_mixer)
    list(PREPEND CMAKE_PREFIX_PATH "${sdl3_mixer_SOURCE_DIR}")
    find_package(SDL3_mixer CONFIG REQUIRED)
  else()
    FetchContent_Declare(
            SDL3_mixer
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
            GIT_TAG release-3.2.0
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    set(SDL3MIXER_INSTALL OFF)
    if(EMSCRIPTEN)
      list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/emscripten")
      set(SDL3MIXER_USE_SYSTEM_FREETYPE ON)
      set(SDL3MIXER_VENDORED OFF)
      set(SDL3MIXER_PLUTOSVG OFF)
      add_compile_options(-sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1)
      add_link_options(-sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1)
    endif()
    FetchContent_MakeAvailable(SDL3_mixer)
  endif()
endif()

# ---- IMGUI ----
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.92.5-docking
        GIT_SHALLOW TRUE
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

target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${sdl3_SOURCE_DIR}/include)
target_link_libraries(imgui PUBLIC SDL3::SDL3)
target_compile_features(imgui PUBLIC cxx_std_20)

target_link_libraries(${ENGINE_NAME} PUBLIC imgui)
# ---- VLD ----
if(WIN32)
  find_package(VLD CONFIG)
endif()

target_include_directories(${ENGINE_NAME} PUBLIC
        ${CMAKE_SOURCE_DIR}/Minigin/
        ${glm_SOURCE_DIR}
        ${sdl3_SOURCE_DIR}/include
        ${sdl3_image_SOURCE_DIR}/include
        ${sdl3_ttf_SOURCE_DIR}/include
        ${sdl3_mixer_SOURCE_DIR}/include
        ${imgui_SOURCE_DIR}
        ${VLD_INCLUDE_DIRS}
)
target_link_libraries(${ENGINE_NAME} PUBLIC
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
        SDL3_mixer::SDL3_mixer
        glm::glm
        imgui
        ${VLD_LIBRARIES}
)


# =========================
# STEAM (GAME ONLY)
# =========================
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/steam")
find_package(Steamworks QUIET)

if(Steamworks_FOUND)
  target_link_libraries(${GAME_NAME} PRIVATE Steamworks::Steamworks)
  target_compile_definitions(${GAME_NAME} PRIVATE USE_STEAMWORKS)
endif()

# =========================
# PLATFORM: EMSCRIPTEN
# =========================
if(EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".html")

  set_target_properties(${GAME_NAME} PROPERTIES
          COMPILE_FLtaAGS "-g"
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
# WARNINGS
# =========================
if(MSVC)
  target_compile_options(${ENGINE_NAME} PRIVATE /W4 /WX)
  target_compile_options(${GAME_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${ENGINE_NAME} PRIVATE -Wall -Wextra -Werror)
  target_compile_options(${GAME_NAME} PRIVATE -Wall -Wextra -Werror)
endif()