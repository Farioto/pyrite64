/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "editorMain.h"

#include <atomic>
#include <cstdio>
#include <mutex>

#include "imgui.h"
#include "SDL3/SDL_dialog.h"

namespace
{
  bool isHoverAdd = false;
  bool isHoverLast = false;

  constinit bool fileSelectIsOpen{false};
  constinit std::mutex mtxProjectPath{};
  constinit std::atomic_bool hasProjectPath{false};
  constinit std::string projectPath{};

  void cbOpenProject(void *userdata, const char * const *filelist, int filter) {
    std::lock_guard lock{mtxProjectPath};
    projectPath = (filelist && filelist[0]) ? filelist[0] : "";
    hasProjectPath = true;
  }
}

Editor::Main::Main(SDL_GPUDevice* device)
  : texTitle{device, "data/img/titleLogo.png"},
  texBtnAdd{device, "data/img/cardAdd.svg"},
  texBtnOpen{device, "data/img/cardLast.svg"}
{
}

Editor::Main::~Main() {
}

void Editor::Main::draw()
{
  auto &io = ImGui::GetIO();

  ImGui::SetNextWindowPos({0,0}, ImGuiCond_Appearing, {0.0f, 0.0f});
  ImGui::SetNextWindowSize({io.DisplaySize.x, io.DisplaySize.y}, ImGuiCond_Always);
  ImGui::Begin("WIN_MAIN", 0,
    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar
    | ImGuiWindowFlags_NoBackground
  );

  ImVec2 centerPos = {io.DisplaySize.x / 2, io.DisplaySize.y / 2};
  auto logoSize = texTitle.getSize(0.75f);

  if (isHoverAdd || isHoverLast) {
    ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
  } else {
    ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
  }

  ImGui::SetCursorPos({
    centerPos.x - (logoSize.x/2),
    centerPos.y - (logoSize.y/2) - 150
  });
  ImGui::Image(ImTextureID(texTitle.getGPUTex()),logoSize);

  constexpr float BTN_SPACING = 160;

  auto getBtnPos = [&](ImVec2 size, bool isLeft) {
    return ImVec2{
      centerPos.x - (size.x/2) + (isLeft ? -BTN_SPACING : BTN_SPACING),
      centerPos.y - (size.y/2) + 120
    };
  };

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));

  auto btnSizeAdd = texBtnAdd.getSize(isHoverAdd ? 0.85f : 0.8f);
  ImGui::SetCursorPos(getBtnPos(btnSizeAdd, true));
  ImGui::ImageButton("New Project",
      ImTextureID(texBtnAdd.getGPUTex()),
      btnSizeAdd, {0,0}, {1,1}, {0,0,0,0},
      {1,1,1, isHoverAdd ? 1 : 0.8f}
  );
  isHoverAdd = ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly);

  auto btnSizeLast = texBtnOpen.getSize(isHoverLast ? 0.85f : 0.8f);
  ImGui::SetCursorPos(getBtnPos(btnSizeLast, false));
  bool wantsOpen = ImGui::ImageButton("Open Project",
      ImTextureID(texBtnOpen.getGPUTex()),
      btnSizeLast, {0,0}, {1,1}, {0,0,0,0},
      {1,1,1,isHoverLast ? 1 : 0.8f}
  );
  isHoverLast = ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly);

  ImGui::PopStyleColor(3);

  // version
  ImGui::SetCursorPos({14, io.DisplaySize.y - 30});
  ImGui::Text("Pyrite64 [v0.0.0-alpha]   -   (c) 2025 Max Bebök (HailToDodongo)");

  ImGui::End();

  if (wantsOpen && !fileSelectIsOpen) {
    SDL_ShowOpenFolderDialog(cbOpenProject, nullptr, SDL_GL_GetCurrentWindow(), nullptr, false);
    fileSelectIsOpen = true;
  }

  if (hasProjectPath) {
    std::lock_guard lock{mtxProjectPath};
    if (!projectPath.empty()) {
      printf("Open project: %s\n", projectPath.c_str());
    }
    fileSelectIsOpen = false;
    hasProjectPath = false;
  }
}
