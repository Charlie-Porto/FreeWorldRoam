#ifndef squareDrawingFunctions_cpp
#define squareDrawingFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
functions to draw squares
-----------------------------------------------------------------*/

#include <glm/vec2.hpp>

#include <ezprint.cpp>
#include <vezprint.cpp>
#include <drawing_functions.cpp>
#include <render_functions.cpp>
#include "simpleDrawingFunctions.cpp"
#include "../../../SDL_core/simulation_manager.cpp"
#include "../../../constants/static_variables.cpp"


namespace pce {
namespace draw {


void drawQuadrilateral(const std::vector<glm::dvec2> points, std::vector<int> color) {
  const std::vector<glm::dvec2> cartesian_points = pce::quickdraw::ConvertGroupCartesianPointstoSDL(points);
  SDL_SetRenderDrawColor(Simulation::renderer, color[0], color[1], color[2], color[3]);
  for (int i = 0; i < cartesian_points.size(); ++i) {
    SDL_RenderDrawLine(
      Simulation::renderer,
      cartesian_points[i].x, cartesian_points[i].y,
      cartesian_points[(i+1) % cartesian_points.size()].x, cartesian_points[(i+1) % cartesian_points.size()].y
    );                                           
  }
  SDL_SetRenderDrawColor(Simulation::renderer, 0, 0, 0, 255);
}


}
}




#endif /* squareDrawingFunctions_cpp */
