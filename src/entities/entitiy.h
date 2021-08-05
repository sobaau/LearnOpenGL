#ifndef ENTITIY_H_
#define ENTITIY_H_

#include <glm/glm.hpp>

class Entity
{
    glm::vec3 position;
public:
    virtual void draw() = 0;
    [[nodiscard]] glm::vec3 getPosition() const;
};
#endif // ENTITIY_H_