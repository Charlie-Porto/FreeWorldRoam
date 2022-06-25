#ifndef physicsSystemFunctions_cpp
#define physicsSystemFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
free functions to assist the Physics System
-----------------------------------------------------------------*/

#include <cmath>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include <ezprint.cpp>

#include "MapBuilderSystem.cpp"
#include "../../constants/static_variables.cpp"

namespace pce {
namespace phys {

void calculateAirbornePosition(pce::Motion& motion, pce::Orientation& orientation, double time) {
  motion.time_airborne += time;
  const double y_position_a = -9.81*(pow(motion.time_airborne, 2.0)) / 2.0;
  const double y_position_v = motion.initial_velocity.y * motion.time_airborne;
  const double new_y_position = y_position_a + y_position_v + motion.previous_ground_position.y;
  
  const double x_position_v = motion.initial_velocity.x * motion.time_airborne;
  const double new_x_position = x_position_v + motion.previous_ground_position.x;

  const double z_position_v = motion.initial_velocity.z * motion.time_airborne;
  const double new_z_position = z_position_v + motion.previous_ground_position.z;

  orientation.position = glm::dvec3(new_x_position, new_y_position, new_z_position);
}


void checkForMovementObstructions(pce::Orientation& orientation, pce::Motion& motion) {
  glm::dvec3 current_travel_direction = glm::normalize(orientation.position - orientation.previous_position);
  const double block_obstruction_perimeter =.2;
  
  const double x_orientation_index = MapBuilderSystem::origin_index_.x
                                   - (orientation.position.x);
  const double y_orientation_index = MapBuilderSystem::origin_index_.y
                                   - (orientation.position.y);
  const double z_orientation_index = MapBuilderSystem::origin_index_.z
                                   - (orientation.position.z);
  
  const double x_probing_index = x_orientation_index + current_travel_direction.x;
  const double y_probing_index = y_orientation_index + current_travel_direction.y;
  const double z_probing_index = z_orientation_index + current_travel_direction.z;

  ezp::print_labeled_item("x_orientation_index: ", x_orientation_index);
  ezp::print_labeled_item("y_orientation_index: ", y_orientation_index);
  ezp::print_labeled_item("z_orientation_index: ", z_orientation_index);

  if (z_probing_index < 0 || z_probing_index > pce::map_depth_z) {
    orientation.position.z = orientation.previous_position.z; 
    ezp::print_item("at edge of map in z direction");
  }
  else if(MapBuilderSystem::map_array_.at(x_orientation_index,
                                      y_orientation_index,
                                      z_probing_index) != 0) {
    orientation.position.z = orientation.previous_position.z; 
    ezp::print_item("obstruction in Z direction");
  }

  if (y_probing_index < 2 || abs(y_probing_index) > 1 || abs(y_probing_index) > pce::map_height_y) {
    orientation.position.y = orientation.previous_position.y; 
    ezp::print_item("at edge of map in y direction");
  }
  else if (MapBuilderSystem::map_array_.at(x_orientation_index,
                                      y_probing_index,
                                      z_orientation_index) != 0) {
    ezp::print_item("***** ON TOP OF BLOCK *****");
    orientation.position.y = orientation.previous_position.y; 
    motion.is_airborne = false;
    motion.time_airborne = 0.0;
    motion.initial_velocity = glm::dvec3(0, 0, 0);
    ezp::print_item("obstruction in Y direction");
  } else {
    motion.is_airborne = true;
    // motion.initial_velocity = current_travel_direction * global_const::movement_speed;
  }

  if (x_probing_index < 0 || x_probing_index > pce::map_width_x) {
    orientation.position.x = orientation.previous_position.x; 
    ezp::print_item("at edge of map in x direction");
  }
  else if (MapBuilderSystem::map_array_.at(x_probing_index,
                                      y_orientation_index, 
                                      z_orientation_index) != 0){
    orientation.position.x = orientation.previous_position.x; 
    ezp::print_item("obstruction in X direction");
  }
}




}
}



#endif /* physicsSystemFunctions_cpp */
