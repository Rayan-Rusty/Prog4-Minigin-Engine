//
// Created by omen on 14/02/2026.
//

#include "Game.h"

#include "SceneManager.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Scene.h"
#include "Components/TextComponent.h"
#include "Components/FPSComponent.h"
#include "Components/RenderComponent.h"
#include "Components/RotationComponent.h"
#include <imgui.h>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_plot.h>
dae::Game::Game(dae::Scene* scene)
    : m_CurrentScene(scene) {
}

void dae::Game::init()
{
    InitializeIMGUIScene();
}

void dae::Game::Update(float deltaTime) {

    m_CurrentScene->Update(deltaTime);
}

void dae::Game::Draw() {
    m_CurrentScene->Render();
    WindowIntBenchmark();
    WindowGameObjectWindow();
}

void dae::Game::WindowIntBenchmark()
{

    constexpr int maxSamples = 1000;
    constexpr int minSamples = 10;
    ImGui::Begin("Exercise 1");


    ImGui::PushItemWidth(100);
    ImGui::InputInt("##SampleInput", &m_sampleCountInt);
    m_sampleCountInt = std::clamp(m_sampleCountInt, minSamples, maxSamples);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::Text("# Samples");


    if (ImGui::Button("Run Int Benchmark"))
        RunIntBenchmark();



    if (!m_IntTimings.empty())
    {
        ImGui::PushStyleColor(ImGuiCol_PlotLines, IM_COL32(255, 0, 0, 255)); // red
        ImGui::Text("Trash the cache");
        ImGui::PlotLines(
            "Int benchmark",           // label
            m_IntTimings.data(),      // data pointer
            static_cast<int>(m_IntTimings.size()), // count
            0,                        // offsets
            nullptr,                  // overlaying text
            FLT_MAX,                  // min amount
            FLT_MAX,                  // max amount
            ImVec2(0, 150)            // size
        );
        ImGui::PopStyleColor();
    }

    ImGui::End();
}

void dae::Game::WindowGameObjectWindow()
{
    constexpr int maxSamples = 1000;
    constexpr int minSamples = 10;

    ImGui::Begin("Exercise 2");

    ImGui::PushItemWidth(100);
    ImGui::InputInt("##SampleInput", &m_sampleCountGameObject);
    m_sampleCountGameObject = std::clamp(m_sampleCountGameObject, minSamples, maxSamples);
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::Text("# Samples");

    if (ImGui::Button("Trash the cache with GameObject3D"))
        RunGameObject3DBenchmark();
    if (ImGui::Button("Trash the cache with GameObject3DAlt"))
        RunGameObject3DAltBenchmark();

    if (!m_GameObject3D.empty())
    {
        ImGui::PushStyleColor(ImGuiCol_PlotLines, IM_COL32(0, 255, 0, 255));
        ImGui::Text("GameObject:");
        ImGui::PlotLines(
            "object benchmark",
            m_GameObject3D.data(),
            static_cast<int>(m_GameObject3D.size()),
            0,
            nullptr,
            FLT_MIN,
            FLT_MAX,
            ImVec2(0,150)
            );
        ImGui::PopStyleColor();
    }

    if (!m_GameObject3DAlt.empty())
    {
        ImGui::PushStyleColor(ImGuiCol_PlotLines, IM_COL32(0, 0, 255, 255));
        ImGui::Text("GameObjectAlt:");
        ImGui::PlotLines(
            "object benchmark",
            m_GameObject3DAlt.data(),
            static_cast<int>(m_GameObject3DAlt.size()),
            0,
            nullptr,
            FLT_MIN,
            FLT_MAX,
            ImVec2(0,150)
            );
        ImGui::PopStyleColor();
    }

    ImGui::End();
}

void dae::Game::RunIntBenchmark()
{
    m_IntTimings.clear();

    const size_t size = 1 << 26;
    std::vector<int> arr(size, 1);


    for (int step = 1; step <= 1024; step *= 2 )
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < arr.size(); i += step)
        {
            arr[i] *= 2;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        float durationMs = static_cast<float>(duration) / 1000.0f;

        m_IntTimings.push_back(durationMs);
    }
}

void dae::Game::RunGameObject3DBenchmark()
{
    m_GameObject3D.clear();
    const size_t size = 1 << 20;
    std::vector<GameObject3D> arr(size);
    for (int step = 1; step <= 1024; step *= 2)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < arr.size(); i += step)
        {
            arr[i].ID *= 2;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        float durationMs = static_cast<float>(duration) / 1000.0f;

        m_GameObject3D.push_back(durationMs);
    }
}


