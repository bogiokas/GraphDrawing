#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "GraphEventHandler.hpp"

static constexpr int WIDTH = 1024;
static constexpr int HEIGHT = 600;

class Graph;

class GLHelper {
public:
	GLHelper(Graph* pG) {
		glfwInit();
#ifdef _DEBUG
		window = glfwCreateWindow(640, 480, "Let There Be Graphs", nullptr, nullptr);
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
		glfwSetCursorPosCallback(window, CursorPosCallback);
		glfwSetMouseButtonCallback(window, MouseButtonCallback);
		glfwSetKeyCallback(window, KeyCallback);
	}
	void EndLoop() {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
private:
	static const GraphEventHandler& GetHandler(GLFWwindow* w);
	static void CursorPosCallback(GLFWwindow* w, double x, double y);
	static void MouseButtonCallback(GLFWwindow* w, int button, int action, int /*mods*/);
	static void KeyCallback(GLFWwindow* w, int key, int /*scancode*/, int action, int /*mods*/);

	GLFWwindow* window;
};
