#include "main.h"

#ifndef BOSS_H
#define BOSS_H

class Boss {
public:
    Boss() {}
    Boss(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    int health;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
private:
    VAO *object, *object1;
};

#endif // BOSS_H
