//
// Created by omen on 05/03/2026.
//

#include "DebugComponent.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_plot.h>

#include <chrono>
#include <algorithm>
#include <vector>

//#include "GameObject.h"
void dae::DebugComponent::Update(float)
{

}

void dae::DebugComponent::Draw()
{
    WindowIntBenchmark();
    WindowGameObjectWindow();
}




void DebugComponent::WindowIntBenchmark() {
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
        ImGui::PushStyleColor(ImGuiCol_PlotLines, IM_COL32(255,0,0,255));

        ImGui::Text("Trash the cache");

        ImGui::PlotLines(
            "Int benchmark",
            m_IntTimings.data(),
            static_cast<int>(m_IntTimings.size()),
            0,
            nullptr,
            FLT_MAX,
            FLT_MAX,
            ImVec2(0,150)
        );

        ImGui::PopStyleColor();
    }

    ImGui::End();
}

void DebugComponent::WindowGameObjectWindow()
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
        ImGui::PushStyleColor(ImGuiCol_PlotLines, IM_COL32(0,255,0,255));

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
        ImGui::PushStyleColor(ImGuiCol_PlotLines, IM_COL32(0,0,255,255));

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

void DebugComponent::RunIntBenchmark()
{
    m_IntTimings.clear();

    const size_t size = 1 << 26;
    std::vector<int> arr(size, 1);

    for (int step = 1; step <= 1024; step *= 2)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < arr.size(); i += step)
        {
            arr[i] *= 2;
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        float durationMs = static_cast<float>(duration) / 1000.0f;

        m_IntTimings.push_back(durationMs);
    }
}

void DebugComponent::RunGameObject3DBenchmark()
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

        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        float durationMs = static_cast<float>(duration) / 1000.0f;

        m_GameObject3D.push_back(durationMs);
    }
}

void DebugComponent::RunGameObject3DAltBenchmark()
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

        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        float durationMs = static_cast<float>(duration) / 1000.0f;

        m_GameObject3DAlt.push_back(durationMs);
    }
}