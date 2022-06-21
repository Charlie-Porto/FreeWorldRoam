#ifndef CameraOperatorSystem_cpp
#define CameraOperatorSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
Camera Operator System: manages the camera
-----------------------------------------------------------------*/

#include <ezprint.cpp>
#include <vezprint.cpp>
#include <eye_camera.cpp>

#include "cameraOperatorFunctions.cpp"
#include "../System.cpp"

extern ControlPanel control;

namespace pce{
class CameraOperatorSystem : public ISystem {
public:
  
  void Init() {
    camera_.position = glm::dvec3(0, 0, 0);
    camera_.view_direction = glm::dvec3(0, 0, 1);
    camera_.xz_angle = 0.0;
    camera_.y_angle = 0.0;
    camera_.rotation_versor = {1.0, 0.0, 0.0, 0.0};
    camera_.transformation_vector = {0, 0, 0};
  }

  void UpdateCameraPositionAndAngle() {
    ezp::print_item("updating Camera Position and Angle");
    pce::cam_op::updateEyeCameraPosition(camera_, keyboard_); 
    ezp::print_item("camera position: ");
    vezp::print_dvec3(camera_.position);
    ezp::print_item("camera view direction: ");
    vezp::print_dvec3(camera_.view_direction);
    
  }

private:
  EyeCamera camera_;
  VirtualKeyboard keyboard_;
  

};
}
#endif /* CameraOperatorSystem_cpp */
