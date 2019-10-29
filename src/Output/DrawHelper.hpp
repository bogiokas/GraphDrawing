#pragma once
#include "Basics/Basics.hpp"

#include "Basics/Shapes.hpp"
#include "Graphs/Graph.hpp"
#include "Physics/Node.hpp"

class DrawHelper {
public:
	template<class Drawable>
	static void Draw(const Drawable& object);
};

template<> void DrawHelper::Draw(const Node& node);

template<> void DrawHelper::Draw(const std::vector<std::unique_ptr<Vertex>>& vertices);
template<> void DrawHelper::Draw(const std::vector<std::unique_ptr<Edge>>& edges);