#include "main.h"

#ifndef BARREL_H
#define BARREL_H

class Barrel {
public:
    Barrel() {}
    Barrel(float x, float y, float z, color_t color);
    glm::vec3 position;
    int points, powerup_present;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    double speed;
private:
    VAO *object, *object1;
};

#endif // BARREL_H
