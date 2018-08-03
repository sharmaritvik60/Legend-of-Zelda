#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color, float angle, float angle1);
    glm::vec3 position;
    glm::vec3 speed;
    float rotation, angle, angle1;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
private:
    VAO *object, *object1;
};

#endif // BALL_H
