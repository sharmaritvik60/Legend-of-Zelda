#include "boss.h"
#include "main.h"

Boss::Boss(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->health = 100;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -0.7f,-0.7f,-0.7f, // triangle 1 : begin
        -0.7f,-0.7f, 0.7f,
        -0.7f, 0.7f, 0.7f, // triangle 1 : end
        0.7f, 0.7f,-0.7f, // triangle 2 : begin
        -0.7f,-0.7f,-0.7f,
        -0.7f, 0.7f,-0.7f, // triangle 2 : end
        0.7f,-0.7f, 0.7f,
        -0.7f,-0.7f,-0.7f,
        0.7f,-0.7f,-0.7f,
        0.7f, 0.7f,-0.7f,
        0.7f,-0.7f,-0.7f,
        -0.7f,-0.7f,-0.7f,
        -0.7f,-0.7f,-0.7f,
        -0.7f, 0.7f, 0.7f,
        -0.7f, 0.7f,-0.7f,
        0.7f,-0.7f, 0.7f,
        -0.7f,-0.7f, 0.7f,
        -0.7f,-0.7f,-0.7f,
        -0.7f, 0.7f, 0.7f,
        -0.7f,-0.7f, 0.7f,
        0.7f,-0.7f, 0.7f,
        0.7f, 0.7f, 0.7f,
        0.7f,-0.7f,-0.7f,
        0.7f, 0.7f,-0.7f,
        0.7f,-0.7f,-0.7f,
        0.7f, 0.7f, 0.7f,
        0.7f,-0.7f, 0.7f,
        0.7f, 0.7f, 0.7f,
        0.7f, 0.7f,-0.7f,
        -0.7f, 0.7f,-0.7f,
        0.7f, 0.7f, 0.7f,
        -0.7f, 0.7f,-0.7f,
        -0.7f, 0.7f, 0.7f,
        0.7f, 0.7f, 0.7f,
        -0.7f, 0.7f, 0.7f,
        0.7f,-0.7f, 0.7f,

        -0.4f,-1.2f,-0.15f, // triangle 1 : begin
        -0.4f,-1.2f, 0.15f,
        -0.4f, 0.0f, 0.15f, // triangle 1 : end
        -0.3f, 0.0f,-0.15f, // triangle 2 : begin
        -0.4f,-1.2f,-0.15f,
        -0.4f, 0.0f,-0.15f, // triangle 2 : end
        -0.3f,-1.2f, 0.15f,
        -0.4f,-1.2f,-0.15f,
        -0.3f,-1.2f,-0.15f,
        -0.3f, 0.0f,-0.15f,
        -0.3f,-1.2f,-0.15f,
        -0.4f,-1.2f,-0.15f,
        -0.4f,-1.2f,-0.15f,
        -0.4f, 0.0f, 0.15f,
        -0.4f, 0.0f,-0.15f,
        -0.3f,-1.2f, 0.15f,
        -0.4f,-1.2f, 0.15f,
        -0.4f,-1.2f,-0.15f,
        -0.4f, 0.0f, 0.15f,
        -0.4f,-1.2f, 0.15f,
        -0.3f,-1.2f, 0.15f,
        -0.3f, 0.0f, 0.15f,
        -0.3f,-1.2f,-0.15f,
        -0.3f, 0.0f,-0.15f,
        -0.3f,-1.2f,-0.15f,
        -0.3f, 0.0f, 0.15f,
        -0.3f,-1.2f, 0.15f,
        -0.3f, 0.0f, 0.15f,
        -0.3f, 0.0f,-0.15f,
        -0.4f, 0.0f,-0.15f,
        -0.3f, 0.0f, 0.15f,
        -0.4f, 0.0f,-0.15f,
        -0.4f, 0.0f, 0.15f,
        -0.3f, 0.0f, 0.15f,
        -0.4f, 0.0f, 0.15f,
        -0.3f,-1.2f, 0.15f,

        0.4f,-1.2f,-0.15f, // triangle 1 : begin
        0.4f,-1.2f, 0.15f,
        0.4f, 0.0f, 0.15f, // triangle 1 : end
        0.3f, 0.0f,-0.15f, // triangle 2 : begin
        0.4f,-1.2f,-0.15f,
        0.4f, 0.0f,-0.15f, // triangle 2 : end
        0.3f,-1.2f, 0.15f,
        0.4f,-1.2f,-0.15f,
        0.3f,-1.2f,-0.15f,
        0.3f, 0.0f,-0.15f,
        0.3f,-1.2f,-0.15f,
        0.4f,-1.2f,-0.15f,
        0.4f,-1.2f,-0.15f,
        0.4f, 0.0f, 0.15f,
        0.4f, 0.0f,-0.15f,
        0.3f,-1.2f, 0.15f,
        0.4f,-1.2f, 0.15f,
        0.4f,-1.2f,-0.15f,
        0.4f, 0.0f, 0.15f,
        0.4f,-1.2f, 0.15f,
        0.3f,-1.2f, 0.15f,
        0.3f, 0.0f, 0.15f,
        0.3f,-1.2f,-0.15f,
        0.3f, 0.0f,-0.15f,
        0.3f,-1.2f,-0.15f,
        0.3f, 0.0f, 0.15f,
        0.3f,-1.2f, 0.15f,
        0.3f, 0.0f, 0.15f,
        0.3f, 0.0f,-0.15f,
        0.4f, 0.0f,-0.15f,
        0.3f, 0.0f, 0.15f,
        0.4f, 0.0f,-0.15f,
        0.4f, 0.0f, 0.15f,
        0.3f, 0.0f, 0.15f,
        0.4f, 0.0f, 0.15f,
        0.3f,-1.2f, 0.15f
    };
    this->object = create3DObject(GL_TRIANGLES, 36*3, vertex_buffer_data, color, GL_FILL);
    static GLfloat haha[360*25];
    float radius = 0.1f, si, co;
    for(int i=1;i<=360;i++)
    {
        si = sin(M_PI/180.0f * i);
        co = cos(M_PI/180.0f * i);
        haha[18*i] = 0.20f;
        haha[18*i+1] = 0.20f;
        haha[18*i+2] = -0.4f;
        haha[18*i+3] = 0.20f+radius*si;
        haha[18*i+4] = 0.20f+radius*co;
        si = sin(M_PI/180.0f * (i-1));
        co = cos(M_PI/180.0f * (i-1));
        haha[18*i+5] = -0.4f;
        haha[18*i+6] = 0.20f+radius*si;
        haha[18*i+7] = 0.20f+radius*co;
        haha[18*i+8] = -0.4f;

        si = sin(M_PI/180.0f * i);
        co = cos(M_PI/180.0f * i);
        haha[18*i+9] = -0.20f;
        haha[18*i+10] = 0.20f;
        haha[18*i+11] = -0.4f;
        haha[18*i+12] = -0.20f+radius*si;
        haha[18*i+13] = 0.20f+radius*co;
        si = sin(M_PI/180.0f * (i-1));
        co = cos(M_PI/180.0f * (i-1));
        haha[18*i+14] = -0.4f;
        haha[18*i+15] = -0.20f+radius*si;
        haha[18*i+16] = 0.20f+radius*co;
        haha[18*i+17] = -0.4f;
    }
    haha[6498] = -0.1f;
    haha[6499] = -0.1f;
    haha[6500] = -0.4f;
    haha[6501] = 0.1f;
    haha[6502] = -0.1f;
    haha[6503] = -0.4f;
    haha[6504] = -0.1f;
    haha[6505] = -0.2f;
    haha[6506] = -0.4f;

    haha[6507] = 0.1f;
    haha[6508] = -0.2f;
    haha[6509] = -0.4f;
    haha[6510] = 0.1f;
    haha[6511] = -0.1f;
    haha[6512] = -0.4f;
    haha[6513] = -0.1f;
    haha[6514] = -0.2f;
    haha[6515] = -0.4f;
    this->object1 = create3DObject(GL_TRIANGLES, 2172, haha, COLOR_BACKGROUND, GL_FILL);
}

void Boss::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Boss::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}
