#ifndef physicsFunctionsForCamera_cpp
#define physicsFunctionsForCamera_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
physics functions to assist the camera with jumping and falling.
-----------------------------------------------------------------*/

#include <cmath>
#include <orca_array.hpp>
#include <eye_camera.cpp>
#include <ezprint.cpp>
#include "../../constants/static_variables.cpp"

namespace pce {
namespace cam_phys {

const double GRAVITY = -9.81; // meters per second squared

void updateCameraAirbornePosition (EyeCamera& camera, double time_change,
                                   const orca_array::array3d<uint32_t>& map_array,
                                   const glm::dvec3& map_origin_index) {
  double init_velocity = 0.0;
  if (camera.currently_jumping) { 
    ezp::print_item("jumping");
    init_velocity = global_const::jump_velocity; 
  }
  camera.time_airborne += time_change;
  const double a_term = GRAVITY * pow(camera.time_airborne, 2.0) / 2.0;
  const double v_term = init_velocity * camera.time_airborne;
  const double potential_y_term_addition = (-a_term + v_term);
  ezp::print_labeled_item("potential y_term addition: ", potential_y_term_addition);
  const double potential_y_term_addition_at_feet = potential_y_term_addition - 2.0;
  const glm::dvec3 potential_new_position = glm::dvec3(camera.position.x,
                                                 potential_y_term_addition_at_feet,
                                                 camera.position.z);
  
  const glm::dvec3 new_index = potential_new_position + map_origin_index;
  const uint32_t array_position_at_feet = map_array.at(int(new_index.x), int(new_index.y), int(new_index.z));
  if (potential_y_term_addition <= 0 && array_position_at_feet != 0) {
    camera.currently_airborne = false;
    camera.currently_jumping = false;
  } else {
    camera.currently_airborne = true;
  }
}


}
}



#endif /* physicsFunctionsForCamera_cpp */
