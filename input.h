#ifndef INPUT_H
#define INPUT_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

extern bool first_mouse;
extern float yaw;
extern float pitch;
extern float last_x;
extern float last_y;
extern float fov;

extern glm::vec3 camera_front;

namespace input
{
	void process_input(GLFWwindow* window, float delta_time, glm::vec3& camera_pos, glm::vec3& camera_front, glm::vec3& camera_up);
	void mouse(GLFWwindow* window, double x_pos, double y_pos);
	void scroll(GLFWwindow* window, double x_offset, double y_offset);
}

#endif

