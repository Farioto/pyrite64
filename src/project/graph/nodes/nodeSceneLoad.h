/**
* @copyright 2026 - Max Bebök
* @license MIT
*/
#pragma once

#include "baseNode.h"
#include "../../../context.h"
#include "../../../utils/hash.h"
#include "../../../editor/imgui/helper.h"

namespace Project::Graph::Node
{
  class SceneLoad : public Base
  {
    private:
      uint32_t sceneId{};

    public:
      constexpr static const char* NAME = ICON_MDI_EARTH_BOX " Load Scene";

      SceneLoad()
      {
        uuid = Utils::Hash::randomU64();
        setTitle(NAME);
        setStyle(std::make_shared<ImFlow::NodeStyle>(IM_COL32(90,191,93,255), ImColor(0,0,0,255), 3.5f));

        addIN<TypeLogic>("", ImFlow::ConnectionFilter::SameType(), PIN_STYLE_LOGIC);
        addOUT<TypeLogic>("", PIN_STYLE_LOGIC);
      }

      void draw() override {
        ImGui::SetNextItemWidth(110.f);
        ImGui::VectorComboBox("##Scene", ctx.project->getScenes().getEntries(), sceneId);
        //showIN("", 0, ImFlow::ConnectionFilter::SameType(), PIN_STYLE_LOGIC);
      }

      void serialize(nlohmann::json &j) override {
        j["sceneId"] = sceneId;
      }

      void deserialize(nlohmann::json &j) override {
        sceneId = j.value("sceneId", 0);
      }

      void build(BuildCtx &ctx) override
      {
        ctx.localConst("uint16_t", "sceneId", std::to_string(sceneId))
          .line("P64::SceneManager::load(sceneId);")
        ;
      }
  };
}