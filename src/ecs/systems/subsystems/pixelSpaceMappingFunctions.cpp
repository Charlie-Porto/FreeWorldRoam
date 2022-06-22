#ifndef pixelSpaceMappingFunctions_cpp
#define pixelSpaceMappingFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions to assist in the translating of 'real' 3-space into pixel 2-space
and vice versa
-----------------------------------------------------------------*/

#include <cmath>
#include <complex>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/ext/quaternion_double.hpp>
#include <quaternion_funktions.cpp>
#include <ezprint.cpp>
#include <vezprint.cpp>
#include <vec3_functions.cpp>
#include <sign.cpp>
#include "../../../constants/static_variables.cpp"

namespace pce {
namespace pix_map {

const double PI = 3.14159265;


glm::dvec3 calculateAdjacentPixelVector3(const glm::dvec3& base_vector,
                                         const double& angle,
                                         const glm::dvec3& axis_of_rotation) {
  // can use either x or y axis as axis of rotation because we are calculating
  // increment distance which will be same in either case
  const glm::dquat rotation_quaternion = qfunc::convertAngleAxisToQuaternion(
                                             angle, axis_of_rotation);
  auto const result = glm::normalize(qfunc::rotateVector3byQuaternion(base_vector, rotation_quaternion));
  // ezp::print_item("base vector: ");
  // vezp::print_dvec3(base_vector); 
  // ezp::print_item("Adjacent Pixel Result: ");
  // vezp::print_dvec3(result); 
  return result;
}



glm::dvec3 calculateVerticalNeighborPixelVec3(const glm::dvec3& base_vector, double direction) {
  // if (direction == 0.0) {return base_vector;}
  return calculateAdjacentPixelVector3(base_vector, global_const::pixel_angle_in_3space * direction, 
                                       glm::dvec3(1.0, 0.0, 0.0));
}


glm::dvec3 calculateHorizontalNeighborPixelVec3(const glm::dvec3& base_vector, double direction) {
  // if (direction == 0.0) {return base_vector;}
  return calculateAdjacentPixelVector3(base_vector, global_const::pixel_angle_in_3space * direction, 
                                       glm::dvec3(0.0, 1.0, 0.0));
}


std::complex<double> convertAngleToComplexNumber(const double& angle) {
  return std::complex<double>(cos(angle * PI/180.0), sin(angle * PI/180.0));
}



double calculateStandardPixelDistance() {
  auto base_vector = normalize(glm::dvec3(1.0, 1.0, 1.0));
  const auto axis_of_rotation = glm::dvec3(0.0, 1.0, 0.0);
  const glm::dvec3 adjacent_pixel = pce::pix_map::calculateAdjacentPixelVector3(
                                        base_vector,
                                        global_const::pixel_angle_in_3space,
                                        axis_of_rotation);
  double dist = v3func::calculateDistanceBetweenPosition3Vectors(base_vector, adjacent_pixel);
  // ezp::print_labeled_item("distance: ", dist);
  return dist;
}

}
}

#endif /* pixelSpaceMappingFunctions_cpp */
