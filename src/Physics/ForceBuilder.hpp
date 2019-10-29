#pragma once
#include "Basics/Basics.hpp"

#include "Force.hpp"
#include "Node.hpp"

class ForceBuilder {
public:
	static Force AttractionForce(const Node& nodeFrom, const Node& nodeTo);
	static Force RepulsionForce(const Node& nodeFrom, const Node& nodeTo);
	static Force RepulsionFromBoundaryForce(const Node& nodeFrom);
	static Force KeepAtDistForce(const Node& nodeFrom, const Node& nodeTo, double dist);
private:
	static double GravitationalForceMagnitude(const Node& node0, const Node& node1);
	static Force DampedHarmonicOscilationForce(const Node& node0, const Node& node1);
	static Force HarmonicOscilationForce(const Node& node0, const Node& node1);
	static Force DampingForce(const Node& node0, const Node& node1);
};
