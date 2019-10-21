#pragma once
#include "Basics.hpp"

#include "Shapes.hpp"
#include "Graph.hpp"
#include "Physics.hpp"

namespace DrawHelper {
	template<class Drawable>
	void Draw(const Drawable& object);

	template<class Printable>
	void Print(const Printable& object);

	void PrintLine();

	template<> void Draw(const Physics& node);
	template<> void Draw(const std::vector<std::unique_ptr<Vertex>>& vertices);
	template<> void Draw(const std::vector<std::unique_ptr<Edge>>& edges);
	template<> void Print(const Point2& point);
	template<> void Print(const Physics& node);
}

