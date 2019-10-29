#include "ForceBuilder.hpp"

Force ForceBuilder::AttractionForce(const Node& nodeFrom, const Node& nodeTo) {
	double forceMagnitude = GravitationalForceMagnitude(nodeFrom, nodeTo);
	Point2 direction = nodeTo.GetPos() - nodeFrom.GetPos();
	direction.Normalize();
	return direction * forceMagnitude;
}

Force ForceBuilder::RepulsionForce(const Node& nodeFrom, const Node& nodeTo) {
	double forceMagnitude = GravitationalForceMagnitude(nodeFrom, nodeTo);
	Point2 direction = nodeFrom.GetPos() - nodeTo.GetPos();
	direction.Normalize();
	return direction * forceMagnitude;
}

Force ForceBuilder::RepulsionFromBoundaryForce(const Node& nodeFrom) {
	const auto& pos = nodeFrom.GetPos();
	Node projRight = Node(Point2(1.0, pos[1]));
	double forceMagnitudeRight = GravitationalForceMagnitude(nodeFrom, projRight);
	Node projLeft = Node(Point2(-1.0, pos[1]));
	double forceMagnitudeLeft = GravitationalForceMagnitude(nodeFrom, projLeft);
	Node projUp = Node(Point2(pos[0], -1.0));
	double forceMagnitudeUp = GravitationalForceMagnitude(nodeFrom, projUp);
	Node projDown = Node(Point2(pos[0], 1.0));
	double forceMagnitudeDown = GravitationalForceMagnitude(nodeFrom, projDown);
	return Point2::Xinv() * forceMagnitudeRight +
		Point2::X() * forceMagnitudeLeft +
		Point2::Yinv() * forceMagnitudeUp +
		Point2::Y() * forceMagnitudeDown;
}

Force ForceBuilder::KeepAtDistForce(const Node& nodeFrom, const Node& nodeTo, double dist) {
	double d = (nodeFrom.GetPos() - nodeTo.GetPos()).Norm();
	double frac = (d - dist)/d;
	const auto fracPos = nodeFrom.GetPos()*(1-frac) + nodeTo.GetPos()*frac;
	const auto nodeTarget = Node(fracPos, nodeTo.GetVel());
	return DampedHarmonicOscilationForce(nodeFrom, nodeTarget);
}

double ForceBuilder::GravitationalForceMagnitude(const Node& node0, const Node& node1) {
	constexpr double gConst = 0.005;
	double distQ = (node0.GetPos() - node1.GetPos()).NormQ();
	return gConst * node0.GetMass()  * node1.GetMass() / distQ;
}

Force ForceBuilder::DampedHarmonicOscilationForce(const Node& node0, const Node& node1) {
	return HarmonicOscilationForce(node0, node1) + DampingForce(node0, node1);
}

Force ForceBuilder::HarmonicOscilationForce(const Node& node0, const Node& node1) {
	constexpr double kConst = 0.01;
	Point2 relativePos = node1.GetPos() - node0.GetPos();
	return relativePos * kConst;
}

Force ForceBuilder::DampingForce(const Node& node0, const Node& node1) {
	constexpr double cConst = 0.1; // limit: 2sqrt(m*k) = 0.2
	Point2 relativeVel = node1.GetVel() - node0.GetVel();
	return relativeVel * cConst;
}

