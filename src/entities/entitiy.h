#ifndef ENTITIY_H_
#define ENTITIY_H_
#include <glm/glm.hpp>
#include <string>
#include <algorithm>

struct Entity
{
public:
    virtual glm::vec3 get_position() = 0;
    virtual std::string get_name() = 0;
};
#endif // ENTITIY_H_