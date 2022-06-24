#ifndef spacePixelConversionFunctions_cpp
#define spacePixelConversionFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions for converting 2d pixels to 3space and vice versa 
(some overlap in discription with cameraPixel Mapper -- to fix this)
-----------------------------------------------------------------*/

#include <cmath>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <ezprint.cpp>
#include <sign.cpp>
#include "pixelSpaceMappingFunctions.cpp"

namespace pce {
namespace pix_map {


glm::dvec3 convertPixelToPointOnViewSphere(const glm::dvec2& pixel,
                                           const glm::dvec3& view_sphere_center) {
  auto base_vector = glm::dvec3(0.0, 0.0, -1.0);
  for (int i = 0; i < abs(pixel.x); ++i) {
    base_vector = pce::pix_map::calculateHorizontalNeighborPixelVec3(base_vector, pce::math::sign(pixel.x));
  }
  for (int i = 0; i < abs(pixel.y); ++i) {
    base_vector = pce::pix_map::calculateVerticalNeighborPixelVec3(base_vector, -pce::math::sign(pixel.y));
  }
  auto b = (view_sphere_center + base_vector);
  return b;
} // the below function is not yet finished but is gettiing there
glm::dvec2 fastconvertPointOnViewSphereToPixel(const glm::dvec3& point,
                                               const glm::dvec3& view_sphere_center) {
  if (point.z < view_sphere_center.z) {
  const double y_circle_radius = global_const::lense_curve_index * sqrt(pow(point.y, 2.0) + pow(point.z, 2.0)); 
  const double y_point_angle = abs(atan(point.y/point.z));
  const double y_pix_angle_arc_length = y_circle_radius * abs((global_const::pixel_angle_in_3space * PI/180.0)); 
  const double y_point_arc_length = y_point_angle * (global_const::pixel_angle_in_3space * PI/180.0);
  const double y_pixel = 70.0 * y_point_arc_length/y_pix_angle_arc_length * pce::math::sign(point.y);
  // const double y_pixel = y_point_arc_length/y_pix_angle_arc_length * pce::math::sign(point.y);

  const double x_point_angle = abs(atan(point.x / point.z));
  const double x_pix_angle_arc_length = abs(global_const::lense_curve_index * global_const::view_sphere_radius * (global_const::pixel_angle_in_3space * PI/180.0));
  const double x_point_arc_length = abs(x_point_angle * global_const::lense_curve_index * global_const::view_sphere_radius);
  const double x_pixel = x_point_arc_length/x_pix_angle_arc_length * pce::math::sign(point.x);
  // const double x_pixel = 5 * x_point_arc_length/x_pix_angle_arc_length * pce::math::sign(point.x);
  return glm::dvec2(x_pixel, y_pixel);
  }
  return glm::dvec2(3000, 3000);
}


glm::dvec2 convertPointOnViewSphereToPixel(const glm::dvec3& point,
                                           const glm::dvec3& view_sphere_center) {
  const double granularity = .001;
  const int search_cycles = 2000;
  auto mpoint = glm::dvec3(point.x, point.y, point.z) - view_sphere_center;
  int i = 0;
  while (abs(mpoint.y) >= granularity && i <= search_cycles) {
    mpoint = pce::pix_map::calculateVerticalNeighborPixelVec3(mpoint, pce::math::sign(point.y));
    ++i;
  }
  if (i >= search_cycles) {
    return glm::dvec2(2000, 2000);
  }
  int j = 0;
  while (abs(mpoint.x) >= granularity && j <= search_cycles) {
    mpoint = pce::pix_map::calculateHorizontalNeighborPixelVec3(mpoint, -pce::math::sign(point.x));
    ++j;
  }
  auto v = glm::dvec2(double(j) * pce::math::sign(point.x), double(i) * pce::math::sign(point.y));
  return v;
}

}
}



#endif /* spacePixelConversionFunctions_cpp */
