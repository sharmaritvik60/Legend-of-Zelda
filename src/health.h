#include "main.h"

#ifndef HEALTH_H
#define HEALTH_H

class Health {
public:
    Health() {}
    Health(float x, float y, float z, color_t color, int health);
    glm::vec3 position;
    float rotation;
    int health;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
private:
    VAO *object;
};

#endif // HEALTH_H
