#ifndef MapBuilderSystem_cpp
#define MapBuilderSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
psuedo-system that makes the map
^^ not an actual system; not inherited from ISystem
-----------------------------------------------------------------*/

#include <vector>
#include <assert.h>

#include <orca_array.hpp>

#include <ezprint.cpp>


extern ControlPanel control;

namespace pce{

const int map_height_y = 2;
const int map_width_x = 9;
const int map_depth_z = 9;


class MapBuilderSystem {
public:
MapBuilderSystem() : map_array_(9, 2, 9) {
  ezp::print_item("constructing MapBuilderSystem");
}

Entity CreateBlockEntity(glm::ivec3 index) {
  Entity block = control.CreateEntity();
    const glm::dvec3 start_position = -glm::dvec3(index) - glm::dvec3(0, -1, 10) + origin_index_;
    // control.AddComponent(block, pce::Block{.type_index = 1});
    control.AddComponent(block, pce::MapArray{.index = index});
    control.AddComponent(block, pce::Position{
      .actual = start_position
      // .actual=((glm::dvec3(index) - origin_index_))/5.0,
      // .rotated=((glm::dvec3(index) - origin_index_))/5.0
    });
    control.AddComponent(block, pce::Radar{});
  ezp::print_labeled_item("entity start position for entity: ", block);
  vezp::print_dvec3(start_position);
  return block;
}


void CreateMapArray() {
  origin_index_ = glm::dvec3(double(map_width_x - 1.0)/2.0,
                             0.0, 
                             double(map_depth_z - 1.0)/2.0);
  // currently, this function creates a 5x5 floor
  for (int i = 0; i < map_width_x; ++i) {
    for (int j = 0; j < map_height_y; ++j) {
      for (int k = 0; k < map_depth_z; ++k) {
        if (j == 0) {
          auto entity = CreateBlockEntity(glm::ivec3(i, j, k));
          map_array_.at(i, j, k) = entity;
        } else {
          map_array_.at(i, j, k) = 0;
        }
      }
    }
  }
}


void PrintMapArray() {
  for (int i = 0; i < map_width_x; ++i) {
    for (int j = 0; j < map_height_y; ++j) {
      // ezp::print_item(MapArray[i][j]);
      for (int k = 0; k < map_depth_z; ++k) {
        ezp::print_item(map_array_.at(i, j, k));
      }
    }
  }
}

const glm::dvec3 ProvideOriginIndex() const {
  return origin_index_;
}


const orca_array::array3d<uint32_t>& ProvideMapArray() {
  return map_array_;
}

private:
// uint32_t MapArray[map_width_x][map_height_y][map_depth_z];
glm::dvec3 origin_index_;
orca_array::array3d<uint32_t> map_array_;
// std::vector<std::vector<std::vector<uint32_t>>> AltMapArray;

};
}
#endif /* MapBuilderSystem_cpp */
