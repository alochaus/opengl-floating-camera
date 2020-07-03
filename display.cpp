#include"diplay.h"

extern float fov;
extern unsigned short W_WIDTH;
extern unsigned short W_HEIGHT;

bool firstMouse =  true;
float yaw       = -90.0f;
float pitch     =  0.0f;
float last_x    =  (float)W_WIDTH / 2.0;
float last_y    =  (float)W_HEIGHT / 2.0;

extern glm::vec3 camera_front;

static void initialize_and_configure_glfw();
static void initialize_glad();
static void frame_buffer_size_callback(GLFWwindow* window, int width, int height);
static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Display::Display(const unsigned short WIDTH, const unsigned short HEIGHT, const char* TITLE)
{
	initialize_and_configure_glfw();
	
	window = glfwCreateWindow(
		WIDTH,
		HEIGHT,
		TITLE,
		NULL,
		NULL
	);

	if(window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	initialize_glad();
}

Display::~Display()
{
	
}

GLFWwindow* Display::get_window() const
{
	return window;
}

void Display::swap_buffers()
{
	glfwSwapBuffers(window);
}

void Display::poll_event()
{
	glfwPollEvents();
}

bool Display::is_open()
{
	return !glfwWindowShouldClose(window);
}

static void initialize_and_configure_glfw()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __MACOS__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

static void initialize_glad()
{
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(-1);
	}
}

static void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		last_x = xpos;
		last_y = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - last_x;
	float yoffset = last_y - ypos; // reversed since y-coordinates go from bottom to top
	last_x = xpos;
	last_y = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
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

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset * 10;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}
