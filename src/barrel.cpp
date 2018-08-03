#include "barrel.h"
#include "main.h"

Barrel::Barrel(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->powerup_present = 1;
    int rn = rand()%2;
    if(rn)
    {
        this->points = 50;
        color = COLOR_BLUE;
    }
    else
    {
        this->points = 100;
        color = COLOR_PINK;
    }
    float si, co, radius = 0.7f;
    static GLfloat arr[360*30];

    const static GLfloat arr1[] =
    {
        0, 0.8f, 0,
        -0.2f, 1.3f, -0.2f,
        0.2f, 1.3f, -0.2f,
        0, 0.8f, 0,
        -0.2f, 1.3f, -0.2f,
        -0.2f, 1.3f, 0.2f,
        0, 0.8f, 0,
        0.2f, 1.3f, 0.2f,
        -0.2f, 1.3f, 0.2f,
        0, 0.8f, 0,
        0.2f, 1.3f, 0.2f,
        0.2f, 1.3f, -0.2f,

        0, 1.8f, 0,
        -0.2f, 1.3f, -0.2f,
        0.2f, 1.3f, -0.2f,
        0, 1.8f, 0,
        -0.2f, 1.3f, -0.2f,
        -0.2f, 1.3f, 0.2f,
        0, 1.8f, 0,
        0.2f, 1.3f, 0.2f,
        -0.2f, 1.3f, 0.2f,
        0, 1.8f, 0,
        0.2f, 1.3f, 0.2f,
        0.2f, 1.3f, -0.2f,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 24, arr1, color, GL_FILL);

    for(int i=0;i<360;i++)
    {
        si = sin(M_PI*i/180.0f);
        co = cos(M_PI*i/180.0f);
        arr[18*i] = radius*co;
        arr[18*i+1] = 0;
        arr[18*i+2] = radius*si;
        si = sin(M_PI*(i+1)/180.0f);
        co = cos(M_PI*(i+1)/180.0f);
        arr[18*i+3] = radius*co;
        arr[18*i+4] = 0;
        arr[18*i+5] = radius*si;
        arr[18*i+6] = radius*co;
        arr[18*i+7] = 0.3f;
        arr[18*i+8] = radius*si;

        si = sin(M_PI*i/180.0f);
        co = cos(M_PI*i/180.0f);
        arr[18*i+9] = radius*co;
        arr[18*i+10] = 0;
        arr[18*i+11] = radius*si;
        arr[18*i+12] = radius*co;
        arr[18*i+13] = 0.3f;
        arr[18*i+14] = radius*si;
        si = sin(M_PI*(i+1)/180.0f);
        co = cos(M_PI*(i+1)/180.0f);
        arr[18*i+15] = radius*co;
        arr[18*i+16] = 0.3f;
        arr[18*i+17] = radius*si;
    }
    for(int i=0;i<360;i++)
    {
        si = sin(M_PI*i/180.0f);
        co = cos(M_PI*i/180.0f);
        arr[6480+9*i] = radius*co;
        arr[6480+9*i+1] = 0.3f;
        arr[6480+9*i+2] = radius*si;
        arr[6480+9*i+3] = 0;
        arr[6480+9*i+4] = 0.3f;
        arr[6480+9*i+5] = 0;
        si = sin(M_PI*(i+1)/180.0f);
        co = cos(M_PI*(i+1)/180.0f);
        arr[6480+9*i+6] = radius*co;
        arr[6480+9*i+7] = 0.3f;
        arr[6480+9*i+8] = radius*si;
    }
    this->object = create3DObject(GL_TRIANGLES, 360*9, arr, COLOR_BARREL, GL_FILL);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
}

void Barrel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if(this->powerup_present)
        draw3DObject(this->object1);
}

void Barrel::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}
