#include "GLHelper.hpp"
#include "Graph.hpp"

const GraphEventHandler& GLHelper::GetHandler(GLFWwindow* w) {
	auto G = static_cast<Graph*>(glfwGetWindowUserPointer(w));
	return G->GetEventHandler();
}

void GLHelper::CursorPosCallback(GLFWwindow* w, double x, double y) {
	GetHandler(w).CursorPos(2*x/WIDTH-1, 2*y/HEIGHT-1);
}
void GLHelper::MouseButtonCallback(GLFWwindow* w, int button, int action, int /*mods*/) {
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) glfwSetWindowShouldClose(w, GLFW_TRUE);
	GetHandler(w).MouseButton();
}

void GLHelper::KeyCallback(GLFWwindow* w, int key, int /*scancode*/, int action, int /*mods*/) {
	if(action == GLFW_PRESS) {
		if(key == GLFW_KEY_Q) glfwSetWindowShouldClose(w, GLFW_TRUE);
	}
	GetHandler(w).Key();
}
