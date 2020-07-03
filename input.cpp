#include"input.h"

void input::process_input(GLFWwindow* window, float delta_time, glm::vec3& camera_pos, glm::vec3& camera_front, glm::vec3& camera_up)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	const float camera_speed = 2.5 * delta_time;

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera_pos += camera_speed * camera_front;
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera_pos -= camera_speed * camera_front;
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
};

void input::mouse(GLFWwindow* window, double x_pos, double y_pos)
{
	if (first_mouse)
	{
		last_x = x_pos;
		last_y = y_pos;
		first_mouse = false;
	}

	float x_offset = x_pos - last_x;
	float y_offset = last_y - y_pos;
	last_x = x_pos;
	last_y = y_pos;

	float sensitivity = 0.1f;
	x_offset *= sensitivity;
	y_offset *= sensitivity;

	yaw += x_offset;
	pitch += y_offset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camera_front = glm::normalize(front);
}

void input::scroll(GLFWwindow *window, double x_offset, double y_offset)
{
	fov -= (float)y_offset * 10;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}
