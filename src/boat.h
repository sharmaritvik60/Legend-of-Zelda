#include "main.h"

#ifndef BOAT_H
#define BOAT_H

class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z, color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    float rotation, wind_rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object, *object1, *object2, *object3;
};

#endif // BOAT_H
