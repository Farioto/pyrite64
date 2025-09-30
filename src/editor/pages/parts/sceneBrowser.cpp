/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "sceneBrowser.h"

#include "imgui.h"
#include "../../../context.h"

Editor::SceneBrowser::SceneBrowser() {
}

Editor::SceneBrowser::~SceneBrowser() {
}

void Editor::SceneBrowser::draw()
{
  if (ImGui::Button("Add Scene")) {
    ctx.project->getScenes().add();
  }

  ImGui::NewLine();

  auto &scenes = ctx.project->getScenes().getEntries();
  for (auto &scene : scenes) {
    ImGui::SameLine();
    std::string label = "Scene-" + std::to_string(scene.id);
    if (ImGui::Button(label.c_str(), {64, 64})) {
      ctx.project->getScenes().loadScene(scene.id);
    }
  }
}
