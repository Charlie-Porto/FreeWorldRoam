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
// #include "physicsFunctionsForCamera.cpp"
#include "../System.cpp"

extern ControlPanel control;

namespace pce{
class CameraOperatorSystem : public ISystem {
public:
  CameraOperatorSystem (){
    time_ = 0.0;
    mode_switch_timer_ = -1.0;
    mode_at_start_ = false;
  }
  
  void Init() {
    camera_.position = glm::dvec3(0, 0, 0);
    camera_.view_direction = normalize(glm::dvec3(0, -1, 1));
    camera_.xz_angle = 0.0;
    camera_.y_angle = 0.0;
    camera_.rotation_versor = {1.0, 0.0, 0.0, 0.0};
    camera_.transformation_vector = {0, 0, 0};
    camera_.flight_mode_activated = false;
  }

  const glm::dquat ProvideCamVersor() const {
    return camera_.rotation_versor;
  }
  const glm::dvec3 ProvideCamTransformVector() const {
    return -camera_.position;
  }
  const glm::dvec3 ProvideCamPosition() const {
    return camera_.position;
  }

  
  void CheckModeSwitchButtonTimer(double sdl_time) {
    const bool mode_at_start = camera_.flight_mode_activated;
    time_change_ = sdl_time = time_; 
    time_ = sdl_time;
    mode_switch_timer_ -= time_change_;
    if (mode_switch_timer_ < 0.0) {
      if_mode_switch_available_ = true;
    }
  }


  void UpdateCameraPositionAndAngle(const double sdl_time) {
    CheckModeSwitchButtonTimer(sdl_time);
    pce::cam_op::updateEyeCameraKeyboardPosition(camera_, keyboard_, if_mode_switch_available_); 
    if (mode_at_start_ != camera_.flight_mode_activated) {
      mode_switch_timer_ = 1.0;   
      if_mode_switch_available_ = false;
    }

    // if (camera_.currently_airborne || camera_.currently_jumping) {
      // pce::cam_phys::updateCameraAirbornePosition(camera_, time_change_, map_array, map_origin_index);
    // }

    vezp::print_labeled_dvec3("cam position", camera_.position);
  }

private:
  double time_;
  double time_change_;
  bool mode_at_start_;
  double mode_switch_timer_;
  bool if_mode_switch_available_;
  EyeCamera camera_;
  VirtualKeyboard keyboard_;
  

};
}
#endif /* CameraOperatorSystem_cpp */
