#pragma once
#include "Basics/Basics.hpp"

#include "Basics/Shapes.hpp"
#include "Physics/Node.hpp"

class PrintHelper {
public:
	static void PrintLine();
	template<class Printable>
	static void Print(const Printable& object);
};

template<> void PrintHelper::Print(const Point2& point);
template<> void PrintHelper::Print(const Node& node);
