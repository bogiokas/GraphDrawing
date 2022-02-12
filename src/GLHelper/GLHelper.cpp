#include "GLHelper.hpp"
#include "Graphs/Graph.hpp"

GraphEventHandler& GLHelper::GetHandler(GLFWwindow* w) {
	auto G = static_cast<Graph*>(glfwGetWindowUserPointer(w));
	return G->GetEventHandler();
}

Point2 GLHelper::RawPosToPoint(GLFWwindow* w, double i, double j) {
	int width, height;
	glfwGetWindowSize(w, &width, &height);

	return Point2(2*i/width-1, 1-2*j/height);
}

void GLHelper::WindowSizeCallback(GLFWwindow* /*w*/, int width, int height) {
	glViewport(0, 0, width, height);
}

void GLHelper::CursorPosCallback(GLFWwindow* w, double i, double j) {
	GetHandler(w).PointerPos(RawPosToPoint(w, i, j));
}

void GLHelper::MouseButtonCallback(GLFWwindow* w, GLFWResult button, GLFWResult action, GLFWResult /*mods*/) {
	double i, j;
	glfwGetCursorPos(w, &i, &j);
	Point2 pt = RawPosToPoint(w, i, j);
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

