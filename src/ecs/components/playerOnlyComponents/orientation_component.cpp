#ifndef orientation_component_cpp
#define orientation_component_cpp

#include <glm/vec3.hpp>

namespace pce {

struct Orientation {
  glm::dvec3 position;  
  glm::dvec3 view_direction;
};

}

#endif /* orientation_component_cpp */
