#include "GraphEventHandler.hpp"
#include<iostream>

void GraphEventHandler::CursorPos(double x, double y) const {

	std::cout<<x<<" "<<y<<std::endl;
}

void GraphEventHandler::MouseButton() const {
}

void GraphEventHandler::Key() const {
}
