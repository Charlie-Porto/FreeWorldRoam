#ifndef cameraOperatorFunctions_cpp
#define cameraOperatorFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
free functions to assist the CameraOperatorSystem
-----------------------------------------------------------------*/

#include <cmath>
#include <glm/vec3.hpp>
#include <glm/ext/quaternion_double.hpp>
#include <camera_functions.cpp>
#include <virtual_keyboard.cpp>
#include <ezprint.cpp>

namespace pce {
namespace cam_op {

const double PI = 3.14159265;

void updateCameraReverseRotationVersor(EyeCamera& camera) {
  const glm::dquat vert_rot_versor = cam_func::getCameraVerticalRotationVersor(-camera.y_angle);
  const glm::dquat horiz_rot_versor = cam_func::getCameraHorizontalRotationVersor(camera.xz_angle);
  camera.rotation_versor = horiz_rot_versor * vert_rot_versor;
}


void moveCameraViewDirectionLateral(EyeCamera& camera, const double& direction) {
  camera.xz_angle += global_const::view_movement_angle * direction;
  const double xz_circle_radius = cos(camera.y_angle/180.0 * PI) * global_const::view_sphere_radius;
  camera.view_direction.x = sin(camera.xz_angle/180.0 * PI) * xz_circle_radius;
  camera.view_direction.z = cos(camera.xz_angle/180.0 * PI) * xz_circle_radius;
  updateCameraReverseRotationVersor(camera);
}
void moveCameraViewDirectionVertical(EyeCamera& camera, const double& direction) {
  camera.y_angle += global_const::view_movement_angle * direction;
  camera.view_direction.y = sin(camera.y_angle/180.0 * PI) * global_const::view_sphere_radius;
  moveCameraViewDirectionLateral(camera, 0.0);
}


void moveCameraLaterally(EyeCamera& camera, const glm::dvec3& direction) {
  glm::dvec3 orthogonal_view_direction = glm::normalize(glm::dvec3(camera.view_direction.z, 0.j,
                                                    -camera.view_direction.x));
  // vezp::print_labeled_dvec3("direction vector", camera.view_direction);
  // vezp::print_labeled_dvec3("orthogonal direction vector", orthogonal_view_direction);
  auto const movement_vector = glm::dvec3(
    (direction.x * -orthogonal_view_direction.x + direction.z * camera.view_direction.x),
    0.0,
    (direction.z * camera.view_direction.z + -direction.x * orthogonal_view_direction.z)
  ) * global_const::movement_speed;
  camera.position += movement_vector;
}


void moveCameraVertically(EyeCamera& camera, const double& direction) {
  camera.position.y += global_const::movement_speed * direction;
}



void updateEyeCameraKeyboardPosition(EyeCamera& camera, VirtualKeyboard& keyboard,
                             bool if_mode_switch_available) {
  JoystickReport joystick_report = keyboard.check_buttons(); 
  if (joystick_report.R_pressed == true) { 
    ezp::print_item("JOYSTICK: RIGHT");
    moveCameraViewDirectionLateral(camera, 1.0);
  }
  if (joystick_report.L_pressed == true) {
    ezp::print_item("JOYSTICK: LEFT");
    moveCameraViewDirectionLateral(camera, -1.0);
  }
  if (joystick_report.Up_pressed == true) {
    ezp::print_item("JOYSTICK: UP");
    moveCameraViewDirectionVertical(camera, 1.0);
  }
  if (joystick_report.Down_pressed == true) {
    ezp::print_item("JOYSTICK: DOWN");
    moveCameraViewDirectionVertical(camera, -1.0);
  }
  if (joystick_report.W_pressed == true) {
    ezp::print_item("JOYSTICK: W");
    moveCameraLaterally(camera, glm::dvec3(0, 0, -1));
  }
  if (joystick_report.S_pressed == true) {
    ezp::print_item("JOYSTICK: S");
    moveCameraLaterally(camera, glm::dvec3(0, 0, 1));
  }
  if (joystick_report.A_pressed == true) {
    ezp::print_item("JOYSTICK: A");
    moveCameraLaterally(camera, glm::dvec3(-1, 0, 0));
  }
  if (joystick_report.D_pressed == true) {
    ezp::print_item("JOYSTICK: D");
    moveCameraLaterally(camera, glm::dvec3(1, 0, 0));
  }
  if (camera.flight_mode_activated) {
    if (joystick_report.r_pressed == true) {
      ezp::print_item("JOYSTICK: R");
      moveCameraVertically(camera, -1.0);
    }
    if (joystick_report.F_pressed == true) {
      ezp::print_item("JOYSTICK: F");
      moveCameraVertically(camera, 1.0);
    }
  } else {
    if (joystick_report.SPACE_pressed == true) {
      ezp::print_item("JOYSTICK: SPACE");
      if (!camera.currently_jumping) {
        camera.currently_jumping = true;       
      }
      moveCameraVertically(camera, 1.0);
    }
  }
  if (joystick_report.X_pressed == true) {
    ezp::print_item("JOYSTICK: X");
    if (if_mode_switch_available) {
      camera.flight_mode_activated = !camera.flight_mode_activated;
    } else {
      ezp::print_item("Mode Switch not yet available -- wait a few seconds after your last switch.");
    }
  }
}


}
}



#endif /* cameraOperatorFunctions_cpp */
