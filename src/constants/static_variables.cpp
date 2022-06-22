#ifndef static_variables_cpp
#define static_variables_cpp


/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
to store static consts used in the project
-----------------------------------------------------------------*/

namespace global_const {

// screen
const int screen_x = 1000;
const int screen_y = 672;

// lens
const double lense_curve_index = 0.3;

// pixel mapping
const double pixel_angle_in_3space = .014;

// entities
const double block_side_length = 1.0;

// camera static
const double view_sphere_radius = 1.0;

// camera movement
const double movement_speed = .3;
const double view_movement_angle = 1.5;

}


#endif /* static_variables_cpp */
