#include "entitiy.h"
#include <glm/glm.hpp>
#include <string>

Entity::Entity(glm::vec3 &position, std::string &name) : position(position), name(name){ }

