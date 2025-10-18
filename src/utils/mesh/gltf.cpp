/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#include "gltf.h"

void Utils::Mesh::t3dmToMesh(const T3DMData &t3dmData, Renderer::Mesh &mesh)
{
  mesh.vertices.clear();
  mesh.indices.clear();

  uint16_t idx = 0;
  for (auto &model : t3dmData.models) {
    printf("Tex: %s\n", model.material.texA.texPath.c_str());
    for (auto &tri : model.triangles) {

      for (auto &vert : tri.vert) {

        uint8_t r = (vert.rgba >> 24) & 0xFF;
        uint8_t g = (vert.rgba >> 16) & 0xFF;
        uint8_t b = (vert.rgba >> 8) & 0xFF;
        uint8_t a = (vert.rgba >> 0) & 0xFF;

        mesh.vertices.push_back({
          {vert.pos[0], vert.pos[1], vert.pos[2]},
          vert.norm,
          {r,g,b,a},
          glm::ivec2(vert.s, vert.t)
        });
        /*printf("v: %d,%d,%d norm: %d uv: %d,%d col: %08X\n",
          vert.pos[0], vert.pos[1], vert.pos[2],
          vert.norm,
          vert.s, vert.t,
          vert.rgba
        );*/
      }

      mesh.indices.push_back(idx++);
      mesh.indices.push_back(idx++);
      mesh.indices.push_back(idx++);
    }
  }
}
