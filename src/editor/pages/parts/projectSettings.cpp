/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "projectSettings.h"

#include "imgui.h"
#include "../../../context.h"
#include "../../../utils/logger.h"
#include "misc/cpp/imgui_stdlib.h"
#include "../../imgui/helper.h"

bool Editor::ProjectSettings::draw()
{
  if (ImGui::CollapsingHeader("General", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::InpTable::start("General");
    ImGui::InpTable::addString("Name", ctx.project->conf.name);
    ImGui::InpTable::addString("ROM-Name", ctx.project->conf.romName);
    ImGui::InpTable::end();
  }
  if (ImGui::CollapsingHeader("Environment", ImGuiTreeNodeFlags_DefaultOpen)) {
    ImGui::InpTable::start("Environment");
    ImGui::InpTable::addPath("Emulator", ctx.project->conf.pathEmu);
    ImGui::InpTable::addPath("N64_INST", ctx.project->conf.pathN64Inst, true, "$N64_INST");
    ImGui::InpTable::end();
  }

  // close button, positioned to bottom right corner
  ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 54);
  ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 36);
  if (ImGui::Button("Save")) {
    ctx.project->save();
    return true;
  }
  return false;
}
