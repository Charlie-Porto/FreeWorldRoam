#ifndef PlayerMovementSystem_cpp
#define PlayerMovementSystem_cpp


#include <ezprint.cpp>

#include "playerMovementFunctions.cpp"
#include "../System.cpp"

extern ControlPanel control;

namespace pce{
class PlayerMovementSystem : public ISystem {
public:

void UpdateEntities(double sdl_time) {
  // ezp::print_item("updating player movement system");
  for (auto const& entity : entities) {
    auto& motion = control.GetComponent<pce::Motion>(entity);
    auto& orientation = control.GetComponent<pce::Orientation>(entity);
    
    Entity entity_at_current_pos = pce::motion::getEntityByPositionFromMapArray(orientation.position);
    ezp::print_labeled_item("Entity at current position: ", entity_at_current_pos);
    
    // if (motion.time_airborne > 0.0) {pce::motion::moveAirbornePlayer(motion, orientation);}
    // else {
     
    // }
    
  }
}

private:
  
 
};
}
#endif /* PlayerMovementSystem_cpp */
