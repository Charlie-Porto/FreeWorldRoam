#ifndef playerMovementFunctions_cpp
#define playerMovementFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
free functions to assist the PlayerMovementSystem class.
-----------------------------------------------------------------*/

#include <cmath>
#include <orca_array.hpp>
#include <glm/vec3.hpp>
#include <ezprint.cpp>
#include "../../constants/static_variables.cpp"
#include "MapBuilderSystem.cpp"

extern ControlPanel control;

namespace pce{
namespace motion {

const double GRAVITY = -9.81;

void obtainSurroundingBlockArray(const orca_array::array3d<uint32_t>& map_array,
                                 const glm::dvec3& position,
                                 const glm::dvec3& map_origin_index, 
                                 orca_array::array3d<uint32_t>& surrounding_blocks) {
    // const glm::dvec3 player_current_index = map_origin_index + 
  int i = 0;
}


// uint32_t getEntityByPositionFromMapArray(const orca_array::array3d<uint32_t>& map_array, 
                                        //  const glm::dvec3& position, 
                                        //  const glm::dvec3& map_origin_index) {
uint32_t getEntityByPositionFromMapArray(const glm::dvec3& position) {
  const glm::dvec3 index = pce::MapBuilderSystem::origin_index_ + position;
  return pce::MapBuilderSystem::map_array_.at(int(index.x), int(index.y), int(index.z));
}


void moveAirbornePlayer(pce::Motion& motion, pce::Orientation& orientation) {
  const double distance_eq_a = GRAVITY * pow(motion.time_airborne, 2.0) / 2.0;
  const double distance_eq_b = motion.time_airborne * motion.initial_jump_velocity.y;
  const double current_distance_y = distance_eq_a + distance_eq_b;
  const double distance_change_y = current_distance_y - motion.airborne_distance; 
  if (distance_change_y < 0) {
    motion.is_falling = true;
    motion.is_jumping = false;
  }
  // check if block directly below
  const Entity near_entity = getEntityByPositionFromMapArray(orientation.position); 
  
  if (near_entity != 0) {
    auto const& entity_position = control.GetComponent<pce::Position>(near_entity);
    vezp::print_labeled_dvec3("near entity position: ", entity_position.actual);

  }

  
}

// move playerOnGround(pce::Motion& motion, )
// }
}
}



#endif /* playerMovementFunctions_cpp */
