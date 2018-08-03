#include "main.h"

#ifndef ROCK_H
#define ROCK_H

class Rock {
public:
    Rock() {}
    Rock(float x, float y, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // ROCK_H
