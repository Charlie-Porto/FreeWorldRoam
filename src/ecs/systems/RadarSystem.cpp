#ifndef RadarSystem_cpp
#define RadarSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
system to reliably detect the positions of entities
-----------------------------------------------------------------*/

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

#include <ezprint.cpp>
#include <vezprint.cpp>
#include <math_objects/LineVectorForm.cpp>


#include "subsystems/spacePixelConversionFunctions.cpp"
#include "subsystems/simpleDrawingFunctions.cpp"
#include "../System.cpp"

extern ControlPanel control;

namespace pce{
class RadarSystem : public ISystem {
public:

void UpdateEntities() {
  for (auto const& entity : entities) {
    auto const& position = control.GetComponent<pce::Position>(entity);
    auto& radar = control.GetComponent<pce::Radar>(entity);

    radar.view_sphere_hitpoint = glm::normalize((position.rotated));
    radar.hitpoint_corresponding_pixel = -pce::pix_map::fastconvertPointOnViewSphereToPixel(
    // radar.hitpoint_corresponding_pixel = -pce::pix_map::convertPointOnViewSphereToPixel(
      radar.view_sphere_hitpoint, glm::dvec3(0, 0, 0)
    );
    
    const double distance = glm::dot(position.rotated, position.rotated);
    const double render_radius = 8.0 * ((10.0/distance) * 1.0);

    // pce::quickdraw::drawSmallCircleAtVec2(radar.hitpoint_corresponding_pixel, {230, 80, 20, 255});
    pce::quickdraw::drawCircleAtVec2(radar.hitpoint_corresponding_pixel, render_radius);
    
  }
}

private:
};
}
#endif /* RadarSystem_cpp */