void dae::Game::RunGameObject3DAltBenchmark()
{
    m_GameObject3DAlt.clear();

    const size_t size = 1 << 20;


    std::vector<GameObject3DAlt> arr(size);
    std::vector<TransformObj> transforms(size);

    for (size_t i = 0; i < size; ++i)
    {
        arr[i].transform = &transforms[i];
    }


    for (int step = 1; step <= 1024; step *= 2)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < arr.size(); i += step)
        {
            arr[i].ID *= 2;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        float durationMs = static_cast<float>(duration) / 1000.0f;

        m_GameObject3DAlt.push_back(durationMs);
    }
}

void dae::Game::InitializeGame() {

    //init variables
    auto go{std::make_unique<dae::GameObject>()};
    auto RenderComp{std::make_unique<RenderComponent>(go.get())};


    //---------Background-------------
    RenderComp->SetTextureFilePath("background.png");
    go->AddComponent(std::move(RenderComp));
    m_CurrentScene->Add(std::move(go));

    //---------Logo-------------
    go = std::make_unique<dae::GameObject>();
    go->GetTransform().SetLocalPosition(glm::vec3{358, 180,0});
    RenderComp = std::make_unique<RenderComponent>(go.get());

    RenderComp->SetTextureFilePath("logo.png");
    go->AddComponent(std::move(RenderComp));
    m_CurrentScene->Add(std::move(go));


    //---------Texts-------------
    auto font{dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36)};
    auto textGO{std::make_unique<dae::GameObject>()};
    textGO->GetTransform().SetLocalPosition(glm::vec3{292, 20 ,0});

    auto textComp{std::make_unique<dae::TextComponent>(textGO.get(), "Programming 4 Assignment", font)};
    RenderComp = std::make_unique<RenderComponent>(textGO.get());
    textComp->SetColor({255, 255, 255, 255});
    textGO->AddComponent(std::move(RenderComp));
    textGO->AddComponent(std::move(textComp));
    m_CurrentScene->Add(std::move(textGO));

    //fps Counter

    auto FpsGameObject{std::make_unique<dae::GameObject>()};
    FpsGameObject->GetTransform().SetLocalPosition(glm::vec3{10,10,0});

    auto TextComp{std::make_unique<dae::TextComponent>(FpsGameObject.get(), "FPS : 0", font)};
    TextComp->SetColor({255, 255, 255, 255});
    RenderComp = std::make_unique<RenderComponent>(FpsGameObject.get());

    FpsGameObject->AddComponent(std::move(RenderComp));
    FpsGameObject->AddComponent(std::move(TextComp));
    FpsGameObject->AddComponent(std::make_unique<dae::FPSComponent>(FpsGameObject.get()));
    m_CurrentScene->Add(std::move(FpsGameObject));


    //##########################################################
    //                  objects with children
    //##########################################################
    auto parentObject{std::make_unique<dae::GameObject>()};


    parentObject->GetTransform().SetLocalPosition(glm::vec3{250,250,0});

    RenderComp = std::make_unique<RenderComponent>(parentObject.get());
    RenderComp->SetTextureFilePath("Dragon.png");

    auto rotationComponent {std::make_unique<dae::RotationComponent>(parentObject.get(),glm::vec3{270,270,0}, 1.f)};


    parentObject->AddComponent(std::move(rotationComponent));
    parentObject->AddComponent(std::move(RenderComp));

    auto child {std::make_unique<dae::GameObject>()};
    child->GetTransform().SetLocalPosition(glm::vec3{20,20,0});

    child->SetParent(parentObject.get() , false);
    RenderComp= std::make_unique<RenderComponent>(child.get());
    RenderComp->SetTextureFilePath("Player.png");


    rotationComponent = std::make_unique<dae::RotationComponent>(child.get(),glm::vec3{0,0,0}, -1.f);
    child->AddComponent(std::move(rotationComponent));
    child->AddComponent(std::move(RenderComp));

    m_CurrentScene->Add(std::move(parentObject));
    m_CurrentScene->Add(std::move(child));
}

void dae::Game::InitializeIMGUIScene()
{
    auto go{std::make_unique<dae::GameObject>()};
    auto RenderComp{std::make_unique<RenderComponent>(go.get())};


    //---------Background-------------
    RenderComp->SetTextureFilePath("background.png");
    go->AddComponent(std::move(RenderComp));
    m_CurrentScene->Add(std::move(go));

    //---------Logo-------------
    go = std::make_unique<dae::GameObject>();
    go->GetTransform().SetLocalPosition(glm::vec3{358, 180,0});
    RenderComp = std::make_unique<RenderComponent>(go.get());

    RenderComp->SetTextureFilePath("logo.png");
    go->AddComponent(std::move(RenderComp));
    m_CurrentScene->Add(std::move(go));







}
