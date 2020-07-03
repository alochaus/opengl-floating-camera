#ifndef GLOBAL_H
#define GLOBAL_H

#include<glm/glm.hpp>

unsigned short W_WIDTH  = 800;
unsigned short W_HEIGHT = 600;
const char*    W_TITLE  = "opengl window";

bool first_mouse =  true;
float yaw        = -90.0f;
float pitch      =  0.0f;
float last_x     =  (float)W_WIDTH / 2.0;
float last_y     =  (float)W_HEIGHT / 2.0;

float fov       =  45.0f;

glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

float delta_time = 0.0f;
float last_frame = 0.0f;

#endif
