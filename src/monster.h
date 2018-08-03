#include "main.h"

#ifndef MONSTER_H
#define MONSTER_H

class Monster {
public:
    Monster() {}
    Monster(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
private:
    VAO *object, *object1;
};

#endif // MONSTER_H
