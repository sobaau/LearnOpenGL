#ifndef ENTITIY_H_
#define ENTITIY_H_

#include <glm/glm.hpp>
#include <string>

struct Entity
{
public:
    Entity() = delete;
    Entity(glm::vec3 &position, std::string &name);
    glm::vec3 position;
    std::string name;
};
#endif // ENTITIY_H_