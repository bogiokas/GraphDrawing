#include "GLHelper.hpp"
#include "Graph.hpp"

GraphEventHandler& GLHelper::GetHandler(GLFWwindow* w) {
	auto G = static_cast<Graph*>(glfwGetWindowUserPointer(w));
	return G->GetEventHandler();
}

Point2 GLHelper::RawPosToPoint(double i, double j) {
	return Point2(2*i/WIDTH-1, 1-2*j/HEIGHT);
}

void GLHelper::CursorPosCallback(GLFWwindow* w, double i, double j) {
	GetHandler(w).PointerPos(RawPosToPoint(i, j));
}

void GLHelper::MouseButtonCallback(GLFWwindow* w, GLFWResult button, GLFWResult action, GLFWResult /*mods*/) {
	double i, j;
	glfwGetCursorPos(w, &i, &j);
	Point2 pt = RawPosToPoint(i, j);
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		GetHandler(w).SelectVertex();
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		GetHandler(w).DeselectVertex();
//	GLFWResult stateShift = glfwGetKey(w, GLFW_KEY_LEFT_SHIFT);
//	GetHandler(w).MouseButton();
}

void GLHelper::KeyCallback(GLFWwindow* w, GLFWResult key, GLFWResult /*scancode*/, GLFWResult action, GLFWResult /*mods*/) {
	if(action == GLFW_PRESS) {
		if(key == GLFW_KEY_Q) glfwSetWindowShouldClose(w, GLFW_TRUE);
	}
}

