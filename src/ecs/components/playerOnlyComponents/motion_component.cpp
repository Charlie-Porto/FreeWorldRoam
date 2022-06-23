#ifndef motion_component_cpp
#define motion_component_cpp

#include <glm/vec3.hpp>

namespace pce {

struct Motion {
  bool is_falling;
  bool is_jumping;
  double speed;
  glm::dvec3 travel_direction;
  glm::dvec3 initial_jump_velocity;
  double airborne_distance;
  double time_airborne;
};

}

#endif /* motion_component_cpp */
