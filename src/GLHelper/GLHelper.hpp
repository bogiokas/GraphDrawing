#pragma once
#include "Graphs/GraphEventHandler.hpp"

#include<GL/glew.h>
#include<GLFW/glfw3.h>

using GLFWResult = int;

#ifdef _WIN32
static constexpr int WIDTH = 1920;
static constexpr int HEIGHT = 1080;
#else
static constexpr int WIDTH = 1024;
static constexpr int HEIGHT = 600;
#endif

class Graph;

class GLHelper {
public:
	GLHelper(Graph* pG) : window(nullptr) {
		glfwInit();
#ifdef _DEBUG
		window = glfwCreateWindow(WIDTH, HEIGHT, "Let There Be Graphs", nullptr, nullptr);
#else
		window = glfwCreateWindow(WIDTH, HEIGHT, "Let There Be Graphs", glfwGetPrimaryMonitor(), nullptr);
#endif
		glfwMakeContextCurrent(window);
		glewInit();
		glfwSetWindowUserPointer(window, static_cast<void*>(pG));
	}
	~GLHelper() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}
	bool IsActive() {
		return !glfwWindowShouldClose(window);
	}
	void BeginLoop() {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSetWindowSizeCallback(window, WindowSizeCallback);
		glfwSetCursorPosCallback(window, CursorPosCallback);
		glfwSetMouseButtonCallback(window, MouseButtonCallback);
		glfwSetKeyCallback(window, KeyCallback);
	}
	void EndLoop() {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
private:
	GLHelper(const GLHelper& other) = delete;
	GLHelper operator=(const GLHelper& other) = delete;
	static GraphEventHandler& GetHandler(GLFWwindow* w);
	static Point2 RawPosToPoint(GLFWwindow* w, double i, double j);
	static void WindowSizeCallback(GLFWwindow* /*w*/, int width, int height);
	static void CursorPosCallback(GLFWwindow* w, double i, double j);
	static void MouseButtonCallback(GLFWwindow* w, GLFWResult button, GLFWResult action, GLFWResult /*mods*/);
	static void KeyCallback(GLFWwindow* w, GLFWResult key, GLFWResult /*scancode*/, GLFWResult action, GLFWResult /*mods*/);

	GLFWwindow* window;
};

