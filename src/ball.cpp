#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z, color_t color, float angle, float angle1) {
    this->position = glm::vec3(x, y, z);
    this->speed = glm::vec3(0, 0.1f*angle1, 0);
    this->rotation = 0;
    this->angle = angle;
    this->angle1 = angle1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.2f,-0.2f,-0.2f, // triangle 1 : begin
        -0.2f,-0.2f, 0.2f,
        -0.2f, 0.2f, 0.2f, // triangle 1 : end
        0.2f, 0.2f,-0.2f, // triangle 2 : begin
        -0.2f,-0.2f,-0.2f,
        -0.2f, 0.2f,-0.2f, // triangle 2 : end
        0.2f,-0.2f, 0.2f,
        -0.2f,-0.2f,-0.2f,
        0.2f,-0.2f,-0.2f,   
        0.2f, 0.2f,-0.2f,
        0.2f,-0.2f,-0.2f,
        -0.2f,-0.2f,-0.2f,
        -0.2f,-0.2f,-0.2f,
        -0.2f, 0.2f, 0.2f,
        -0.2f, 0.2f,-0.2f,
        0.2f,-0.2f, 0.2f,
        -0.2f,-0.2f, 0.2f,
        -0.2f,-0.2f,-0.2f,
        -0.2f, 0.2f, 0.2f,
        -0.2f,-0.2f, 0.2f,
        0.2f,-0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f,-0.2f,-0.2f,
        0.2f, 0.2f,-0.2f,
        0.2f,-0.2f,-0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f,-0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f, 0.2f,-0.2f,
        -0.2f, 0.2f,-0.2f,
        0.2f, 0.2f, 0.2f,
        -0.2f, 0.2f,-0.2f,
        -0.2f, 0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        -0.2f, 0.2f, 0.2f,
        0.2f,-0.2f, 0.2f
    };
    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);

    static const GLfloat vertex_buffer_data1[] = {
        -0.2f,-0.2f,-0.2f, // triangle 1 : begin
        -0.2f,-0.2f, 0.2f,
        -0.2f, 0.2f, 0.2f, // triangle 1 : end
        0.2f, 0.2f,-0.2f, // triangle 2 : begin
        -0.2f,-0.2f,-0.2f,
        -0.2f, 0.2f,-0.2f, // triangle 2 : end
        0.2f,-0.2f, 0.2f,
        -0.2f,-0.2f,-0.2f,
        0.2f,-0.2f,-0.2f,   
        0.2f, 0.2f,-0.2f,
        0.2f,-0.2f,-0.2f,
        -0.2f,-0.2f,-0.2f,
        -0.2f,-0.2f,-0.2f,
        -0.2f, 0.2f, 0.2f,
        -0.2f, 0.2f,-0.2f,
        0.2f,-0.2f, 0.2f,
        -0.2f,-0.2f, 0.2f,
        -0.2f,-0.2f,-0.2f,
        -0.2f, 0.2f, 0.2f,
        -0.2f,-0.2f, 0.2f,
        0.2f,-0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f,-0.2f,-0.2f,
        0.2f, 0.2f,-0.2f,
        0.2f,-0.2f,-0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f,-0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        0.2f, 0.2f,-0.2f,
        -0.2f, 0.2f,-0.2f,
        0.2f, 0.2f, 0.2f,
        -0.2f, 0.2f,-0.2f,
        -0.2f, 0.2f, 0.2f,
        0.2f, 0.2f, 0.2f,
        -0.2f, 0.2f, 0.2f,
        0.2f,-0.2f, 0.2f
    };

    this->object1 = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data1, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate, rotate, MVP, rotate1;
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

    Matrices.model = glm::mat4(1.0f);
    translate = glm::translate (this->position);    // glTranslatef
    rotate    = glm::rotate((float) (45.0f * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate1 = glm::rotate((float) (45.0f * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

