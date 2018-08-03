#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->speed = glm::vec3(0, 0, 0);
    this->rotation = 0;
    this->wind_rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    // static const GLfloat vertex_buffer_data[] = {
    //     -0.4f,-0.1f,-0.4f, // triangle 1 : begin
    //     -0.4f,-0.1f, 0.4f,
    //     -0.4f, 0.1f, 0.4f, // triangle 1 : end
    //     0.4f, 0.1f,-0.4f, // triangle 2 : begin
    //     -0.4f,-0.1f,-0.4f,
    //     -0.4f, 0.1f,-0.4f, // triangle 2 : end
    //     0.4f,-0.1f, 0.4f,
    //     -0.4f,-0.1f,-0.4f,
    //     0.4f,-0.1f,-0.4f,
    //     0.4f, 0.1f,-0.4f,
    //     0.4f,-0.1f,-0.4f,
    //     -0.4f,-0.1f,-0.4f,
    //     -0.4f,-0.1f,-0.4f,
    //     -0.4f, 0.1f, 0.4f,
    //     -0.4f, 0.1f,-0.4f,
    //     0.4f,-0.1f, 0.4f,
    //     -0.4f,-0.1f, 0.4f,
    //     -0.4f,-0.1f,-0.4f,
    //     -0.4f, 0.1f, 0.4f,
    //     -0.4f,-0.1f, 0.4f,
    //     0.4f,-0.1f, 0.4f,
    //     0.4f, 0.1f, 0.4f,
    //     0.4f,-0.1f,-0.4f,
    //     0.4f, 0.1f,-0.4f,
    //     0.4f,-0.1f,-0.4f,
    //     0.4f, 0.1f, 0.4f,
    //     0.4f,-0.1f, 0.4f,
    //     0.4f, 0.1f, 0.4f,
    //     0.4f, 0.1f,-0.4f,
    //     -0.4f, 0.1f,-0.4f,
    //     0.4f, 0.1f, 0.4f,
    //     -0.4f, 0.1f,-0.4f,
    //     -0.4f, 0.1f, 0.4f,
    //     0.4f, 0.1f, 0.4f,
    //     -0.4f, 0.1f, 0.4f,
    //     0.4f,-0.1f, 0.4f
    // };

    static const GLfloat vertex_buffer_data1[] = {
    -0.15f, 0.0f, 0.4f,
    0.15f, 0.0f, 0.4f,
    -0.15f, 0.0f, -0.4f,
    0.15f, 0.0f, -0.4f,
    -0.15f, 0.0f, -0.4f,
    0.15f, 0.0f, 0.4f,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data1, color, GL_FILL);

    static const GLfloat vertex_buffer_data2[] = {
    0.01f, 0, 0,
    -0.01f, 0, 0,
    0.01f, 1.2f, 0,
    -0.01f, 0, 0,
    0.01f, 1.2f, 0,
    -0.01f, 1.2f, 0,

    -0.01f, 1.2f, 0,
    -0.01f, 0.8f, 0,
    -0.24f, 1.0f, 0
    };
    this->object2 = create3DObject(GL_TRIANGLES, 9, vertex_buffer_data2, COLOR_POLE, GL_FILL);

    static GLfloat haha[720*40];
    float radius = 0.1f, si, co;
    for(int i=1;i<=720*2;i++)
    {
        si = sin(M_PI*((float)(i-1)/4.0f)/180.0f);
        co = cos(M_PI*((float)(i-1)/4.0f)/180.0f);
        haha[18*(i-1)] = radius*co;
        haha[18*(i-1)+1] = radius+radius*si+0.3f;
        haha[18*(i-1)+2] = 0.8f;
        haha[18*(i-1)+3] = radius*co;
        haha[18*(i-1)+4] = radius+radius*si+0.3f;
        haha[18*(i-1)+5] = 0.2f;
        si = sin(M_PI*((float)i/4.0f)/180.0f);
        co = cos(M_PI*((float)i/4.0f)/180.0f);
        haha[18*(i-1)+6] = radius*co;
        haha[18*(i-1)+7] = radius+radius*si+0.3f;
        haha[18*(i-1)+8] = 0.2f;

        si = sin(M_PI*((float)(i-1)/4.0f)/180.0f);
        co = cos(M_PI*((float)(i-1)/4.0f)/180.0f);
        haha[18*(i-1)+9] = radius*co;
        haha[18*(i-1)+10] = radius+radius*si+0.3f;
        haha[18*(i-1)+11] = 0.8f;
        si = sin(M_PI*((float)i/4.0f)/180.0f);
        co = cos(M_PI*((float)i/4.0f)/180.0f);
        haha[18*(i-1)+12] = radius*co;
        haha[18*(i-1)+13] = radius+radius*si+0.3f;
        haha[18*(i-1)+14] = 0.8f;
        haha[18*(i-1)+15] = radius*co;
        haha[18*(i-1)+16] = radius+radius*si+0.3f;
        haha[18*(i-1)+17] = 0.2f;
    }
    this->object3 = create3DObject(GL_TRIANGLES, 720*6*2, haha, COLOR_BROWN, GL_FILL);

    static const GLfloat vertex_buffer_data[] = {

    -0.15f, 0.0f, 0.4f,
    -0.15f, 0.0f, -0.4f,
    -0.25f, 0.3f, -0.4f,
    -0.15f, 0.0f, 0.4f,
    -0.25f, 0.3f, -0.4f,
    -0.25f, 0.3f, 0.4f,

    0.15f, 0.0f, 0.4f,
    0.15f, 0.0f, -0.4f,
    0.25f, 0.3f, -0.4f,
    0.15f, 0.0f, 0.4f,
    0.25f, 0.3f, -0.4f,
    0.25f, 0.3f, 0.4f,

    -0.15f, 0.0f, 0.4f,
    0.15f, 0.0f, 0.4f,
    -0.25f, 0.3f, 0.4f,
    0.15f, 0.0f, 0.4f,
    -0.25f, 0.3f, 0.4f,
    0.25f, 0.3f, 0.4f,

    -0.15f, 0.0f, -0.4f,
    0.15f, 0.0f, -0.4f,
    -0.25f, 0.3f, -0.4f,
    0.15f, 0.0f, -0.4f,
    -0.25f, 0.3f, -0.4f,
    0.25f, 0.3f, -0.4f,
    };
    this->object = create3DObject(GL_TRIANGLES, 6*4, vertex_buffer_data, COLOR_BOAT, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 wind_rotate  = glm::rotate((float) (this->wind_rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * wind_rotate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Boat::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
